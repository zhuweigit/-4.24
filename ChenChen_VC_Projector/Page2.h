#pragma once
#include "afxcmn.h"
#include "Page1.h"
#include "tchart1.h"

// CPage2 �Ի���

class CPage2 : public CDialog
{
	DECLARE_DYNAMIC(CPage2)

public:
	CPage2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPage2();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	// ��γ��������ȡ
	CListCtrl m_listControl;

	//��������
	std::vector<CString> m_POS_1_Vector;
	//γ������
	std::vector<CString> m_POS_2_Vector;
	//��γ����ȡ����
	void selectFileData(CString strIndex, int ip);
	// ����������
	CProgressCtrl m_progress;
	// TeeChart�ؼ�����
	CTchart1 m_chart;
	afx_msg void OnBnClickedButton2();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
