// 0131123761Dlg.cpp : 实现文件
#include "stdafx.h"
#include "0131123761.h"
#include "0131123761Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

//===============================================
#include"Mmsystem.h"
#pragma   comment(lib, "winmm.lib")

MCI_OPEN_PARMS op;

void  CMy0131123761Dlg::OnPlay(int TestNumber) 
 {
  // TODO: Add your control notification handler code here
  DWORD cdlen ;//音频文件长度
  
  //获取当前选中项，根据选项改变当前播放音乐
  CString str;
  str.Format(_T(".\\MusicDoc\\%d.mp3"),TestNumber);

 op.dwCallback=NULL; 
  op.lpstrAlias=NULL; 
  op.lpstrDeviceType=_T("MPEGAudio");  //设备类型，大多数文件可以这样设置 
 op.lpstrElementName=str; //文件路径 
 op.wDeviceID=NULL;      //打开设备成功以后保存这个设备号备用 
 UINT rs;        //接受函数返回结果 
 //发送命令打开设备，成功返回0，否则返回错误号，第三个参数这里必须MCI_OPEN_ELEMENT  
  rs=mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)&op);

 mciSendCommand(NULL,MCI_SET,MCI_SET_DOOR_OPEN,NULL); 

 cdlen=getinfo(op.wDeviceID,MCI_STATUS_LENGTH);//获取音频文件长度

 m_hour = (int)cdlen/3600000;
 m_minute = (int)cdlen/60000;
 m_second = (int)cdlen%60000/1000;

 if(rs==0)        //设备打开成功就播放文件 
 { 
   MCI_PLAY_PARMS pp; 
   pp.dwCallback=NULL; 
   pp.dwFrom=0;      //开始播放的位置 
  mciSendCommand(op.wDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)&pp);
   //播放文件，如果第三个参数设为MCI_WAIT则程序窗口会被阻塞，为了避免这种情况可以设为MCI_NOTIFY 
  }

 //Sleep(cdlen);//根据文件长度等待，与MCI_WAIT效果一样，cdlen参数可以控制播放时间
 //OnStop();        //关闭音频文件 
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
  //在WM_CLOSE消息处理过程中发送MCI_CLOSE命令关闭设备
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
//pdf文件写入
//if(())



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMy0131123761Dlg 对话框




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

	//<<读取信息存储
	total_minutes = 0;
	total_questions = 0;
	audio_format = _T("");
	max_speed = 0;
	percentage_accuracy = _T("");
	percentage_speed = _T("");
	//>>
	m_MyEdit4Value = _T("");

	//<<记录考试用时
	m_TotalTime = 0;
	//>>
	accuracy =0.0f;
	speed = 0.0f;
	score = 0.0f;
	//<<调用一次setFocusEdit6
	m_Judgement = true;
	//>>
	//<<PDF初始化
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


// CMy0131123761Dlg 消息处理程序

BOOL CMy0131123761Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//<<====================================================文件加密======================================================
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


	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy0131123761Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	//判断准考证号以及身份证号是否符合标准
	CString Registeration_number =m_MyEdit2;
	CString ID_number = m_MyEdit3;
	int Rlength = Registeration_number.GetLength();
	int IDlength = ID_number.GetLength();
	bool judge1 = Number1Judge(Registeration_number,Rlength);
	bool judge2 = Number2Judge(ID_number,IDlength);
	//验证准考证号与身份证号是否匹配

	//获取当前选中项
	int TestNumber = m_MyCombo2.GetCurSel();

	if(Rlength == 11 && IDlength == 18 && judge1 && judge2)
	{
		OnPlay(TestNumber);
		//UpdateData();
		
		m_MyEdit6Value = _T("考试开始了，请在这个地方录入文字。。。");
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
		//<<改变字体
		m_MyFont.CreatePointFont(150,_T("华文行楷"));
		m_MyEdit4Ctrl.SetFont(&m_MyFont);
		//>>
		SetTimer(1,1000,0);
	}
	else
	{
		MessageBox(_T("请重新核实您的个人信息"),_T("信息有误"),0);
	}
}
void CMy0131123761Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	m_MyEdit4Value.Format(_T("\r\n考试剩余时间\r\n\r\n")+m_strHour+_T(":")+m_strMinute+_T(":")+m_strSecond);

	UpdateData(false);
	
	CDialogEx::OnTimer(nIDEvent);
}


void CMy0131123761Dlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	//m_MyEdit6Ctrl.Clear();
	// TODO:  在此添加控件通知处理程序代码
}


void CMy0131123761Dlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//UpdateData();
	CDialogEx::OnChar(nChar, nRepCnt, nFlags);
}


void CMy0131123761Dlg::OnBnClickedOk()
{
	UpdateData();
	OnPause();
		char *old_locale=_strdup(setlocale(LC_CTYPE,NULL));
	setlocale(LC_CTYPE,"chs");
	if(MessageBox(_T("提交之后您的本次考试将结束。\r\n您确定提交吗？"),_T("提示"),MB_ICONINFORMATION | MB_OKCANCEL) == IDOK)
	{
	OnStop();
	KillTimer(1);
	
	//<<读取答案文件(解密读文件)===============================================================
	CString strRead;
	int CurrentSel = m_MyCombo2.GetCurSel();//获取当前选中项

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
	m_MyEdit4Value.Format(_T("\r\n您的考试总用时\r\n\r\n%d分%d秒"),m_Minute,m_Second);
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
	// TODO: 在此添加控件通知处理程序代码
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

	// TODO:  在此更改 DC 的任何特性
	if(pWnd->GetDlgCtrlID()==IDC_STATIC1)
	{
		pDC->SetTextColor(RGB(0,0,255)); //设置字体颜色
		//pDC->SetBkColor(RGB(255,0,0)); //设置背景色
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CMy0131123761Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDCANCEL)->EnableWindow(true);

	pdfFileJudgement();

	//UpdateData();
	//int m_Minute = m_TotalTime/60;
	//int m_Second = m_TotalTime%60;

	////<<规范化输出答案
	///*accuracy;
	//speed;
	//score;*/

	//CString m_temp;
	//CString a = _T("%");
	//m_temp.Format(_T("\r\n准考证号：")+m_MyEdit2+_T("\r\n身份证号：")+m_MyEdit3+_T("\r\n考试用时：%d分%d秒")+_T("\r\n您打字的准确率是%.2f")+_T("%%,速度是%.2f个字/分钟，本次考试成绩是%.2f分")+_T("\r\n以下是您本次考试录入的内容：\r\n")+m_MyEdit6Value,m_Minute,m_Second,accuracy,speed,score);
	//MessageBox(m_temp,_T("打印成绩单"),1);
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
	//计算两个字符串的长度
	int len1 = str1.GetLength();
	int len2 = str2.GetLength();
	//建立数组，比字符长度大一个空间
	int **dif = new int *[len1+1];
	for(int i = 0;i<len1+1;i++)
	{
		dif[i] = new int [len2];
	}
	//赋初值
	for(int a = 0;a<=len1;a++)
	{
		dif[a][0] = a;
	}
	for(int a = 0;a<=len2;a++)
	{
		dif[0][a] = a;
	}
	//计算两个字符是否一样，计算左上的值
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
			//取三个值中的最小的
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
    font = pdf.load_font(L"仿宋", L"unicode", L"");
    pdf.setfont(font, 10);

    pdf.set_text_pos(50, a4_height - 50);

    CString tmp;
    m_MyEdit2Ctrl.GetWindowText(tmp);
    wstring card_id=(LPCWSTR)CStringW(tmp);
    card_id = L"准考证号：" + card_id;
    pdf.show(card_id);


    m_MyEdit3Ctrl.GetWindowText(tmp);
    wstring person_id=(LPCWSTR)CStringW(tmp);
    person_id = L"身份证号：" + person_id;
    pdf.continue_text(person_id);

    tmp.Format(_T("您打字的准确率为%.2f%%,速度是%.0f个字/分钟，本次考试的成绩是%.2f分。"),accuracy,speed,score);
    wstring info = (LPCWSTR)CStringW(tmp);
    pdf.continue_text(info);


    pdf.continue_text(L"以下是您本次考试录入的内容：");
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
	CString sFind = _T("\r\n");//寻找回车确认编辑
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