
// 2013253063_HW3.h : 2013253063_HW3 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMy2013253063_HW3App:
// �� Ŭ������ ������ ���ؼ��� 2013253063_HW3.cpp�� �����Ͻʽÿ�.
//

class CMy2013253063_HW3App : public CWinApp
{
public:
	CMy2013253063_HW3App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy2013253063_HW3App theApp;
