// Page1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "zhuwei.h"
#include "Page1.h"
#include "afxdialogex.h"
#include <algorithm>
#include"CSeries.h"

// CPage1 �Ի���

IMPLEMENT_DYNAMIC(CPage1, CDialog)

//��ȡ�ļ��߳�
DWORD WINAPI ThreadReadFile(LPVOID lpParameter);
//��ʾ���������߳�
DWORD WINAPI ThreadDisplayAllData(LPVOID lpParameter);

std::vector<std::vector<CString>> allFileVector;

CPage1::CPage1(CWnd* pParent /*=NULL*/)
	: CDialog(CPage1::IDD, pParent)
	, m_nRadio(0)
	, m_DataName(_T(""))
	, m_switchPaintName(0)
	, m_switchPaint(0)
{
	m_brush_cp1.CreateSolidBrush(RGB(69, 71, 72));//������ɫ
}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listControl);
	DDX_Control(pDX, IDC_PROGRESS1, m_speed);
	//	DDX_Control(pDX, IDC_PICSHOW, m_PicCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_EDIT2, m_fileName);
	DDX_Control(pDX, IDC_TCHART1, m_chart);
	DDX_Control(pDX, IDC_EDIT3, m_dataLineName);
}


BEGIN_MESSAGE_MAP(CPage1, CDialog)
//	ON_WM_CTLCOLOR()
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CPage1::OnLvnItemchangedList2)
	ON_BN_CLICKED(IDC_RADIO1, &CPage1::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CPage1::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CPage1::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CPage1::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON2, &CPage1::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPage1::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPage1::OnBnClickedButton4)
END_MESSAGE_MAP()


// CPage1 ��Ϣ�������


BOOL CPage1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//ΪListControl�ؼ���ӱ�ͷ
	m_listControl.InsertColumn(0, L"���", LVCFMT_LEFT, 50);
	m_listControl.InsertColumn(1, L"������ʾ", LVCFMT_LEFT, 500);

	//��ʼ״̬��������ȡĬ��һ��������ȡ
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO3)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO4)->EnableWindow(FALSE);

	//һ�����ݳ�ʼ��
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("Heading/�����"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("Pitch/��ҡ��"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("Roll/�����"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("GPS Latitude/γ��"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("GPS Longitude/����"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("GPS Position/��λ"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("COG/�Եغ���"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("SOG/�Եغ���"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("GPS UTC/����Э��ʱ"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);

	//�������ݳ�ʼ��
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("AT2"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("POS"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("SAT"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("SA4"));
	((CComboBox*)GetDlgItem(IDC_COMBO4))->EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CPage1::readFile()
{
	HANDLE hThreadReadFile;

	hThreadReadFile = CreateThread(NULL, 0, ThreadReadFile, this, 0, NULL);
	CloseHandle(hThreadReadFile);
}

DWORD WINAPI ThreadReadFile(LPVOID lpParameter)
{
	CPage1* page1 = (CPage1*)lpParameter;
	//TRUE��ʾ��
	CFileDialog fileDlg(true);

	//���öԻ����������
	fileDlg.m_ofn.lpstrTitle = L"ѡ�񴬲�����";

	//��ʽ������
	fileDlg.m_ofn.lpstrFilter = L"Log Files(*.log)\0*.log\0Txt Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";

	//��ʾ�ļ��Ի���,���ж϶Ի����Ƿ�������
	if (fileDlg.DoModal() == TRUE)
	{
		//��ȡ�ļ���
		CString m_File = fileDlg.GetFileName();
		//��ʾ����ȡ���ļ���
		page1->m_fileName.SetWindowTextW(m_File);

		//��ȡ�����ļ�������·��filePath
		CString filePath = fileDlg.GetPathName();

		//��ʼ���ļ��ܴ�С�͵�ǰ�Ѿ���ȡ�Ĵ�С
		double fileSize = 0;
		double nowReadSize = 0;

		//��ȡ���ļ��Ĵ�С
		CFileStatus fileStatus;
		if (CFile::GetStatus(filePath, fileStatus))
		{
			fileSize = fileStatus.m_size;
		}

		page1->m_speed.SetRange(0, 1000); //���ý������ķ�Χ 

		//����������ǰ�����ListControl�ؼ��е�����
		page1->m_listControl.DeleteAllItems();

		//ʹ��CStdioFile��Ĺ��캯�����ж����ı�����
		CStdioFile file(filePath, CFile::modeRead);
		CString strNowLine;		//��ǰ���������е�����
		CString strOneWord;		//��ǰ������oneLineString�е�ǰ�������������֮�������
		CString strNumber;		//��ǰ�Ķ�ȡ����
		int curPos;		//���ڴ����һ�������У���ǰ��������λ���Ǳ����еĵ�curPos���ַ�
		int intLineNum = 0;	//ListControl�ؼ���������ʾ�������
		CString strLineNum;	//��lineNumת����CString���ͱ�����ListControl����ʾ
		std::vector<CString> nowLineVector;		//��ǰ��������ʱ�洢������

		//��������е�����
		page1->m_allFileVector.clear();
		page1->m_allFileLineVector.clear();
		allFileVector.clear();

		//�������ݲ���ʾ��ControlList�ؼ���
		while (file.ReadString(strNowLine))
		{
			curPos = 0;
			//��int�͵�lineNumת��ΪCString�͵�strLineNum
			strLineNum.Format(_T("%d"), intLineNum + 1);

			//��ListControl����ʾ����
			page1->m_listControl.InsertItem(intLineNum, _T(""));
			page1->m_listControl.SetItemText(intLineNum, 0, strLineNum);
			page1->m_listControl.SetItemText(intLineNum, 1, strNowLine);

			//��ȡ��ǰ����Ĵ�С
			//nowReadSize += (strNowLine.GetLength() + 2);
			nowReadSize += (strNowLine.GetLength() + 1);
			page1->m_speed.SetPos(1000 * (nowReadSize / fileSize));

			//�ٷֺ���ʾ��ȡ����
			strNumber.Format(_T("%3.2f"), (double)(100 * (nowReadSize / fileSize)));
			page1->m_edit.SetWindowTextW(strNumber + "%");

			intLineNum++;

			//����д����������
			page1->m_allFileLineVector.push_back(strNowLine);
			//ȡ����һ������ǰ������
			strOneWord = strNowLine.Tokenize(_T(","), curPos);

			while (strOneWord != "")
			{
				//��ȡ�������ݷŵ���ǰ��������ʱ�洢��������
				nowLineVector.push_back(strOneWord);
				//ȡ��һ������ǰ������
				strOneWord = strNowLine.Tokenize(_T(","), curPos);
			}

			//��ǰ�����������ϣ���ȡ�������ݷŵ���������
			page1->m_allFileVector.push_back(nowLineVector);

			nowLineVector.clear();

		}
		page1->m_speed.SetPos(1000);
		page1->m_edit.SetWindowTextW(L"100%");

		//��ȫ�����ݸ�ȫ������allFileVector�����������߳�ʹ��
		allFileVector = page1->m_allFileVector;

		return 0;
	}
	else
		return 0;
}

void CPage1::progress()
{
	CProgressCtrl *myProCtrl = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);
	myProCtrl->SetRange(0, 100);
	for (int i = 0; i<100; i++)
	{
		//myProCtrl2->OffsetPos(1); //�˾�����ͬ�������䣬�Թ̶�����1������ʾ���ù���Ҳ��������ʵ�֣�myProCtrl2->SetPos(i); 
		myProCtrl->SetStep(1);
		myProCtrl->StepIt();
		Sleep(100);
	}
}

void CPage1::OnBnClickedRadio1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_nRadio = 0;
	if (m_nRadio == 0)
	{
		GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO3)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO4)->EnableWindow(FALSE);
	}

}


void CPage1::OnBnClickedRadio2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_nRadio = 1;
	if (m_nRadio == 1)
	{
		GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO3)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO4)->EnableWindow(TRUE);
	}
}

//������������ȡ
void CPage1::selectFileData(CString strIndex, int ip)
{
	m_selectDataVector.clear();
	for (int i = 0; i < m_allFileVector.size(); i++)
	{
		if (m_allFileVector[i][1] == strIndex)
			m_selectDataVector.push_back(m_allFileVector[i][ip]);
	}
}

//������������ȡ
void CPage1::selectFileData(CString strIndex, int ip, int ic)
{
	m_selectDataVector.clear();
	for (int i = 0; i < m_allFileVector.size(); i++)
	{
		if (m_allFileVector[i][1] == strIndex)
			m_selectDataVector.push_back(m_allFileVector[i][ip] + m_allFileVector[i][ic]);
	}
}

//����һ������ȡʱ������ѡ��������ֶΣ�ȷ�����ŵĸ���
void CPage1::OnCbnSelchangeCombo3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	((CComboBox*)GetDlgItem(IDC_COMBO4))->ResetContent();	//���ԭ������
	int index = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();	//��ǰѡ�е���
	((CComboBox*)GetDlgItem(IDC_COMBO4))->EnableWindow(true);
	switch (index)
	{
	case 0:
		for (int i = 0; i < 12; i++)
		{
			CString strtemp;
			strtemp.Format(_T("%d"), i);
			((CComboBox*)GetDlgItem(IDC_COMBO4))->AddString(strtemp);
		}
		break;

	case 1:
		for (int i = 0; i < 19; i++)
		{
			CString strtemp;
			strtemp.Format(_T("%d"), i);
			((CComboBox*)GetDlgItem(IDC_COMBO4))->AddString(strtemp);
		}
		break;

	case 2:
		for (int i = 0; i < 57; i++)
		{
			CString strtemp;
			strtemp.Format(_T("%d"), i);
			((CComboBox*)GetDlgItem(IDC_COMBO4))->AddString(strtemp);
		}
		break;

	case 3:
		for (int i = 0; i < 20; i++)
		{
			CString strtemp;
			strtemp.Format(_T("%d"), i);
			((CComboBox*)GetDlgItem(IDC_COMBO4))->AddString(strtemp);
		}
		break;
	}
}

//��ȡ����
void CPage1::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (CPage1::m_nRadio == 0)
	{
		m_switchPaintName = 0;//������������ȡʱ����ʾ����ȡ����������
		m_switchPaint = 1;//���Խ��л����߲���
		int index = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetLBText(index, m_DataName);
		if (m_DataName == _T("Heading/�����"))
			selectFileData(_T("AT2"), 3);
		if (m_DataName == _T("Pitch/��ҡ��"))
			selectFileData(_T("AT2"), 4);
		if (m_DataName == _T("Roll/�����"))
			selectFileData(_T("AT2"), 5);
		if (m_DataName == _T("GPS Latitude/γ��"))
			selectFileData(_T("POS"), 5, 6);
		if (m_DataName == _T("GPS Longitude/����"))
			selectFileData(_T("POS"), 7, 8);
		if (m_DataName == _T("GPS Position/��λ"))
			selectFileData(_T("POS"), 9);
		if (m_DataName == _T("COG/�Եغ���"))
			selectFileData(_T("POS"), 11);
		if (m_DataName == _T("SOG/�Եغ���"))
			selectFileData(_T("POS"), 12);
		if (m_DataName == _T("GPS UTC/����Э��ʱ"))
			selectFileData(_T("POS"), 4);
	}
	else
	{
		m_switchPaintName = 1;//�Զ�����ȡʱ����ʾ��������
		CString strIndex;
		CString temp;
		int index = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO3))->GetLBText(index, strIndex);
		GetDlgItemText(IDC_COMBO4, temp);
		int iTemp = _ttoi(temp);
		selectFileData(strIndex, iTemp);
	}

	//��û�ж�������ʱ�����Ի���
	if (m_selectDataVector.empty())
	{
		MessageBox(_T("���ȶ�������"));
	}

	//���ListControl�ؼ���׼��д����ȡ��������
	m_listControl.DeleteAllItems();
	int intLineNum = 0;		//ListControl�ؼ������ݵ����
	for (int i = 0; i < m_selectDataVector.size(); i++)
	{
		CString strLineNum;		//ListControl�ؼ������ݵ����intLineNumװ��ΪCString
		strLineNum.Format(_T("%d"), intLineNum + 1);
		m_listControl.InsertItem(i, _T(""));
		m_listControl.SetItemText(i, 0, strLineNum);
		m_listControl.SetItemText(i, 1, m_selectDataVector[i]);
		intLineNum++;
	}
}

//���ݴ���
void CPage1::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_selectDataVector.empty())
	{
		MessageBox(_T("����ȡ�������ݺ󱣴�"));
		return;
	}
	CFileDialog FileDlg(false, _T("txt"), NULL, OFN_OVERWRITEPROMPT, NULL, this);

	if (FileDlg.DoModal() == TRUE)
	{
		CString FilePath = FileDlg.GetPathName();
		CStdioFile DataFile(FilePath, CFile::modeWrite | CFile::modeCreate);
		CString str;
		for (int i = 0; i < m_selectDataVector.size(); i++)
		{
			str = m_selectDataVector[i] + L"\r\n";
			DataFile.WriteString(str);
		}
		DataFile.Close();
	}
	else
		return;
}

//����ͼ��
void CPage1::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_allFileVector.empty())
	{
		MessageBox(_T("��������ݲ���ȡ"));
		return ;
	}

	if (m_switchPaint == 0)
	{
		MessageBox(_T("������ȡ����"));
		return;
	}

	//����"��ʾ����:"���Ƿ���ʾ��������
	if (m_switchPaintName == 0)
		m_dataLineName.SetWindowTextW(m_DataName);
	else
		m_dataLineName.SetWindowTextW(L"");

	//ʹ��TeeChart����ͼ��
	CSeries lineSeries = (CSeries)m_chart.Series(0);
	lineSeries.Clear();
	for (int i = 0; i<m_selectDataVector.size(); i++)
	{
		double rand = _wtof(m_selectDataVector[i].GetBuffer(0));
		lineSeries.AddXY((double)i, rand, NULL, NULL);
	}

}

//��ʾ��������
void CPage1::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//����Ƿ��ȶ���������
	if (m_allFileVector.empty())
	{
		MessageBox(_T("���ȶ�������"));
		return;
	}

	//���listControl�ؼ�
	m_listControl.DeleteAllItems();
	//��հٷֱ���ʾ
	m_edit.SetWindowTextW(L"");
	//�����ʾ���������߳̾��
	HANDLE hThreadDisplayAllData;
	//������ʾ�������ݵ��߳�
	hThreadDisplayAllData = CreateThread(NULL, 0, ThreadDisplayAllData, this, 0, NULL);
	CloseHandle(hThreadDisplayAllData);

	/*int intLineNum = 0;		//ListControl�ؼ������ݵ����
	CString strarray;		//ת��ΪCString������
	for (int i = 0; i < m_allFileLineVector.size(); i++)
	{
		strarray.Format(_T("%d"), intLineNum + 1);
		m_listControl.InsertItem(i, _T(""));
		m_listControl.SetItemText(i, 0, strarray);
		m_listControl.SetItemText(i, 1, m_allFileLineVector[i]);
		intLineNum++;
	}*/
}

DWORD WINAPI ThreadDisplayAllData(LPVOID lpParameter)
{
	CPage1* page1 = (CPage1*)lpParameter;
	int intLineNum = 0;		//ListControl�ؼ������ݵ����
	CString strarray;		//ת��ΪCString������

	double fileSize = 0;	//�����ܴ�С
	double m = 0;			//�������Ĳ���

	fileSize = allFileVector.size();	//��������ܴ�С

	page1->m_speed.SetRange(0, allFileVector.size()); //���ý������ķ�Χ

	for (int i = 0; i < allFileVector.size(); i++)
	{
		//�б�ؼ�������ʾ
		strarray.Format(_T("%d"), intLineNum + 1);
		page1->m_listControl.InsertItem(i, _T(""));
		page1->m_listControl.SetItemText(i, 0, strarray);
		page1->m_listControl.SetItemText(i, 1, page1->m_allFileLineVector[i]);
		intLineNum++;
		//��������ʾ
		page1->m_speed.SetPos(i);
	}
	page1->m_speed.SetPos(allFileVector.size());
	return 0;
}