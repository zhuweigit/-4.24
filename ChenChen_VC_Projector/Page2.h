#pragma once
#include "afxcmn.h"
#include "Page1.h"
#include "tchart1.h"

// CPage2 对话框

class CPage2 : public CDialog
{
	DECLARE_DYNAMIC(CPage2)

public:
	CPage2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPage2();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	// 经纬度数据提取
	CListCtrl m_listControl;

	//经度容器
	std::vector<CString> m_POS_1_Vector;
	//纬度容器
	std::vector<CString> m_POS_2_Vector;
	//经纬度提取函数
	void selectFileData(CString strIndex, int ip);
	// 进度条变量
	CProgressCtrl m_progress;
	// TeeChart控件变量
	CTchart1 m_chart;
	afx_msg void OnBnClickedButton2();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
