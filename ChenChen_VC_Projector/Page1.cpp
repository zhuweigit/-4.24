// Page1.cpp : 实现文件
//

#include "stdafx.h"
#include "zhuwei.h"
#include "Page1.h"
#include "afxdialogex.h"
#include <algorithm>
#include"CSeries.h"

// CPage1 对话框

IMPLEMENT_DYNAMIC(CPage1, CDialog)

//读取文件线程
DWORD WINAPI ThreadReadFile(LPVOID lpParameter);
//显示所有数据线程
DWORD WINAPI ThreadDisplayAllData(LPVOID lpParameter);

std::vector<std::vector<CString>> allFileVector;

CPage1::CPage1(CWnd* pParent /*=NULL*/)
	: CDialog(CPage1::IDD, pParent)
	, m_nRadio(0)
	, m_DataName(_T(""))
	, m_switchPaintName(0)
	, m_switchPaint(0)
{
	m_brush_cp1.CreateSolidBrush(RGB(69, 71, 72));//背景颜色
}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listControl);
	DDX_Control(pDX, IDC_PROGRESS1, m_speed);
	//	DDX_Control(pDX, IDC_PICSHOW, m_PicCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_EDIT2, m_fileName);
	DDX_Control(pDX, IDC_TCHART1, m_chart);
	DDX_Control(pDX, IDC_EDIT3, m_dataLineName);
}


BEGIN_MESSAGE_MAP(CPage1, CDialog)
//	ON_WM_CTLCOLOR()
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CPage1::OnLvnItemchangedList2)
	ON_BN_CLICKED(IDC_RADIO1, &CPage1::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CPage1::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CPage1::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CPage1::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON2, &CPage1::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPage1::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPage1::OnBnClickedButton4)
END_MESSAGE_MAP()


// CPage1 消息处理程序


BOOL CPage1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//为ListControl控件添加表头
	m_listControl.InsertColumn(0, L"序号", LVCFMT_LEFT, 50);
	m_listControl.InsertColumn(1, L"数据显示", LVCFMT_LEFT, 500);

	//初始状态下数据提取默认一般数据提取
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO3)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO4)->EnableWindow(FALSE);

	//一般数据初始化
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("Heading/首向角"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("Pitch/纵摇角"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("Roll/横倾角"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("GPS Latitude/纬度"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("GPS Longitude/经度"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("GPS Position/船位"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("COG/对地航向"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("SOG/对地航速"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("GPS UTC/国际协调时"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);

	//任意数据初始化
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("AT2"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("POS"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("SAT"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("SA4"));
	((CComboBox*)GetDlgItem(IDC_COMBO4))->EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CPage1::readFile()
{
	HANDLE hThreadReadFile;

	hThreadReadFile = CreateThread(NULL, 0, ThreadReadFile, this, 0, NULL);
	CloseHandle(hThreadReadFile);
}

DWORD WINAPI ThreadReadFile(LPVOID lpParameter)
{
	CPage1* page1 = (CPage1*)lpParameter;
	//TRUE表示打开
	CFileDialog fileDlg(true);

	//设置对话框标题文字
	fileDlg.m_ofn.lpstrTitle = L"选择船舶数据";

	//格式过滤器
	fileDlg.m_ofn.lpstrFilter = L"Log Files(*.log)\0*.log\0Txt Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";

	//显示文件对话框,并判断对话框是否正常打开
	if (fileDlg.DoModal() == TRUE)
	{
		//获取文件名
		CString m_File = fileDlg.GetFileName();
		//显示所获取的文件名
		page1->m_fileName.SetWindowTextW(m_File);

		//获取所打开文件的完整路径filePath
		CString filePath = fileDlg.GetPathName();

		//初始化文件总大小和当前已经读取的大小
		double fileSize = 0;
		double nowReadSize = 0;

		//获取打开文件的大小
		CFileStatus fileStatus;
		if (CFile::GetStatus(filePath, fileStatus))
		{
			fileSize = fileStatus.m_size;
		}

		page1->m_speed.SetRange(0, 1000); //设置进度条的范围 

		//读入新数据前先清空ListControl控件中的数据
		page1->m_listControl.DeleteAllItems();

		//使用CStdioFile类的构造函数按行读入文本数据
		CStdioFile file(filePath, CFile::modeRead);
		CString strNowLine;		//当前所读入这行的数据
		CString strOneWord;		//当前度入行oneLineString中当前读入的两个逗号之间的数据
		CString strNumber;		//当前的读取进度
		int curPos;		//正在处理的一行数据中，当前逗号所在位置是本行中的第curPos个字符
		int intLineNum = 0;	//ListControl控件中数据显示的行序号
		CString strLineNum;	//将lineNum转换成CString类型便于在ListControl中显示
		std::vector<CString> nowLineVector;		//当前读入行暂时存储的容器

		//清空容器中的数据
		page1->m_allFileVector.clear();
		page1->m_allFileLineVector.clear();
		allFileVector.clear();

		//读入数据并显示在ControlList控件中
		while (file.ReadString(strNowLine))
		{
			curPos = 0;
			//将int型的lineNum转换为CString型的strLineNum
			strLineNum.Format(_T("%d"), intLineNum + 1);

			//在ListControl中显示数据
			page1->m_listControl.InsertItem(intLineNum, _T(""));
			page1->m_listControl.SetItemText(intLineNum, 0, strLineNum);
			page1->m_listControl.SetItemText(intLineNum, 1, strNowLine);

			//获取当前读入的大小
			//nowReadSize += (strNowLine.GetLength() + 2);
			nowReadSize += (strNowLine.GetLength() + 1);
			page1->m_speed.SetPos(1000 * (nowReadSize / fileSize));

			//百分号显示读取进度
			strNumber.Format(_T("%3.2f"), (double)(100 * (nowReadSize / fileSize)));
			page1->m_edit.SetWindowTextW(strNumber + "%");

			intLineNum++;

			//按行写入行容器中
			page1->m_allFileLineVector.push_back(strNowLine);
			//取出第一个逗号前的数据
			strOneWord = strNowLine.Tokenize(_T(","), curPos);

			while (strOneWord != "")
			{
				//将取出的数据放到当前读入行暂时存储的容器中
				nowLineVector.push_back(strOneWord);
				//取下一个逗号前的数据
				strOneWord = strNowLine.Tokenize(_T(","), curPos);
			}

			//当前行容器存放完毕，将取出的数据放到总容器中
			page1->m_allFileVector.push_back(nowLineVector);

			nowLineVector.clear();

		}
		page1->m_speed.SetPos(1000);
		page1->m_edit.SetWindowTextW(L"100%");

		//将全部数据给全局容器allFileVector方便其他多线程使用
		allFileVector = page1->m_allFileVector;

		return 0;
	}
	else
		return 0;
}

void CPage1::progress()
{
	CProgressCtrl *myProCtrl = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);
	myProCtrl->SetRange(0, 100);
	for (int i = 0; i<100; i++)
	{
		//myProCtrl2->OffsetPos(1); //此句代码等同于下两句，以固定步长1更新显示，该功能也可以这样实现：myProCtrl2->SetPos(i); 
		myProCtrl->SetStep(1);
		myProCtrl->StepIt();
		Sleep(100);
	}
}

void CPage1::OnBnClickedRadio1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_nRadio = 0;
	if (m_nRadio == 0)
	{
		GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO3)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO4)->EnableWindow(FALSE);
	}

}


void CPage1::OnBnClickedRadio2()
{
	// TODO:  在此添加控件通知处理程序代码
	m_nRadio = 1;
	if (m_nRadio == 1)
	{
		GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO3)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO4)->EnableWindow(TRUE);
	}
}

//两参数数据提取
void CPage1::selectFileData(CString strIndex, int ip)
{
	m_selectDataVector.clear();
	for (int i = 0; i < m_allFileVector.size(); i++)
	{
		if (m_allFileVector[i][1] == strIndex)
			m_selectDataVector.push_back(m_allFileVector[i][ip]);
	}
}

//三参数数据提取
void CPage1::selectFileData(CString strIndex, int ip, int ic)
{
	m_selectDataVector.clear();
	for (int i = 0; i < m_allFileVector.size(); i++)
	{
		if (m_allFileVector[i][1] == strIndex)
			m_selectDataVector.push_back(m_allFileVector[i][ip] + m_allFileVector[i][ic]);
	}
}

//在任一数据提取时，根据选择的数据字段，确定逗号的个数
void CPage1::OnCbnSelchangeCombo3()
{
	// TODO:  在此添加控件通知处理程序代码
	((CComboBox*)GetDlgItem(IDC_COMBO4))->ResetContent();	//清除原有数据
	int index = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();	//当前选中的行
	((CComboBox*)GetDlgItem(IDC_COMBO4))->EnableWindow(true);
	switch (index)
	{
	case 0:
		for (int i = 0; i < 12; i++)
		{
			CString strtemp;
			strtemp.Format(_T("%d"), i);
			((CComboBox*)GetDlgItem(IDC_COMBO4))->AddString(strtemp);
		}
		break;

	case 1:
		for (int i = 0; i < 19; i++)
		{
			CString strtemp;
			strtemp.Format(_T("%d"), i);
			((CComboBox*)GetDlgItem(IDC_COMBO4))->AddString(strtemp);
		}
		break;

	case 2:
		for (int i = 0; i < 57; i++)
		{
			CString strtemp;
			strtemp.Format(_T("%d"), i);
			((CComboBox*)GetDlgItem(IDC_COMBO4))->AddString(strtemp);
		}
		break;

	case 3:
		for (int i = 0; i < 20; i++)
		{
			CString strtemp;
			strtemp.Format(_T("%d"), i);
			((CComboBox*)GetDlgItem(IDC_COMBO4))->AddString(strtemp);
		}
		break;
	}
}

//提取数据
void CPage1::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (CPage1::m_nRadio == 0)
	{
		m_switchPaintName = 0;//按给定数据提取时会显示所提取的数据名称
		m_switchPaint = 1;//可以进行画曲线操作
		int index = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetLBText(index, m_DataName);
		if (m_DataName == _T("Heading/首向角"))
			selectFileData(_T("AT2"), 3);
		if (m_DataName == _T("Pitch/纵摇角"))
			selectFileData(_T("AT2"), 4);
		if (m_DataName == _T("Roll/横倾角"))
			selectFileData(_T("AT2"), 5);
		if (m_DataName == _T("GPS Latitude/纬度"))
			selectFileData(_T("POS"), 5, 6);
		if (m_DataName == _T("GPS Longitude/经度"))
			selectFileData(_T("POS"), 7, 8);
		if (m_DataName == _T("GPS Position/船位"))
			selectFileData(_T("POS"), 9);
		if (m_DataName == _T("COG/对地航向"))
			selectFileData(_T("POS"), 11);
		if (m_DataName == _T("SOG/对地航速"))
			selectFileData(_T("POS"), 12);
		if (m_DataName == _T("GPS UTC/国际协调时"))
			selectFileData(_T("POS"), 4);
	}
	else
	{
		m_switchPaintName = 1;//自定义提取时不显示数据名称
		CString strIndex;
		CString temp;
		int index = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO3))->GetLBText(index, strIndex);
		GetDlgItemText(IDC_COMBO4, temp);
		int iTemp = _ttoi(temp);
		selectFileData(strIndex, iTemp);
	}

	//当没有读入数据时弹出对话框
	if (m_selectDataVector.empty())
	{
		MessageBox(_T("请先读入数据"));
	}

	//清空ListControl控件，准备写入提取出的数据
	m_listControl.DeleteAllItems();
	int intLineNum = 0;		//ListControl控件中数据的序号
	for (int i = 0; i < m_selectDataVector.size(); i++)
	{
		CString strLineNum;		//ListControl控件中数据的序号intLineNum装换为CString
		strLineNum.Format(_T("%d"), intLineNum + 1);
		m_listControl.InsertItem(i, _T(""));
		m_listControl.SetItemText(i, 0, strLineNum);
		m_listControl.SetItemText(i, 1, m_selectDataVector[i]);
		intLineNum++;
	}
}

//数据存盘
void CPage1::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_selectDataVector.empty())
	{
		MessageBox(_T("请提取所需数据后保存"));
		return;
	}
	CFileDialog FileDlg(false, _T("txt"), NULL, OFN_OVERWRITEPROMPT, NULL, this);

	if (FileDlg.DoModal() == TRUE)
	{
		CString FilePath = FileDlg.GetPathName();
		CStdioFile DataFile(FilePath, CFile::modeWrite | CFile::modeCreate);
		CString str;
		for (int i = 0; i < m_selectDataVector.size(); i++)
		{
			str = m_selectDataVector[i] + L"\r\n";
			DataFile.WriteString(str);
		}
		DataFile.Close();
	}
	else
		return;
}

//绘制图形
void CPage1::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_allFileVector.empty())
	{
		MessageBox(_T("请读入数据并提取"));
		return ;
	}

	if (m_switchPaint == 0)
	{
		MessageBox(_T("请先提取数据"));
		return;
	}

	//控制"显示曲线:"后是否显示数据名称
	if (m_switchPaintName == 0)
		m_dataLineName.SetWindowTextW(m_DataName);
	else
		m_dataLineName.SetWindowTextW(L"");

	//使用TeeChart绘制图形
	CSeries lineSeries = (CSeries)m_chart.Series(0);
	lineSeries.Clear();
	for (int i = 0; i<m_selectDataVector.size(); i++)
	{
		double rand = _wtof(m_selectDataVector[i].GetBuffer(0));
		lineSeries.AddXY((double)i, rand, NULL, NULL);
	}

}

//显示所有数据
void CPage1::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	//检查是否先读入了数据
	if (m_allFileVector.empty())
	{
		MessageBox(_T("请先读入数据"));
		return;
	}

	//清空listControl控件
	m_listControl.DeleteAllItems();
	//清空百分比显示
	m_edit.SetWindowTextW(L"");
	//添加显示所有数据线程句柄
	HANDLE hThreadDisplayAllData;
	//创建显示所有数据的线程
	hThreadDisplayAllData = CreateThread(NULL, 0, ThreadDisplayAllData, this, 0, NULL);
	CloseHandle(hThreadDisplayAllData);

	/*int intLineNum = 0;		//ListControl控件中数据的序号
	CString strarray;		//转换为CString后的序号
	for (int i = 0; i < m_allFileLineVector.size(); i++)
	{
		strarray.Format(_T("%d"), intLineNum + 1);
		m_listControl.InsertItem(i, _T(""));
		m_listControl.SetItemText(i, 0, strarray);
		m_listControl.SetItemText(i, 1, m_allFileLineVector[i]);
		intLineNum++;
	}*/
}

DWORD WINAPI ThreadDisplayAllData(LPVOID lpParameter)
{
	CPage1* page1 = (CPage1*)lpParameter;
	int intLineNum = 0;		//ListControl控件中数据的序号
	CString strarray;		//转换为CString后的序号

	double fileSize = 0;	//数据总大小
	double m = 0;			//进度条的步长

	fileSize = allFileVector.size();	//获得数据总大小

	page1->m_speed.SetRange(0, allFileVector.size()); //设置进度条的范围

	for (int i = 0; i < allFileVector.size(); i++)
	{
		//列表控件数据显示
		strarray.Format(_T("%d"), intLineNum + 1);
		page1->m_listControl.InsertItem(i, _T(""));
		page1->m_listControl.SetItemText(i, 0, strarray);
		page1->m_listControl.SetItemText(i, 1, page1->m_allFileLineVector[i]);
		intLineNum++;
		//进度条显示
		page1->m_speed.SetPos(i);
	}
	page1->m_speed.SetPos(allFileVector.size());
	return 0;
}