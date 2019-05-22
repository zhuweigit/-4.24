
// MainFrm.cpp : CMainFrame 类的实现
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
	ON_MESSAGE(UM_PROGRESS, &OnProgress)	//映射关联进度栏消息和其消息响应函数
	ON_WM_TIMER()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//启动画面
	CSplashWnd::ShowSplashScreen(this);
	Sleep(3000);

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//得到显示器大小
	int   cx, cy;
	cx = GetSystemMetrics(SM_CXSCREEN);
	cy = GetSystemMetrics(SM_CYSCREEN);
	//再用MoveWindow，初始化窗口大小以及所在位置
	CRect   rcTemp;
	rcTemp.BottomRight() = CPoint(cx, cy);			//获得右下角点
	rcTemp.TopLeft() = CPoint(cx / 10, cy / 15);	//获得左上角点
	MoveWindow(&rcTemp);

//	SetTimer(1, 1000, NULL);

//	PostMessage(UM_PROGRESS);	//发送进度栏消息

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	//固定窗口的大小
	cs.style &= ~WS_MAXIMIZEBOX;	//使最大化按钮无效
	cs.style &= ~WS_THICKFRAME;		//使窗口不能鼠标拖动改变大小
	/*cs.cx = 500;
	cs.cy = 500;*/

	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序

LRESULT CMainFrame::OnProgress(WPARAM wParam, LPARAM lParam)
{
	//显示进度栏
	CRect rect;
	m_wndStatusBar.GetItemRect(2, &rect);	//进度栏位置
	m_progress.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTH, rect, &m_wndStatusBar, 123);	//创建进度栏
//	m_progress.SetPos(50);	//进度条的初始进度

	return TRUE;
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
//	m_progress.StepIt();
	CFrameWnd::OnTimer(nIDEvent);
}
