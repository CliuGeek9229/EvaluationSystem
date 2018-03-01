
// 0131123761Dlg.h : 头文件
//

#pragma once


//文件读取 支持中文
#include"locale.h"

//<<pdf生成
#include "pdflib.hpp"
using namespace pdflib;
#pragma   comment(lib, "pdflib.lib")
//>>


// CMy0131123761Dlg 对话框
class CMy0131123761Dlg : public CDialogEx
{
// 构造
public:
	CMy0131123761Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY0131123761_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	
	//音乐控制
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
	//改变字体
	CFont m_MyFont;
	afx_msg void OnBnClickedOk();
	CString m_MyEdit6Value;
	CString m_MyEdit2;
	CString m_MyEdit3;

	//读取ini文件数据
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

	//<<记录考试用时
	int m_TotalTime;
	//>>
	//<<调用一次setFocusEdit6
	bool m_Judgement;
	//>>
	afx_msg void OnBnClickedButton2();

	//<<计算相似度函数
	float Similarity(CString str1,CString str2);
	//<<计算三个值的最小值函数
	int GetMin(int ,int ,int);

	CStdioFile m_ReadFile;
	float accuracy;
	float score;
	float speed;
	//PDF文件写入
	PDF *p;
	int i1,j1,Left,Top;
	void pdfFileJudgement();
	CEdit m_MyEdit2Ctrl;
	CEdit m_MyEdit3Ctrl;
};

