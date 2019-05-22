// SplashWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "zhuwei.h"
#include "SplashWnd.h"


// CSplashWnd  
CSplashWnd* CSplashWnd::m_pSplashWnd;

IMPLEMENT_DYNAMIC(CSplashWnd, CWnd)

CSplashWnd::CSplashWnd()
{

}

CSplashWnd::~CSplashWnd()
{
	ASSERT(m_pSplashWnd == this);
	m_pSplashWnd = NULL;
}


BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CSplashWnd ��Ϣ�������  

void CSplashWnd::ShowSplashScreen(CWnd* pParentWnd)
{
	if (m_pSplashWnd != NULL) return;
	m_pSplashWnd = new CSplashWnd;
	if (!m_pSplashWnd->Create(pParentWnd))
		//������ʼ���洰��     
		delete m_pSplashWnd;
	else
		m_pSplashWnd->UpdateWindow();
	//��ʾ��ʼ���洰��
}

bool CSplashWnd::Create(CWnd* pParentWnd)
{
	if (!m_bitmap.LoadBitmap(IDB_BITMAP))
		//����λͼ     
		return FALSE;
	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	return CreateEx(0, AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, pParentWnd->GetSafeHwnd(), NULL);//��������ܴ��ڵ��Ӵ���  
}

int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CenterWindow();
	SetTimer(1, 1000, NULL); //ʱ�����     

	return 0;
}

void CSplashWnd::OnPaint()
{
	CPaintDC dc(this);
	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(&dc)) return;
	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmap);
}


void CSplashWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default  
	DestroyWindow(); //���ٳ�ʼ���洰��     
	AfxGetMainWnd()->UpdateWindow();
	CWnd::OnTimer(nIDEvent);
}

void CSplashWnd::PostNcDestroy(void)
{
	DestroyWindow();
	CWnd::PostNcDestroy();
}