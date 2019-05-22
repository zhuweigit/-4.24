// Page2.cpp : 实现文件
//

#include "stdafx.h"
#include "zhuwei.h"
#include "Page2.h"
#include "afxdialogex.h"
#include"CSeries.h"

// CPage2 对话框

//提取经纬度线程
DWORD WINAPI ThreadReadPOS(LPVOID lpParameter);

IMPLEMENT_DYNAMIC(CPage2, CDialog)

CPage2::CPage2(CWnd* pParent /*=NULL*/)
	: CDialog(CPage2::IDD, pParent)
{

}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listControl);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_TCHART1, m_chart);
}


BEGIN_MESSAGE_MAP(CPage2, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPage2::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPage2::OnBnClickedButton2)
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPage2 消息处理程序


BOOL CPage2::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//为ListControl控件添加表头
	m_listControl.InsertColumn(0, L"经度", LVCFMT_LEFT, 110);
	m_listControl.InsertColumn(1, L"纬度", LVCFMT_LEFT, 110);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//提取经纬度数据
void CPage2::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	HANDLE hThreadReadFile2;

	hThreadReadFile2 = CreateThread(NULL, 0, ThreadReadPOS, this, 0, NULL);
	CloseHandle(hThreadReadFile2);

}

DWORD WINAPI ThreadReadPOS(LPVOID lpParameter)
{
	CPage2* page2 = (CPage2*)lpParameter;

	//经纬度数据提取
	page2->selectFileData(_T("POS"), 5);

	//ListControl控件中数据显示的行序号
	int intLineNum = 0;	
	//进度条声明
	page2->m_progress.SetRange(0, page2->m_POS_1_Vector.size()); //设置进度条的范围
	//读入新数据前先清空ListControl控件中的数据
	page2->m_listControl.DeleteAllItems();

	for (int i = 0; i < page2->m_POS_1_Vector.size(); i++)
	{
		page2->m_listControl.InsertItem(intLineNum, _T(""));
		page2->m_listControl.SetItemText(intLineNum, 0, page2->m_POS_1_Vector[i]);
		page2->m_listControl.SetItemText(intLineNum, 1, page2->m_POS_2_Vector[i]);

		//进度条显示
		page2->m_progress.SetPos(i);
	}
	page2->m_progress.SetPos(page2->m_POS_1_Vector.size());
	return 0;
}

void CPage2::selectFileData(CString strIndex, int ip)
{
	m_POS_1_Vector.clear();
	for (int i = 0; i < allFileVector.size(); i++)
	{
		if (allFileVector[i][1] == strIndex)
		{
			m_POS_1_Vector.push_back(allFileVector[i][ip]);
			m_POS_2_Vector.push_back(allFileVector[i][ip + 2]);
		}
	}
}

void CPage2::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_POS_1_Vector.empty())
	{
		MessageBox(_T("请读入数据并提取"));
		return;
	}

	//使用TeeChart绘制图形
	CSeries lineSeries = (CSeries)m_chart.Series(0);
	lineSeries.Clear();
	for (int i = 0; i < m_POS_1_Vector.size(); i++)
	{
		double axis = _wtof(m_POS_2_Vector[i].GetBuffer(0));
		double rand = _wtof(m_POS_1_Vector[i].GetBuffer(0));
		lineSeries.AddXY(axis, rand, NULL, NULL);
	}
}