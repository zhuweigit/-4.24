
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "zhuwei.h"

#include "MainFrm.h"
#include "SplashWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE(UM_PROGRESS, &OnProgress)	//ӳ�������������Ϣ������Ϣ��Ӧ����
	ON_WM_TIMER()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//��������
	CSplashWnd::ShowSplashScreen(this);
	Sleep(3000);

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//�õ���ʾ����С
	int   cx, cy;
	cx = GetSystemMetrics(SM_CXSCREEN);
	cy = GetSystemMetrics(SM_CYSCREEN);
	//����MoveWindow����ʼ�����ڴ�С�Լ�����λ��
	CRect   rcTemp;
	rcTemp.BottomRight() = CPoint(cx, cy);			//������½ǵ�
	rcTemp.TopLeft() = CPoint(cx / 10, cy / 15);	//������Ͻǵ�
	MoveWindow(&rcTemp);

//	SetTimer(1, 1000, NULL);

//	PostMessage(UM_PROGRESS);	//���ͽ�������Ϣ

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	//�̶����ڵĴ�С
	cs.style &= ~WS_MAXIMIZEBOX;	//ʹ��󻯰�ť��Ч
	cs.style &= ~WS_THICKFRAME;		//ʹ���ڲ�������϶��ı��С
	/*cs.cx = 500;
	cs.cy = 500;*/

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

LRESULT CMainFrame::OnProgress(WPARAM wParam, LPARAM lParam)
{
	//��ʾ������
	CRect rect;
	m_wndStatusBar.GetItemRect(2, &rect);	//������λ��
	m_progress.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTH, rect, &m_wndStatusBar, 123);	//����������
//	m_progress.SetPos(50);	//�������ĳ�ʼ����

	return TRUE;
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	m_progress.StepIt();
	CFrameWnd::OnTimer(nIDEvent);
}
