
// 0131123761Dlg.h : ͷ�ļ�
//

#pragma once


//�ļ���ȡ ֧������
#include"locale.h"

//<<pdf����
#include "pdflib.hpp"
using namespace pdflib;
#pragma   comment(lib, "pdflib.lib")
//>>


// CMy0131123761Dlg �Ի���
class CMy0131123761Dlg : public CDialogEx
{
// ����
public:
	CMy0131123761Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY0131123761_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_MyCombo2;
	CButton m_MyButton1;
	afx_msg void OnBnClickedButton1();
//	CString m_MyEdit2;
//	CString m_MyEdit3;
//	CEdit m_MyEdit4Ctrl;
//	CString m_MyEdit4Value;
//	CEdit m_MyEdit6Ctrl;
//	CString m_MyEdit6Value;
	
	//���ֿ���
	void OnPlay(int);
	DWORD getinfo(UINT,DWORD);
	void OnStop();
	void OnPause();
	void OnResume();


	//<<2015/08/25/Cliu/Judge
	bool Number1Judge(CString ,int );
	bool Number2Judge(CString ,int );
	//>>

	//<<15/08/25/EditCtrl4/Timer
	int m_second;
	int m_minute;
	int m_hour;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//�ı�����
	CFont m_MyFont;
	afx_msg void OnBnClickedOk();
	CString m_MyEdit6Value;
	CString m_MyEdit2;
	CString m_MyEdit3;

	//��ȡini�ļ�����
	int total_minutes;
	int total_questions;
	CString audio_format;
	int max_speed;
	CString percentage_accuracy;
	CString percentage_speed;
	//>>

	afx_msg void OnEnSetfocusEdit6();
	CString m_MyEdit4Value;
	CStatic m_MyEdit4Ctrl;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//<<��¼������ʱ
	int m_TotalTime;
	//>>
	//<<����һ��setFocusEdit6
	bool m_Judgement;
	//>>
	afx_msg void OnBnClickedButton2();

	//<<�������ƶȺ���
	float Similarity(CString str1,CString str2);
	//<<��������ֵ����Сֵ����
	int GetMin(int ,int ,int);

	CStdioFile m_ReadFile;
	float accuracy;
	float score;
	float speed;
	//PDF�ļ�д��
	PDF *p;
	int i1,j1,Left,Top;
	void pdfFileJudgement();
	CEdit m_MyEdit2Ctrl;
	CEdit m_MyEdit3Ctrl;
};

