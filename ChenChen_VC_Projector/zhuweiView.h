
// zhuweiView.h : CzhuweiView 类的接口
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
protected: // 仅从序列化创建
	CzhuweiView();
	DECLARE_DYNCREATE(CzhuweiView)

public:
	enum{ IDD = IDD_CHENCHEN_VC_PROJECTOR_FORM };

// 特性
public:
	CzhuweiDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CzhuweiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	// 与对话框中的Tab Control控件交互
	CTabCtrl m_tab;
	// 选择是哪个Page即将被切换
	int m_CurSelTab;
	//定义CPage变量
	CPage1 m_page1;
	CPage2 m_page2;
	CPage3 m_page3;
	CPage4 m_page4;
	CPage5 m_page5;
	//用来保存对话框对象指针
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
	
public:
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnFileOpen();

public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	CStatusBar m_wndStatusBar;	// 状态栏相关变量
	CProgressCtrl m_progress;	// 工具栏中的进度栏变量

	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // zhuweiView.cpp 中的调试版本
inline CzhuweiDoc* CzhuweiView::GetDocument() const
   { return reinterpret_cast<CzhuweiDoc*>(m_pDocument); }
#endif

