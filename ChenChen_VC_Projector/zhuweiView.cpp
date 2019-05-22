
// zhuweiView.cpp : CzhuweiView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "zhuwei.h"
#endif

#include "zhuweiDoc.h"
#include "zhuweiView.h"
#include"MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CzhuweiView

IMPLEMENT_DYNCREATE(CzhuweiView, CFormView)

BEGIN_MESSAGE_MAP(CzhuweiView, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CzhuweiView::OnTcnSelchangeTab1)
	ON_WM_PAINT()
//	ON_WM_CTLCOLOR()
ON_COMMAND(ID_FILE_OPEN, &CzhuweiView::OnFileOpen)
//ON_WM_CREATE()
ON_WM_TIMER()
END_MESSAGE_MAP()

// CzhuweiView 构造/析构

CzhuweiView::CzhuweiView()
	: CFormView(CzhuweiView::IDD)
	, m_CurSelTab(0)
{
	// TODO:  在此处添加构造代码
}

CzhuweiView::~CzhuweiView()
{
}

void CzhuweiView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	//将变量m_tab与Tab Control控件绑定
	//IDC_TAB1是Tab Control控件的ID
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BOOL CzhuweiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CzhuweiView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	//为Tab Control增加五个页面
	m_tab.InsertItem(0, _T("数据提取模块"));
	m_tab.InsertItem(1, _T("数据处理模块"));
	m_tab.InsertItem(2, _T("建模模块"));
	m_tab.InsertItem(3, _T("仿真模块"));
	m_tab.InsertItem(4, _T("比较模块"));

	//创建两个对话框
	m_page1.Create(IDD_DIALOG1, &m_tab);
	m_page2.Create(IDD_DIALOG2, &m_tab);
	m_page3.Create(IDD_DIALOG3, &m_tab);
	m_page4.Create(IDD_DIALOG4, &m_tab);
	m_page5.Create(IDD_DIALOG5, &m_tab);

	//设定在Tab内显示的范围
	CRect rc;
	//获得TAB控件的坐标
	m_tab.GetClientRect(rc);

	//定位选项卡页的位置，这里可以根据情况自己调节偏移量
	rc.top += 20;
	rc.bottom -= 5;
	rc.left += 1;
	rc.right -= 2;

	//将子页面移动到指定的位置
	m_page1.MoveWindow(&rc);
	m_page2.MoveWindow(&rc);
	m_page3.MoveWindow(&rc);
	m_page4.MoveWindow(&rc);
	m_page5.MoveWindow(&rc);

	//显示子页面
	//显示初始页面
	m_page1.ShowWindow(SW_SHOW);
	m_page2.ShowWindow(SW_HIDE);
	m_page3.ShowWindow(SW_HIDE);
	m_page4.ShowWindow(SW_HIDE);
	m_page5.ShowWindow(SW_HIDE);

	//保存当前选择
	//m_CurSelTab = 0;
	m_tab.SetCurSel(0);

//	SetTimer(1, 1000, NULL);
}


// CzhuweiView 诊断

#ifdef _DEBUG
void CzhuweiView::AssertValid() const
{
	CFormView::AssertValid();
}

void CzhuweiView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CzhuweiDoc* CzhuweiView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CzhuweiDoc)));
	return (CzhuweiDoc*)m_pDocument;
}
#endif //_DEBUG


// CzhuweiView 消息处理程序


void CzhuweiView::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	switch (m_tab.GetCurSel())
	{
	case 0:
		m_page1.ShowWindow(SW_SHOW);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_HIDE);
		m_page5.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_SHOW);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_HIDE);
		m_page5.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_SHOW);
		m_page4.ShowWindow(SW_HIDE);
		m_page5.ShowWindow(SW_HIDE);
		break;
	case 3:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_SHOW);
		m_page5.ShowWindow(SW_HIDE);
		break;
	case 4:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_HIDE);
		m_page5.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}


void CzhuweiView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CFormView::OnPaint()
}

void CzhuweiView::OnFileOpen()
{
	// TODO:  在此添加命令处理程序代码
	
	m_page1.readFile();		//执行读取文件函数

}



void CzhuweiView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
//	m_progress.StepIt();	//控制进度条的进度
	CFormView::OnTimer(nIDEvent);
}

//
//DWORD WINAPI CzhuweiView::ThreadSpeed(LPVOID lpParameter)
//{
//	CProgressCtrl *Speed = (CProgressCtrl*)lpParameter;
//
//	Speed->SetRange(0, 100000); //设置进度条的范围     
//	for (int i = 0; i < 100000; i++)
//	{
//		Speed->SetPos(i); //进度条的位置  
//	}
//
//	return 0;
//}
//
//DWORD WINAPI CzhuweiView::ThreadReadFile(LPVOID lpParameter)
//{
//	//使用CStdioFile类的构造函数按行读入文本数据
//	CStdioFile file(filePath, CFile::modeRead);
//	CString strNowLine;		//当前所读入这行的数据
//	CString strOneWord;		//当前度入行oneLineString中当前读入的两个逗号之间的数据
//	int curPos;		//正在处理的一行数据中，当前逗号所在位置是本行中的第curPos个字符
//	int intLineNum = 0;	//ListControl控件中数据显示的行序号
//	CString strLineNum;	//将lineNum转换成CString类型便于在ListControl中显示
//	std::vector<CString> nowLineVector;		//当前读入行暂时存储的容器
//
//	while (file.ReadString(strNowLine))
//	{
//		curPos = 0;
//		//将int型的lineNum转换为CString型的strLineNum
//		strLineNum.Format(_T("%d"), intLineNum + 1);
//
//		//在ListControl中显示数据
//		m_page1.m_listControl.InsertItem(intLineNum, _T(""));
//		m_page1.m_listControl.SetItemText(intLineNum, 0, strLineNum);
//		m_page1.m_listControl.SetItemText(intLineNum, 1, strNowLine);
//		intLineNum++;
//		//取出第一个逗号前的数据
//		strOneWord = strNowLine.Tokenize(_T(","), curPos);
//
//		while (strOneWord != "")
//		{
//			//将取出的数据放到当前读入行暂时存储的容器中
//			nowLineVector.push_back(strOneWord);
//			//取下一个逗号前的数据
//			strOneWord = strNowLine.Tokenize(_T(","), curPos);
//		}
//
//		//当前行容器存放完毕，将取出的数据放到总容器中
//		m_allFileVector.push_back(nowLineVector);
//		nowLineVector.clear();
//	}
//	return 0;
//}