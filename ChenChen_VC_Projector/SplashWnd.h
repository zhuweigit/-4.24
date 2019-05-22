#pragma once


// CSplashWnd

class CSplashWnd : public CWnd
{
	DECLARE_DYNAMIC(CSplashWnd)

public:
	CSplashWnd();
	virtual ~CSplashWnd();
	virtual void PostNcDestroy();


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()


protected:
	static CSplashWnd* m_pSplashWnd;//ָ���ʼ�����ָ��  
	bool Create(CWnd* pParentWnd);

public:
	CBitmap m_bitmap;//��ʼ����λͼ   
	static void ShowSplashScreen(CWnd* pParentWnd);
};

