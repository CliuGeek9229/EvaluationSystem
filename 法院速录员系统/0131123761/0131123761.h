
// 0131123761.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CMy0131123761App:
// �йش����ʵ�֣������ 0131123761.cpp
//

class CMy0131123761App : public CWinApp
{
public:
	CMy0131123761App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy0131123761App theApp;