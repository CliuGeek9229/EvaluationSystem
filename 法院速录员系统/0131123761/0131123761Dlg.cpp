// 0131123761Dlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "0131123761.h"
#include "0131123761Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

//===============================================
#include"Mmsystem.h"
#pragma   comment(lib, "winmm.lib")

MCI_OPEN_PARMS op;

void  CMy0131123761Dlg::OnPlay(int TestNumber) 
 {
  // TODO: Add your control notification handler code here
  DWORD cdlen ;//��Ƶ�ļ�����
  
  //��ȡ��ǰѡ�������ѡ��ı䵱ǰ��������
  CString str;
  str.Format(_T(".\\MusicDoc\\%d.mp3"),TestNumber);

 op.dwCallback=NULL; 
  op.lpstrAlias=NULL; 
  op.lpstrDeviceType=_T("MPEGAudio");  //�豸���ͣ�������ļ������������� 
 op.lpstrElementName=str; //�ļ�·�� 
 op.wDeviceID=NULL;      //���豸�ɹ��Ժ󱣴�����豸�ű��� 
 UINT rs;        //���ܺ������ؽ�� 
 //����������豸���ɹ�����0�����򷵻ش���ţ������������������MCI_OPEN_ELEMENT  
  rs=mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)&op);

 mciSendCommand(NULL,MCI_SET,MCI_SET_DOOR_OPEN,NULL); 

 cdlen=getinfo(op.wDeviceID,MCI_STATUS_LENGTH);//��ȡ��Ƶ�ļ�����

 m_hour = (int)cdlen/3600000;
 m_minute = (int)cdlen/60000;
 m_second = (int)cdlen%60000/1000;

 if(rs==0)        //�豸�򿪳ɹ��Ͳ����ļ� 
 { 
   MCI_PLAY_PARMS pp; 
   pp.dwCallback=NULL; 
   pp.dwFrom=0;      //��ʼ���ŵ�λ�� 
  mciSendCommand(op.wDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)&pp);
   //�����ļ������������������ΪMCI_WAIT����򴰿ڻᱻ������Ϊ�˱����������������ΪMCI_NOTIFY 
  }

 //Sleep(cdlen);//�����ļ����ȵȴ�����MCI_WAITЧ��һ����cdlen�������Կ��Ʋ���ʱ��
 //OnStop();        //�ر���Ƶ�ļ� 
 }

DWORD  CMy0131123761Dlg::getinfo(UINT wDeviceID,DWORD item)
 {
  MCI_STATUS_PARMS mcistatusparms;
  mcistatusparms.dwCallback=(DWORD)GetSafeHwnd();
  mcistatusparms.dwItem=item;
  mcistatusparms.dwReturn=0;
  mciSendCommand(wDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)&mcistatusparms);
  return mcistatusparms.dwReturn;
 }

void  CMy0131123761Dlg::OnStop() 
 {
  // TODO: Add your control notification handler code here
  //��WM_CLOSE��Ϣ��������з���MCI_CLOSE����ر��豸
 MCI_GENERIC_PARMS gp; 
  gp.dwCallback=NULL; 
  mciSendCommand(op.wDeviceID,MCI_CLOSE,MCI_WAIT,(DWORD)&gp);  
 }

void CMy0131123761Dlg::OnPause()
{
	MCI_PLAY_PARMS PlayParms;
	mciSendCommand (op.wDeviceID,MCI_PAUSE, 0,(DWORD)(LPVOID) &PlayParms);
}
void CMy0131123761Dlg::OnResume()
{
	MCI_PLAY_PARMS PlayParms;
	mciSendCommand(op.wDeviceID, MCI_RESUME, 0, (DWORD)(LPVOID)&PlayParms);
}
//===============================================

//===============================================
//pdf�ļ�д��
//if(())



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMy0131123761Dlg �Ի���




CMy0131123761Dlg::CMy0131123761Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy0131123761Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	//  m_MyEdit2 = _T("");
	//  m_MyEdit3 = _T("");
	//  m_MyEdit4Value = _T("");
	//  m_MyEdit6Value = _T("");

	/*m_second = 30;
	m_minute = 15;
	m_hour = 0;*/
	m_MyEdit6Value = _T("");
	m_MyEdit2 = _T("");
	m_MyEdit3 = _T("");

	//<<��ȡ��Ϣ�洢
	total_minutes = 0;
	total_questions = 0;
	audio_format = _T("");
	max_speed = 0;
	percentage_accuracy = _T("");
	percentage_speed = _T("");
	//>>
	m_MyEdit4Value = _T("");

	//<<��¼������ʱ
	m_TotalTime = 0;
	//>>
	accuracy =0.0f;
	speed = 0.0f;
	score = 0.0f;
	//<<����һ��setFocusEdit6
	m_Judgement = true;
	//>>
	//<<PDF��ʼ��
	p = NULL;
	i1 = 0;
	j1 = 0;
	Left = 50;
	Top = 800;
}

void CMy0131123761Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_MyCombo2);
	DDX_Control(pDX, IDC_BUTTON1, m_MyButton1);
	//  DDX_Text(pDX, IDC_EDIT2, m_MyEdit2);
	//  DDX_Text(pDX, IDC_EDIT3, m_MyEdit3);
	//  DDX_Control(pDX, IDC_EDIT4, m_MyEdit4Ctrl);
	//  DDX_Text(pDX, IDC_EDIT4, m_MyEdit4Value);
	//  DDX_Control(pDX, IDC_EDIT6, m_MyEdit6Ctrl);
	//  DDX_Text(pDX, IDC_EDIT6, m_MyEdit6Value);
	DDX_Text(pDX, IDC_EDIT6, m_MyEdit6Value);
	DDX_Text(pDX, IDC_EDIT2, m_MyEdit2);
	DDV_MaxChars(pDX, m_MyEdit2, 11);
	DDX_Text(pDX, IDC_EDIT3, m_MyEdit3);
	DDV_MaxChars(pDX, m_MyEdit3, 18);
	DDX_Text(pDX, IDC_STATIC1, m_MyEdit4Value);
	DDX_Control(pDX, IDC_STATIC1, m_MyEdit4Ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_MyEdit2Ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_MyEdit3Ctrl);
}

BEGIN_MESSAGE_MAP(CMy0131123761Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy0131123761Dlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT6, &CMy0131123761Dlg::OnEnChangeEdit6)
	ON_WM_CHAR()
	ON_BN_CLICKED(IDOK, &CMy0131123761Dlg::OnBnClickedOk)
	ON_EN_SETFOCUS(IDC_EDIT6, &CMy0131123761Dlg::OnEnSetfocusEdit6)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, &CMy0131123761Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMy0131123761Dlg ��Ϣ�������

BOOL CMy0131123761Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//<<====================================================�ļ�����======================================================
	total_questions = GetPrivateProfileInt(_T("ExamInfo"),_T("total_questions"),0,_T(".\\typist.ini"));
	for (int i = 0; i < total_questions; i++)
	{
		CString temp=_T(".\\AnswerDoc\\");
		CString turn;
		turn.Format(_T("%d"), i);
		temp += turn;
		temp += _T(".txt");
		int text=GetPrivateProfileInt(_T("Examanswer"),_T("sign"),0,temp);
		if (text == 1)
		{
			CString str;
			GetPrivateProfileString(_T("Examanswer"), _T("answer"), _T(""), str.GetBufferSetLength(4096), 4096, temp);
			str.ReleaseBuffer();
			char chLetter[4096];
			int i=0;
			for (; i < str.GetLength(); i++)
			{
				chLetter[i] = str.GetAt(i) +1;
			}
			chLetter[i] = '\0';
			str = chLetter;
			WritePrivateProfileString(_T("Examanswer"), _T("answer"), str, temp);
			str.Format(_T("%d"), 0);
			WritePrivateProfileString(_T("Examanswer"), _T("sign"), str, temp);
		}
	}


	//====================================================================================================================

	//cliu ComboBox
	CString str[5] = {_T("01"),_T("02"),_T("03"),_T("04"),_T("05")};
	int nIndex;
	for(int i = 0;i<5;i++)
	{
		nIndex = m_MyCombo2.AddString(str[i]);
		m_MyCombo2.SetItemData(nIndex,i);
	}
	m_MyCombo2.SetCurSel(0);


	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy0131123761Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy0131123761Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy0131123761Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
bool CMy0131123761Dlg::Number1Judge(CString str1,int n1)
{
	int i = 0;
	for(;i<n1;i++)
	{
		if(str1[i]<'0'||str1[i]>'9')
		{
			
			return false;
			break;
		}
	}

	return true;
}
bool CMy0131123761Dlg::Number2Judge(CString str2,int n2)
{
	int i = 0;
	for(;i<n2;i++)
	{
		if(str2[i]<'0'||str2[i]>'9')
		{
			
			return false;
			break;
		}
	}

	return true;
}
void CMy0131123761Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	//�ж�׼��֤���Լ����֤���Ƿ���ϱ�׼
	CString Registeration_number =m_MyEdit2;
	CString ID_number = m_MyEdit3;
	int Rlength = Registeration_number.GetLength();
	int IDlength = ID_number.GetLength();
	bool judge1 = Number1Judge(Registeration_number,Rlength);
	bool judge2 = Number2Judge(ID_number,IDlength);
	//��֤׼��֤�������֤���Ƿ�ƥ��

	//��ȡ��ǰѡ����
	int TestNumber = m_MyCombo2.GetCurSel();

	if(Rlength == 11 && IDlength == 18 && judge1 && judge2)
	{
		OnPlay(TestNumber);
		//UpdateData();
		
		m_MyEdit6Value = _T("���Կ�ʼ�ˣ���������ط�¼�����֡�����");
		UpdateData(false);

		total_minutes = GetPrivateProfileInt(_T("ExamInfo"),_T("total_minutes"),0,_T(".\\typist.ini"));
		total_questions = GetPrivateProfileInt(_T("ExamInfo"),_T("total_questions"),0,_T(".\\typist.ini"));
		GetPrivateProfileString(_T("ExamInfo"),_T("audio_format"),NULL,audio_format.GetBufferSetLength(20),20,_T(".\\typist.ini"));
		max_speed = GetPrivateProfileInt(_T("ExamInfo"),_T("max_speed"),0,_T(".\\typist.ini"));
		GetPrivateProfileString(_T("ExamInfo"),_T("percentage_accuracy"),NULL,percentage_accuracy.GetBufferSetLength(20),20,_T(".\\typist.ini"));
		GetPrivateProfileString(_T("ExamInfo"),_T("percentage_speed"),NULL,percentage_speed.GetBufferSetLength(20),20,_T(".\\typist.ini"));


		GetDlgItem(IDC_EDIT6)->EnableWindow(true);
		GetDlgItem(IDC_EDIT2)->EnableWindow(false);
		GetDlgItem(IDC_EDIT3)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
		GetDlgItem(IDC_COMBO2)->EnableWindow(false);
		GetDlgItem(IDOK)->EnableWindow(true);
		GetDlgItem(IDCANCEL)->EnableWindow(false);
		//<<�ı�����
		m_MyFont.CreatePointFont(150,_T("�����п�"));
		m_MyEdit4Ctrl.SetFont(&m_MyFont);
		//>>
		SetTimer(1,1000,0);
	}
	else
	{
		MessageBox(_T("�����º�ʵ���ĸ�����Ϣ"),_T("��Ϣ����"),0);
	}
}
void CMy0131123761Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData();
	if(m_second == 0 && m_minute == 0 && m_hour == 0)
	{
		GetDlgItem(IDC_EDIT6)->EnableWindow(false);
	}
	else
	{
		m_TotalTime++;
		if(m_second == 0)
		{
			m_second = 59;
			if(m_minute == 0)
			{
				m_hour--;
				m_minute = 59;
			}
			else
				m_minute--;
		}
		else
			m_second--;
	}
	CString m_strSecond;
	CString m_strMinute;
	CString m_strHour;
	if(m_hour<=9)
		m_strHour.Format(_T("0%d"),m_hour);
	else
		m_strHour.Format(_T("%d"),m_hour);
	if(m_minute<=9)
		m_strMinute.Format(_T("0%d"),m_minute);
	else
		m_strMinute.Format(_T("%d"),m_minute);
	if(m_second<=9)
		m_strSecond.Format(_T("0%d"),m_second);
	else
		m_strSecond.Format(_T("%d"),m_second);
	m_MyEdit4Value.Format(_T("\r\n����ʣ��ʱ��\r\n\r\n")+m_strHour+_T(":")+m_strMinute+_T(":")+m_strSecond);

	UpdateData(false);
	
	CDialogEx::OnTimer(nIDEvent);
}


void CMy0131123761Dlg::OnEnChangeEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	//m_MyEdit6Ctrl.Clear();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMy0131123761Dlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//UpdateData();
	CDialogEx::OnChar(nChar, nRepCnt, nFlags);
}


void CMy0131123761Dlg::OnBnClickedOk()
{
	UpdateData();
	OnPause();
		char *old_locale=_strdup(setlocale(LC_CTYPE,NULL));
	setlocale(LC_CTYPE,"chs");
	if(MessageBox(_T("�ύ֮�����ı��ο��Խ�������\r\n��ȷ���ύ��"),_T("��ʾ"),MB_ICONINFORMATION | MB_OKCANCEL) == IDOK)
	{
	OnStop();
	KillTimer(1);
	
	//<<��ȡ���ļ�(���ܶ��ļ�)===============================================================
	CString strRead;
	int CurrentSel = m_MyCombo2.GetCurSel();//��ȡ��ǰѡ����

	CString strTemp1 = _T(".\\AnswerDoc\\");
	CString CStr1;
	CStr1.Format(_T("%d"),CurrentSel);
	strTemp1 += CStr1;
	strTemp1 +=_T(".txt");

	char * old_locale = _strdup(setlocale(LC_CTYPE, NULL));
	setlocale(LC_CTYPE, "chs");

	GetPrivateProfileString(_T("Examanswer"), _T("answer"), _T(""),strRead.GetBufferSetLength(4096), 4096, strTemp1);
	strRead.ReleaseBuffer();
	char chLetter[4096];
	int i = 0;
	for (; i < strRead.GetLength(); i++)
	{
		chLetter[i] = strRead.GetAt(i) - 1;
	}
	chLetter[i] = '\0';
	strRead = chLetter;
	setlocale(LC_CTYPE, old_locale);
	//>>=====================================================================================
	
	//MessageBox(strRead,_T("asdfasdf"),0);

	
	int WordNumber = m_MyEdit6Value.GetLength();
	accuracy = Similarity(m_MyEdit6Value,strRead);
	accuracy = accuracy*100;
	float m_RealMinute = m_TotalTime/60.0;
	speed = WordNumber/m_RealMinute;
	max_speed = GetPrivateProfileInt(_T("ExamInfo"),_T("max_speed"),0,_T(".\\typist.ini"));
	GetPrivateProfileString(_T("ExamInfo"),_T("percentage_accuracy"),NULL,percentage_accuracy.GetBufferSetLength(20),20,_T(".\\typist.ini"));
	percentage_accuracy.ReleaseBuffer();
	GetPrivateProfileString(_T("ExamInfo"),_T("percentage_speed"),NULL,percentage_speed.GetBufferSetLength(20),20,_T(".\\typist.ini"));
	if(speed>max_speed)
	{
		speed = max_speed;
	} 

	double  Dpercentage_accuracy= atof(percentage_accuracy);  
	double  Dpercentage_speed= atof(percentage_speed);
	

	score = Dpercentage_accuracy*(accuracy)+Dpercentage_speed*speed;

	GetDlgItem(IDOK)->EnableWindow(false);
	//GetDlgItem(IDCANCEL)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_EDIT6)->EnableWindow(false);
	int m_Minute = m_TotalTime/60;
	int m_Second = m_TotalTime%60;
	m_MyEdit4Value.Format(_T("\r\n���Ŀ�������ʱ\r\n\r\n%d��%d��"),m_Minute,m_Second);
	UpdateData(false);
	}
	else
	{
		OnResume();
		//SetTimer(1);
	}
	setlocale(LC_CTYPE,old_locale);
}


void CMy0131123761Dlg::OnEnSetfocusEdit6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_Judgement)
	{
		m_MyEdit6Value =_T("");
		m_Judgement = false;
	}
	UpdateData(false);
}


HBRUSH CMy0131123761Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if(pWnd->GetDlgCtrlID()==IDC_STATIC1)
	{
		pDC->SetTextColor(RGB(0,0,255)); //����������ɫ
		//pDC->SetBkColor(RGB(255,0,0)); //���ñ���ɫ
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CMy0131123761Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDCANCEL)->EnableWindow(true);

	pdfFileJudgement();

	//UpdateData();
	//int m_Minute = m_TotalTime/60;
	//int m_Second = m_TotalTime%60;

	////<<�淶�������
	///*accuracy;
	//speed;
	//score;*/

	//CString m_temp;
	//CString a = _T("%");
	//m_temp.Format(_T("\r\n׼��֤�ţ�")+m_MyEdit2+_T("\r\n���֤�ţ�")+m_MyEdit3+_T("\r\n������ʱ��%d��%d��")+_T("\r\n�����ֵ�׼ȷ����%.2f")+_T("%%,�ٶ���%.2f����/���ӣ����ο��Գɼ���%.2f��")+_T("\r\n�����������ο���¼������ݣ�\r\n")+m_MyEdit6Value,m_Minute,m_Second,accuracy,speed,score);
	//MessageBox(m_temp,_T("��ӡ�ɼ���"),1);
}
int CMy0131123761Dlg::GetMin(int a,int b ,int c)
{
	int m_min;
	m_min = min(a,b);
	m_min = min(m_min, c);
	return m_min;
}

float CMy0131123761Dlg::Similarity(CString str1,CString str2)
{
	//���������ַ����ĳ���
	int len1 = str1.GetLength();
	int len2 = str2.GetLength();
	//�������飬���ַ����ȴ�һ���ռ�
	int **dif = new int *[len1+1];
	for(int i = 0;i<len1+1;i++)
	{
		dif[i] = new int [len2];
	}
	//����ֵ
	for(int a = 0;a<=len1;a++)
	{
		dif[a][0] = a;
	}
	for(int a = 0;a<=len2;a++)
	{
		dif[0][a] = a;
	}
	//���������ַ��Ƿ�һ�����������ϵ�ֵ
	int temp;
	for(int i = 1;i<=len1;i++)
	{
		for(int j = 1;j<=len2;j++)
		{
			if(str1.GetAt(i - 1) == str2.GetAt(j - 1))
			{
				temp = 0;
			}
			else
			{
				temp = 1;
			}
			//ȡ����ֵ�е���С��
			dif[i][j] = GetMin(dif[i-1][j-1]+temp,dif[i][j-1]+1,dif[i-1][j]+1);

		}
	}
	return 1-(float)dif[len1][len2]/max(str1.GetLength(),str2.GetLength());
}

void CMy0131123761Dlg::pdfFileJudgement()
{
	PDFlib pdf;
    int font;
	CStringW strw;
	std::wstring wstr;

	
	
	//pdf.set_parameter(L"license",L"X600605-009100-4E7661-329E0C");

	//pdf.set_parameter(L"license",L"X600605-009100-4E7661-329E0C");
    
	//pdf.set_option(L"errorpolicy=return");

    pdf.begin_document(L"d:\\test.pdf", L"");
    pdf.set_info(L"Creator", L"0131123761");
    pdf.set_info(L"Author", L"cliu");  
    pdf.set_info(L"Title", L"Test");

    pdf.begin_page_ext(a4_width, a4_height, L"");
    font = pdf.load_font(L"����", L"unicode", L"");
    pdf.setfont(font, 10);

    pdf.set_text_pos(50, a4_height - 50);

    CString tmp;
    m_MyEdit2Ctrl.GetWindowText(tmp);
    wstring card_id=(LPCWSTR)CStringW(tmp);
    card_id = L"׼��֤�ţ�" + card_id;
    pdf.show(card_id);


    m_MyEdit3Ctrl.GetWindowText(tmp);
    wstring person_id=(LPCWSTR)CStringW(tmp);
    person_id = L"���֤�ţ�" + person_id;
    pdf.continue_text(person_id);

    tmp.Format(_T("�����ֵ�׼ȷ��Ϊ%.2f%%,�ٶ���%.0f����/���ӣ����ο��Եĳɼ���%.2f�֡�"),accuracy,speed,score);
    wstring info = (LPCWSTR)CStringW(tmp);
    pdf.continue_text(info);


    pdf.continue_text(L"�����������ο���¼������ݣ�");
	//<<=========================================================
	for (int i = 1; i <= (m_MyEdit6Value.GetLength()/60); i++)
	{
		m_MyEdit6Value.Insert(60 * i, _T("\r\n"));
	}
	//>>=========================================================
	wstring input=(LPCWSTR)CStringW(m_MyEdit6Value);

	CString sCombEdit=_T("");
	CString sTemp;
	CString s;
	sTemp.Empty();
	CString sFind = _T("\r\n");//Ѱ�һس�ȷ�ϱ༭
	int iStart = 0;
	int iPos = 0;
	int iCnt = 0;
	int idEdit = 0;
	iPos = m_MyEdit6Value.Find(sFind, iStart);
	if ((iPos = m_MyEdit6Value.Find(sFind, iStart)) != -1)
	{
		while ((iPos = m_MyEdit6Value.Find(sFind, iStart)) != -1)
		{
			iCnt = iPos - iStart;
			for (int i = 0; i < iCnt; i++)
			{
				sTemp = m_MyEdit6Value.GetAt(iStart + i);
				sCombEdit += sTemp;
			}
			strw = sCombEdit;
			wstr = strw;
			pdf.continue_text(wstr);
			idEdit++;
			iStart = iPos + 2;
			sCombEdit = "";
		}
	}
	else
	{
		strw = m_MyEdit6Value;
		wstr = strw;
		pdf.continue_text(wstr);
	}
	iCnt = m_MyEdit6Value.GetLength() - iStart;
	for (int i = 0; i < iCnt; i++)
	{
		sTemp = m_MyEdit6Value.GetAt(iStart + i);
		sCombEdit += sTemp;
	}
	strw = sCombEdit;
	wstr = strw;
	
	//pdf.continue_text(wstr);
	
   
   // pdf.continue_text(input);


    pdf.end_page_ext(L"");
    pdf.end_document(L"");

    ShellExecute(this->m_hWnd, _T("open"), _T("d:\\test.pdf"), NULL, NULL, SW_SHOWMAXIMIZED);

}