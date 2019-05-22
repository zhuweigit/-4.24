#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include<vector>
#include "tchart1.h"

// CPage1 对话框
extern std::vector<std::vector<CString>> allFileVector;

class CPage1 : public CDialog
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPage1();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	// 数据提取模块的背景颜色
	CBrush m_brush_cp1;
public:
//	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	// ListControl控件的变量
	CListCtrl m_listControl;

public:
	//读取选中文件
	void readFile();
	//进度条函数
	void progress();
	//数据提取函数
	void selectFileData(CString strIndex, int ip, int ic);
	//数据提取函数
	void selectFileData(CString strIndex, int ip);

	//m_allFileData二维容器存储所所打开文件的全部内容
	std::vector<std::vector<CString>> m_allFileVector;
	//m_allFileLineVector以行的形式存储所打开文件的全部内容
	std::vector <CString> m_allFileLineVector;
	//m_selectDataVector容器保存按要求提取出的全部数据
	std::vector<CString> m_selectDataVector;
	// 进度栏控件变量
	CProgressCtrl m_speed;

	// 控制打开哪个单选控件	// 控制打开哪个单选控件
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
private:
	// 控制选择哪种数据提取，0表示一般数据提取，1表示任一数据提取
	int m_nRadio;
public:
	afx_msg void OnBnClickedButton1();
	// 所需要提取数据的关键字
	CString m_DataName;
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	// 读取进度百分比显示
	CEdit m_edit;
	// 打开文件的文件名
	CEdit m_fileName;
	// 绘图控件TeeChart关联变量
	CTchart1 m_chart;
	// 所绘制曲线的数据名称
	CEdit m_dataLineName;
	//所画曲线的数据名称
	int m_switchPaintName;
	//是否能进行画曲线操作
	int m_switchPaint;
};
