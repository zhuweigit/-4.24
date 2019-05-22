
// zhuweiView.h : CzhuweiView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include"Page1.h"
#include"Page2.h"
#include"Page3.h"
#include"Page4.h"
#include"Page5.h"
#include "afxwin.h"
#include<vector>
#include "afxext.h"

class CzhuweiView : public CFormView
{
protected: // �������л�����
	CzhuweiView();
	DECLARE_DYNCREATE(CzhuweiView)

public:
	enum{ IDD = IDD_CHENCHEN_VC_PROJECTOR_FORM };

// ����
public:
	CzhuweiDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CzhuweiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	// ��Ի����е�Tab Control�ؼ�����
	CTabCtrl m_tab;
	// ѡ�����ĸ�Page�������л�
	int m_CurSelTab;
	//����CPage����
	CPage1 m_page1;
	CPage2 m_page2;
	CPage3 m_page3;
	CPage4 m_page4;
	CPage5 m_page5;
	//��������Ի������ָ��
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
	
public:
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnFileOpen();

public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	CStatusBar m_wndStatusBar;	// ״̬����ر���
	CProgressCtrl m_progress;	// �������еĽ���������

	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // zhuweiView.cpp �еĵ��԰汾
inline CzhuweiDoc* CzhuweiView::GetDocument() const
   { return reinterpret_cast<CzhuweiDoc*>(m_pDocument); }
#endif

