
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

#define UM_PROGRESS WM_USER+1	//定义状态栏消息


class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	
public:
	CStatusBar        m_wndStatusBar;	// 状态栏相关变量

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	DECLARE_MESSAGE_MAP()

public:
	//状态栏消息响应函数原型声明
	afx_msg LRESULT OnProgress(WPARAM wParam, LPARAM lParam);
	// 进度栏变量
	CProgressCtrl m_progress;
	//设置定时器
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


