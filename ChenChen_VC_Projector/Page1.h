#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include<vector>
#include "tchart1.h"

// CPage1 �Ի���
extern std::vector<std::vector<CString>> allFileVector;

class CPage1 : public CDialog
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPage1();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	// ������ȡģ��ı�����ɫ
	CBrush m_brush_cp1;
public:
//	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	// ListControl�ؼ��ı���
	CListCtrl m_listControl;

public:
	//��ȡѡ���ļ�
	void readFile();
	//����������
	void progress();
	//������ȡ����
	void selectFileData(CString strIndex, int ip, int ic);
	//������ȡ����
	void selectFileData(CString strIndex, int ip);

	//m_allFileData��ά�����洢�������ļ���ȫ������
	std::vector<std::vector<CString>> m_allFileVector;
	//m_allFileLineVector���е���ʽ�洢�����ļ���ȫ������
	std::vector <CString> m_allFileLineVector;
	//m_selectDataVector�������水Ҫ����ȡ����ȫ������
	std::vector<CString> m_selectDataVector;
	// �������ؼ�����
	CProgressCtrl m_speed;

	// ���ƴ��ĸ���ѡ�ؼ�	// ���ƴ��ĸ���ѡ�ؼ�
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
private:
	// ����ѡ������������ȡ��0��ʾһ��������ȡ��1��ʾ��һ������ȡ
	int m_nRadio;
public:
	afx_msg void OnBnClickedButton1();
	// ����Ҫ��ȡ���ݵĹؼ���
	CString m_DataName;
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	// ��ȡ���Ȱٷֱ���ʾ
	CEdit m_edit;
	// ���ļ����ļ���
	CEdit m_fileName;
	// ��ͼ�ؼ�TeeChart��������
	CTchart1 m_chart;
	// ���������ߵ���������
	CEdit m_dataLineName;
	//�������ߵ���������
	int m_switchPaintName;
	//�Ƿ��ܽ��л����߲���
	int m_switchPaint;
};
