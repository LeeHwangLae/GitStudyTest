
// BlackJack.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CBlackJackApp:
// �� Ŭ������ ������ ���ؼ��� BlackJack.cpp�� �����Ͻʽÿ�.
//

class CBlackJackApp : public CWinApp
{
public:
	CBlackJackApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CBlackJackApp theApp;