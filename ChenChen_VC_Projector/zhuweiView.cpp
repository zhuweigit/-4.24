
// zhuweiView.cpp : CzhuweiView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CzhuweiView ����/����

CzhuweiView::CzhuweiView()
	: CFormView(CzhuweiView::IDD)
	, m_CurSelTab(0)
{
	// TODO:  �ڴ˴���ӹ������
}

CzhuweiView::~CzhuweiView()
{
}

void CzhuweiView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	//������m_tab��Tab Control�ؼ���
	//IDC_TAB1��Tab Control�ؼ���ID
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BOOL CzhuweiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CzhuweiView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	//ΪTab Control�������ҳ��
	m_tab.InsertItem(0, _T("������ȡģ��"));
	m_tab.InsertItem(1, _T("���ݴ���ģ��"));
	m_tab.InsertItem(2, _T("��ģģ��"));
	m_tab.InsertItem(3, _T("����ģ��"));
	m_tab.InsertItem(4, _T("�Ƚ�ģ��"));

	//���������Ի���
	m_page1.Create(IDD_DIALOG1, &m_tab);
	m_page2.Create(IDD_DIALOG2, &m_tab);
	m_page3.Create(IDD_DIALOG3, &m_tab);
	m_page4.Create(IDD_DIALOG4, &m_tab);
	m_page5.Create(IDD_DIALOG5, &m_tab);

	//�趨��Tab����ʾ�ķ�Χ
	CRect rc;
	//���TAB�ؼ�������
	m_tab.GetClientRect(rc);

	//��λѡ�ҳ��λ�ã�������Ը�������Լ�����ƫ����
	rc.top += 20;
	rc.bottom -= 5;
	rc.left += 1;
	rc.right -= 2;

	//����ҳ���ƶ���ָ����λ��
	m_page1.MoveWindow(&rc);
	m_page2.MoveWindow(&rc);
	m_page3.MoveWindow(&rc);
	m_page4.MoveWindow(&rc);
	m_page5.MoveWindow(&rc);

	//��ʾ��ҳ��
	//��ʾ��ʼҳ��
	m_page1.ShowWindow(SW_SHOW);
	m_page2.ShowWindow(SW_HIDE);
	m_page3.ShowWindow(SW_HIDE);
	m_page4.ShowWindow(SW_HIDE);
	m_page5.ShowWindow(SW_HIDE);

	//���浱ǰѡ��
	//m_CurSelTab = 0;
	m_tab.SetCurSel(0);

//	SetTimer(1, 1000, NULL);
}


// CzhuweiView ���

#ifdef _DEBUG
void CzhuweiView::AssertValid() const
{
	CFormView::AssertValid();
}

void CzhuweiView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CzhuweiDoc* CzhuweiView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CzhuweiDoc)));
	return (CzhuweiDoc*)m_pDocument;
}
#endif //_DEBUG


// CzhuweiView ��Ϣ�������


void CzhuweiView::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()
}

void CzhuweiView::OnFileOpen()
{
	// TODO:  �ڴ���������������
	
	m_page1.readFile();		//ִ�ж�ȡ�ļ�����

}



void CzhuweiView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	m_progress.StepIt();	//���ƽ������Ľ���
	CFormView::OnTimer(nIDEvent);
}

//
//DWORD WINAPI CzhuweiView::ThreadSpeed(LPVOID lpParameter)
//{
//	CProgressCtrl *Speed = (CProgressCtrl*)lpParameter;
//
//	Speed->SetRange(0, 100000); //���ý������ķ�Χ     
//	for (int i = 0; i < 100000; i++)
//	{
//		Speed->SetPos(i); //��������λ��  
//	}
//
//	return 0;
//}
//
//DWORD WINAPI CzhuweiView::ThreadReadFile(LPVOID lpParameter)
//{
//	//ʹ��CStdioFile��Ĺ��캯�����ж����ı�����
//	CStdioFile file(filePath, CFile::modeRead);
//	CString strNowLine;		//��ǰ���������е�����
//	CString strOneWord;		//��ǰ������oneLineString�е�ǰ�������������֮�������
//	int curPos;		//���ڴ����һ�������У���ǰ��������λ���Ǳ����еĵ�curPos���ַ�
//	int intLineNum = 0;	//ListControl�ؼ���������ʾ�������
//	CString strLineNum;	//��lineNumת����CString���ͱ�����ListControl����ʾ
//	std::vector<CString> nowLineVector;		//��ǰ��������ʱ�洢������
//
//	while (file.ReadString(strNowLine))
//	{
//		curPos = 0;
//		//��int�͵�lineNumת��ΪCString�͵�strLineNum
//		strLineNum.Format(_T("%d"), intLineNum + 1);
//
//		//��ListControl����ʾ����
//		m_page1.m_listControl.InsertItem(intLineNum, _T(""));
//		m_page1.m_listControl.SetItemText(intLineNum, 0, strLineNum);
//		m_page1.m_listControl.SetItemText(intLineNum, 1, strNowLine);
//		intLineNum++;
//		//ȡ����һ������ǰ������
//		strOneWord = strNowLine.Tokenize(_T(","), curPos);
//
//		while (strOneWord != "")
//		{
//			//��ȡ�������ݷŵ���ǰ��������ʱ�洢��������
//			nowLineVector.push_back(strOneWord);
//			//ȡ��һ������ǰ������
//			strOneWord = strNowLine.Tokenize(_T(","), curPos);
//		}
//
//		//��ǰ�����������ϣ���ȡ�������ݷŵ���������
//		m_allFileVector.push_back(nowLineVector);
//		nowLineVector.clear();
//	}
//	return 0;
//}