
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

#define UM_PROGRESS WM_USER+1	//����״̬����Ϣ


class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	
public:
	CStatusBar        m_wndStatusBar;	// ״̬����ر���

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	DECLARE_MESSAGE_MAP()

public:
	//״̬����Ϣ��Ӧ����ԭ������
	afx_msg LRESULT OnProgress(WPARAM wParam, LPARAM lParam);
	// ����������
	CProgressCtrl m_progress;
	//���ö�ʱ��
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


