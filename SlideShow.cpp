// SlideShow.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SlideShow.h"
#include "SlideShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSlideShowApp

BEGIN_MESSAGE_MAP(CSlideShowApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSlideShowApp construction

CSlideShowApp::CSlideShowApp()
{
	m_pszAppName = _tcsdup(_T("Slide Show"));
}


// The one and only CSlideShowApp object

CSlideShowApp theApp;


// CSlideShowApp initialization

BOOL CSlideShowApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
//	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	srand((unsigned)time(NULL));

	ULONG_PTR m_gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	CStdioFile SettingsFile;
	CString FileName = CreateSettingsFolder();
	if (!FileName.IsEmpty())
		FileName += _T("\\Settings.bin");

	CSlideShowDlg dlg;
	m_pMainWnd = &dlg;
	if (!FileName.IsEmpty() && SettingsFile.Open(FileName, CFile::modeRead | CFile::typeBinary | CFile::osSequentialScan))
	{
		dlg.LoadSettings(SettingsFile);
		SettingsFile.Close();
	}
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	if (!FileName.IsEmpty() && SettingsFile.Open(FileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary | CFile::osSequentialScan))
	{
		dlg.SaveSettings(SettingsFile);
		SettingsFile.Close();
	}

	GdiplusShutdown(m_gdiplusToken);
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

CString CSlideShowApp::CreateSettingsFolder()
{
	TCHAR szPath[MAX_PATH];

	// Get path for each user, non-roaming data.
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, szPath)))
	{
		// Append product-specific path
		PathAppend(szPath, _T("\\Adrian Grucza"));
		::CreateDirectory(szPath, 0);
		PathAppend(szPath, _T("\\") + CString(AfxGetAppName()));
		::CreateDirectory(szPath, 0);
	}

	return szPath;
}
