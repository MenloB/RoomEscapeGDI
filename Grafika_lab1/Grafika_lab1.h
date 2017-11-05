
// Grafika_lab1.h : main header file for the Grafika_lab1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGrafikalab1App:
// See Grafika_lab1.cpp for the implementation of this class
//

class CGrafikalab1App : public CWinAppEx
{
public:
	CGrafikalab1App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGrafikalab1App theApp;
