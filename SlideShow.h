// SlideShow.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CSlideShowApp:
// See SlideShow.cpp for the implementation of this class
//

class CSlideShowApp : public CWinApp
{
public:
	CSlideShowApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

private:
	CString CreateSettingsFolder();
};

extern CSlideShowApp theApp;