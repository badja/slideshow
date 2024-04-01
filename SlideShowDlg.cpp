// SlideShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SlideShow.h"
#include "SlideShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSlideShowDlg dialog

CSlideShowCtrl CSlideShowDlg::m_Picture;

CSlideShowDlg::CSlideShowDlg(CWnd* pParent)
	: CDialog(CSlideShowDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_AccelTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR_SLIDE_SHOW));
}

void CSlideShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
}

BEGIN_MESSAGE_MAP(CSlideShowDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_INITMENUPOPUP()
	ON_STN_DBLCLK(IDC_PICTURE, &CSlideShowDlg::OnFullScreen)
	ON_COMMAND(ID_OPEN_FOLDER, &CSlideShowDlg::OnOpenFolder)
	ON_COMMAND(ID_RESCAN_FOLDER, &CSlideShowDlg::OnRescanFolder)
	ON_COMMAND(ID_CLOSE_FOLDER, &CSlideShowDlg::OnCloseFolder)
	ON_COMMAND(ID_PLAY, &CSlideShowDlg::OnPlay)
	ON_COMMAND(ID_PAUSE, &CSlideShowDlg::OnPause)
	ON_COMMAND(ID_PLAY_PAUSE, &CSlideShowDlg::OnPlayPause)
	ON_COMMAND(ID_FULL_SCREEN, &CSlideShowDlg::OnFullScreen)
	ON_COMMAND(ID_STRETCH_TO_FIT, &CSlideShowDlg::OnStretchToFit)
	ON_COMMAND(ID_ITEMS_SHUFFLE, &CSlideShowDlg::OnItemsShuffle)
	ON_COMMAND(ID_ITEMS_LOOP, &CSlideShowDlg::OnItemsLoop)
	ON_COMMAND(ID_ITEMS_NEXT, &CSlideShowDlg::OnItemsNext)
	ON_COMMAND(ID_ITEMS_NEXT_ALT, &CSlideShowDlg::OnItemsNextAlt)
	ON_COMMAND(ID_ITEMS_PREVIOUS, &CSlideShowDlg::OnItemsPrevious)
	ON_COMMAND(ID_ITEMS_PREVIOUS_ALT, &CSlideShowDlg::OnItemsPreviousAlt)
	ON_COMMAND(ID_ITEMS_HOME, &CSlideShowDlg::OnItemsHome)
	ON_COMMAND(ID_ITEMS_RESHUFFLE, &CSlideShowDlg::OnItemsReshuffle)
	ON_COMMAND(ID_SUBITEMS_SHUFFLE, &CSlideShowDlg::OnSubitemsShuffle)
	ON_COMMAND(ID_SUBITEMS_LOOP, &CSlideShowDlg::OnSubitemsLoop)
	ON_COMMAND(ID_SUBITEMS_NEXT, &CSlideShowDlg::OnSubitemsNext)
	ON_COMMAND(ID_SUBITEMS_NEXT_ALT, &CSlideShowDlg::OnSubitemsNextAlt)
	ON_COMMAND(ID_SUBITEMS_PREVIOUS, &CSlideShowDlg::OnSubitemsPrevious)
	ON_COMMAND(ID_SUBITEMS_PREVIOUS_ALT, &CSlideShowDlg::OnSubitemsPreviousAlt)
	ON_COMMAND(ID_SUBITEMS_HOME, &CSlideShowDlg::OnSubitemsHome)
	ON_COMMAND(ID_SUBITEMS_RESHUFFLE, &CSlideShowDlg::OnSubitemsReshuffle)
	ON_COMMAND(ID_ALL_HOME, &CSlideShowDlg::OnAllHome)
	ON_COMMAND(ID_ALL_RESHUFFLE, &CSlideShowDlg::OnAllReshuffle)
	ON_COMMAND(ID_SLIDE_SHOW_ITEMS, &CSlideShowDlg::OnSlideShowItems)
	ON_COMMAND(ID_SLIDE_SHOW_SUBITEMS, &CSlideShowDlg::OnSlideShowSubitems)
	ON_COMMAND(ID_SLIDE_SHOW_SPEED_SLOW, &CSlideShowDlg::OnSlideShowSpeedSlow)
	ON_COMMAND(ID_SLIDE_SHOW_SPEED_MEDIUM, &CSlideShowDlg::OnSlideShowSpeedMedium)
	ON_COMMAND(ID_SLIDE_SHOW_SPEED_FAST, &CSlideShowDlg::OnSlideShowSpeedFast)
	ON_COMMAND(ID_OPEN_FILE, &CSlideShowDlg::OnOpenFile)
	ON_COMMAND(ID_OPEN_FILE_LOCATION, &CSlideShowDlg::OnOpenFileLocation)
	ON_COMMAND(ID_PROPERTIES, &CSlideShowDlg::OnProperties)
	ON_COMMAND(ID_EXIT, &CSlideShowDlg::OnExit)
	ON_UPDATE_COMMAND_UI(ID_RESCAN_FOLDER, &CSlideShowDlg::OnUpdateRescanFolder)
	ON_UPDATE_COMMAND_UI(ID_CLOSE_FOLDER, &CSlideShowDlg::OnUpdateCloseFolder)
	ON_UPDATE_COMMAND_UI(ID_PLAY, &CSlideShowDlg::OnUpdatePlay)
	ON_UPDATE_COMMAND_UI(ID_PAUSE, &CSlideShowDlg::OnUpdatePause)
	ON_UPDATE_COMMAND_UI(ID_FULL_SCREEN, &CSlideShowDlg::OnUpdateFullScreen)
	ON_UPDATE_COMMAND_UI(ID_STRETCH_TO_FIT, &CSlideShowDlg::OnUpdateStretchToFit)
	ON_UPDATE_COMMAND_UI(ID_ITEMS_SHUFFLE, &CSlideShowDlg::OnUpdateItemsShuffle)
	ON_UPDATE_COMMAND_UI(ID_ITEMS_LOOP, &CSlideShowDlg::OnUpdateItemsLoop)
	ON_UPDATE_COMMAND_UI(ID_ITEMS_NEXT, &CSlideShowDlg::OnUpdateItemsNext)
	ON_UPDATE_COMMAND_UI(ID_ITEMS_PREVIOUS, &CSlideShowDlg::OnUpdateItemsPrevious)
	ON_UPDATE_COMMAND_UI(ID_ITEMS_HOME, &CSlideShowDlg::OnUpdateItemsHome)
	ON_UPDATE_COMMAND_UI(ID_ITEMS_RESHUFFLE, &CSlideShowDlg::OnUpdateItemsReshuffle)
	ON_UPDATE_COMMAND_UI(ID_SUBITEMS_SHUFFLE, &CSlideShowDlg::OnUpdateSubitemsShuffle)
	ON_UPDATE_COMMAND_UI(ID_SUBITEMS_LOOP, &CSlideShowDlg::OnUpdateSubitemsLoop)
	ON_UPDATE_COMMAND_UI(ID_SUBITEMS_NEXT, &CSlideShowDlg::OnUpdateSubitemsNext)
	ON_UPDATE_COMMAND_UI(ID_SUBITEMS_PREVIOUS, &CSlideShowDlg::OnUpdateSubitemsPrevious)
	ON_UPDATE_COMMAND_UI(ID_SUBITEMS_HOME, &CSlideShowDlg::OnUpdateSubitemsHome)
	ON_UPDATE_COMMAND_UI(ID_SUBITEMS_RESHUFFLE, &CSlideShowDlg::OnUpdateSubitemsReshuffle)
	ON_UPDATE_COMMAND_UI(ID_ALL_HOME, &CSlideShowDlg::OnUpdateAllHome)
	ON_UPDATE_COMMAND_UI(ID_ALL_RESHUFFLE, &CSlideShowDlg::OnUpdateAllReshuffle)
	ON_UPDATE_COMMAND_UI(ID_SLIDE_SHOW_ITEMS, &CSlideShowDlg::OnUpdateSlideShowItems)
	ON_UPDATE_COMMAND_UI(ID_SLIDE_SHOW_SUBITEMS, &CSlideShowDlg::OnUpdateSlideShowSubitems)
	ON_UPDATE_COMMAND_UI(ID_SLIDE_SHOW_SPEED_SLOW, &CSlideShowDlg::OnUpdateSlideShowSpeedSlow)
	ON_UPDATE_COMMAND_UI(ID_SLIDE_SHOW_SPEED_MEDIUM, &CSlideShowDlg::OnUpdateSlideShowSpeedMedium)
	ON_UPDATE_COMMAND_UI(ID_SLIDE_SHOW_SPEED_FAST, &CSlideShowDlg::OnUpdateSlideShowSpeedFast)
	ON_UPDATE_COMMAND_UI(ID_OPEN_FILE, &CSlideShowDlg::OnUpdateOpenFile)
	ON_UPDATE_COMMAND_UI(ID_OPEN_FILE_LOCATION, &CSlideShowDlg::OnUpdateOpenFileLocation)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES, &CSlideShowDlg::OnUpdateProperties)
END_MESSAGE_MAP()


void CSlideShowDlg::LoadSettings(CFile& File)
{
	TRY 
	{
		CArchive Archive(&File, CArchive::load);
		m_Picture.Serialize(Archive);
	}
	CATCH (CException, e)
	{
		
	}
	END_CATCH
}

void CSlideShowDlg::SaveSettings(CFile& File)
{
	CArchive Archive(&File, CArchive::store);
	m_Picture.Serialize(Archive);
}

// CSlideShowDlg message handlers

BOOL CSlideShowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_Brush.CreateSolidBrush(RGB(0, 0, 0));

	// Trigger the WM_SIZE message
	CRect rect;
	GetClientRect(&rect);
	m_Picture.MoveWindow(0, 0, rect.Width(), rect.Height(), FALSE);
	m_Picture.DisplayCurrentImage();

	m_PopupMenu.LoadMenu(IDR_MENU_POPUP);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CSlideShowDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_AccelTable && ::TranslateAccelerator(m_hWnd, m_AccelTable, pMsg))
		return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSlideShowDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		const int cxIcon = GetSystemMetrics(SM_CXICON);
		const int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		const int x = (rect.Width() - cxIcon + 1) / 2;
		const int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSlideShowDlg::OnQueryDragIcon() noexcept
{
	return m_hIcon;
}

HBRUSH CSlideShowDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	return m_Brush;
}

void CSlideShowDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CWnd* pPicture = GetDlgItem(IDC_PICTURE);
	if (pPicture)
	{
		// Limit picture control size to one monitor
		HDC DC = ::GetDC(NULL);
		cx = min(cx, GetDeviceCaps(DC, HORZRES));
		cy = min(cy, GetDeviceCaps(DC, VERTRES));
		::ReleaseDC(0, DC);

		pPicture->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
		pPicture->Invalidate(FALSE);
	}
}

void CSlideShowDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// If context menu key was pressed, use center-point of window instead
	if (pWnd && point.x < 0 && point.y < 0)
	{
		CRect Rect;
		pWnd->GetWindowRect(Rect);
		point = Rect.CenterPoint();
	}

	m_PopupMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CSlideShowDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	if (bSysMenu)
		return;     // don't support system menu

	ASSERT(pPopupMenu != NULL);
	// check the enabled state of various menu items

	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// determine if menu is popup in top-level menu and set m_pOther to
	//  it if so (m_pParentMenu == NULL indicates that it is secondary popup)
	HMENU hParentMenu{};
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;    // parent == child for tracking popup
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = GetTopLevelParent();
		// child windows don't have menus -- need to go to the top!
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			const int nPosMax = ::GetMenuItemCount(hParentMenu);
			for (int nPos = 0; nPos < nPosMax; nPos++)
			{
				if (::GetSubMenu(hParentMenu, nPos) == pPopupMenu->m_hMenu)
				{
					// when popup is found, m_pParentMenu is containing menu
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
		state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // menu separator or invalid cmd - ignore it

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == UINT_MAX)
		{
			// possibly a popup menu, route to first item of that popup
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == UINT_MAX)
			{
				continue;       // first item of popup can't be routed to
			}
			state.DoUpdate(this, FALSE);    // popups are never auto disabled
		}
		else
		{
			// normal menu item
			// Auto enable/disable if frame window has 'm_bAutoMenuEnable'
			//    set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, TRUE);
		}

		// adjust for menu deletions and additions
		const UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}

void CSlideShowDlg::OnOpenFolder()
{
	//PopUp the Browse for Folder Dialog 
	LPMALLOC pMalloc;
	CString Path;
	/* Gets the Shell's default allocator */
	if (::SHGetMalloc(&pMalloc) == NOERROR && pMalloc)
	{
		BROWSEINFO bi{};
		TCHAR szBuffer[MAX_PATH]{};
		LPTSTR pszBuffer = &szBuffer[0];
		LPITEMIDLIST pidl{};
		// Get help on BROWSEINFO struct - it's got all the bit settings.
		bi.hwndOwner = GetSafeHwnd();
		bi.pidlRoot = NULL;
		bi.pszDisplayName = pszBuffer;
		bi.lpszTitle = _T("Select a folder that contains pictures or folders of pictures");
		bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
		bi.lpfn = BrowseCallbackProc;
		bi.lParam = 0;
		// This next call issues the dialog box.
		if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
		{
			if (::SHGetPathFromIDList(pidl, pszBuffer))
			{ 
				// At this point pszBuffer contains the selected path */.
				Path = pszBuffer;
			}
			// Free the PIDL allocated by SHBrowseForFolder.
			pMalloc->Free(pidl);
		}
		// Release the shell's allocator.
		pMalloc->Release();
	}

	m_Picture.SetFolder(Path);
}

void CSlideShowDlg::OnRescanFolder()
{
	m_Picture.SetFolder(m_Picture.GetFolder());
}

void CSlideShowDlg::OnCloseFolder()
{
	m_Picture.CloseFolder();
}

void CSlideShowDlg::OnPlay()
{
	m_Picture.Start();
}

void CSlideShowDlg::OnPause()
{
	m_Picture.Stop();
}

void CSlideShowDlg::OnPlayPause()
{
	if (m_Picture.IsPlaying())
		m_Picture.Stop();
	else
		m_Picture.Start();
}

void CSlideShowDlg::OnFullScreen()
{
	if (GetStyle() & WS_SIZEBOX)
	{
		GetWindowRect(m_WindowRect);
		ModifyStyle(WS_CAPTION | WS_THICKFRAME, 0);

		CRect DesktopRect;
		DesktopRect.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
		DesktopRect.right = DesktopRect.left + GetSystemMetrics(SM_CXVIRTUALSCREEN);
		DesktopRect.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
		DesktopRect.bottom = DesktopRect.top + GetSystemMetrics(SM_CYVIRTUALSCREEN);
		MoveWindow(DesktopRect);
	}
	else
	{
		ModifyStyle(0, WS_CAPTION | WS_THICKFRAME);
		MoveWindow(m_WindowRect);
	}
}

void CSlideShowDlg::OnStretchToFit()
{
	m_Picture.SetStretchToFit(!m_Picture.GetStretchToFit());
}

void CSlideShowDlg::OnItemsShuffle()
{
	m_Picture.SetShuffleItems(!m_Picture.GetShuffleItems());
}

void CSlideShowDlg::OnItemsLoop() noexcept
{
	m_Picture.SetLoopItems(!m_Picture.GetLoopItems());
}

void CSlideShowDlg::OnItemsNext()
{
	m_Picture.NextItem(TRUE);
}

void CSlideShowDlg::OnItemsNextAlt()
{
	m_Picture.NextItem(FALSE);
}

void CSlideShowDlg::OnItemsPrevious()
{
	m_Picture.PreviousItem(TRUE);
}

void CSlideShowDlg::OnItemsPreviousAlt()
{
	m_Picture.PreviousItem(FALSE);
}

void CSlideShowDlg::OnItemsHome()
{
	m_Picture.HomeItem();
}

void CSlideShowDlg::OnItemsReshuffle()
{
	m_Picture.ReshuffleItems();
}

void CSlideShowDlg::OnSubitemsShuffle()
{
	m_Picture.SetShuffleSubitems(!m_Picture.GetShuffleSubitems());
}

void CSlideShowDlg::OnSubitemsLoop() noexcept
{
	m_Picture.SetLoopSubitems(!m_Picture.GetLoopSubitems());
}

void CSlideShowDlg::OnSubitemsNext()
{
	m_Picture.NextSubitem(TRUE);
}

void CSlideShowDlg::OnSubitemsNextAlt()
{
	m_Picture.NextSubitem(FALSE);
}

void CSlideShowDlg::OnSubitemsPrevious()
{
	m_Picture.PreviousSubitem(TRUE);
}

void CSlideShowDlg::OnSubitemsPreviousAlt()
{
	m_Picture.PreviousSubitem(FALSE);
}

void CSlideShowDlg::OnSubitemsHome()
{
	m_Picture.HomeSubitem();
}

void CSlideShowDlg::OnSubitemsReshuffle()
{
	m_Picture.ReshuffleSubitems();
}

void CSlideShowDlg::OnAllHome()
{
	m_Picture.HomeAll();
}

void CSlideShowDlg::OnAllReshuffle()
{
	m_Picture.ReshuffleAll();
}

void CSlideShowDlg::OnSlideShowItems() noexcept
{
	m_Picture.SetSlideShowType(CSlideShowCtrl::Items);
}

void CSlideShowDlg::OnSlideShowSubitems() noexcept
{
	m_Picture.SetSlideShowType(CSlideShowCtrl::Subitems);
}

void CSlideShowDlg::OnSlideShowSpeedSlow()
{
	m_Picture.SetSlideShowSpeed(CSlideShowCtrl::Slow);
}

void CSlideShowDlg::OnSlideShowSpeedMedium()
{
	m_Picture.SetSlideShowSpeed(CSlideShowCtrl::Medium);
}

void CSlideShowDlg::OnSlideShowSpeedFast()
{
	m_Picture.SetSlideShowSpeed(CSlideShowCtrl::Fast);
}

void CSlideShowDlg::OnOpenFile()
{
	CString strFileName = m_Picture.GetCurrentFileName();

	static SHELLEXECUTEINFO ExecInfo;
	ExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ExecInfo.fMask = SEE_MASK_INVOKEIDLIST;
	ExecInfo.lpVerb = _T("open");
	ExecInfo.lpFile = strFileName;
	ExecInfo.nShow = SW_SHOWNORMAL;

	ShellExecuteEx(&ExecInfo);
}

void CSlideShowDlg::OnOpenFileLocation()
{
	CString strParameters;
	strParameters.Format(_T("/select,\"%s\""), m_Picture.GetCurrentFileName().GetString());

	ShellExecute(0, _T("open"), _T("explorer.exe"), strParameters, 0, SW_NORMAL);
}

void CSlideShowDlg::OnProperties()
{
	CString strFileName = m_Picture.GetCurrentFileName();

	static SHELLEXECUTEINFO ExecInfo;
	ExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ExecInfo.fMask = SEE_MASK_INVOKEIDLIST;
	ExecInfo.lpVerb = _T("properties");
	ExecInfo.lpFile = strFileName;
	ExecInfo.nShow = SW_SHOWNORMAL;

	ShellExecuteEx(&ExecInfo);
}

void CSlideShowDlg::OnExit()
{
	EndDialog(IDCANCEL);
}

void CSlideShowDlg::OnUpdateRescanFolder(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(!m_Picture.GetFolder().IsEmpty());
}

void CSlideShowDlg::OnUpdateCloseFolder(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(!m_Picture.GetFolder().IsEmpty());
}

void CSlideShowDlg::OnUpdatePlay(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(!m_Picture.GetFolder().IsEmpty() && !m_Picture.IsPlaying());
}

void CSlideShowDlg::OnUpdatePause(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(m_Picture.IsPlaying());
}

void CSlideShowDlg::OnUpdateFullScreen(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->SetCheck(!(GetStyle() & WS_SIZEBOX));
}

void CSlideShowDlg::OnUpdateStretchToFit(CCmdUI* pCmdUI)
{
	if (pCmdUI)
		pCmdUI->SetCheck(m_Picture.GetStretchToFit());
}

void CSlideShowDlg::OnUpdateItemsShuffle(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->SetCheck(m_Picture.GetShuffleItems());
}

void CSlideShowDlg::OnUpdateItemsLoop(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->SetCheck(m_Picture.GetLoopItems());
}

void CSlideShowDlg::OnUpdateItemsNext(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(m_Picture.GetLoopItems() || !m_Picture.IsLastItem());
}

void CSlideShowDlg::OnUpdateItemsPrevious(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(m_Picture.GetLoopItems() || !m_Picture.IsFirstItem());
}

void CSlideShowDlg::OnUpdateItemsHome(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(!m_Picture.IsFirstItem());
}

void CSlideShowDlg::OnUpdateItemsReshuffle(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(m_Picture.HasItems());
}

void CSlideShowDlg::OnUpdateSubitemsShuffle(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->SetCheck(m_Picture.GetShuffleSubitems());
}

void CSlideShowDlg::OnUpdateSubitemsLoop(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->SetCheck(m_Picture.GetLoopSubitems());
}

void CSlideShowDlg::OnUpdateSubitemsNext(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(m_Picture.GetLoopSubitems() || !m_Picture.IsLastSubitem());
}

void CSlideShowDlg::OnUpdateSubitemsPrevious(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(m_Picture.GetLoopSubitems() || !m_Picture.IsFirstSubitem());
}

void CSlideShowDlg::OnUpdateSubitemsHome(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(!m_Picture.IsFirstSubitem());
}

void CSlideShowDlg::OnUpdateSubitemsReshuffle(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(m_Picture.HasSubitems());
}

void CSlideShowDlg::OnUpdateAllHome(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(m_Picture.HasItems());
}

void CSlideShowDlg::OnUpdateAllReshuffle(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(m_Picture.HasItems());
}

void CSlideShowDlg::OnUpdateSlideShowItems(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->SetRadio(m_Picture.GetSlideShowType() == CSlideShowCtrl::Items);
}

void CSlideShowDlg::OnUpdateSlideShowSubitems(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->SetRadio(m_Picture.GetSlideShowType() == CSlideShowCtrl::Subitems);
}

void CSlideShowDlg::OnUpdateSlideShowSpeedSlow(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->SetRadio(m_Picture.GetSlideShowSpeed() == CSlideShowCtrl::Slow);
}

void CSlideShowDlg::OnUpdateSlideShowSpeedMedium(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->SetRadio(m_Picture.GetSlideShowSpeed() == CSlideShowCtrl::Medium);
}

void CSlideShowDlg::OnUpdateSlideShowSpeedFast(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->SetRadio(m_Picture.GetSlideShowSpeed() == CSlideShowCtrl::Fast);
}

void CSlideShowDlg::OnUpdateOpenFile(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(!m_Picture.GetCurrentFileName().IsEmpty());
}

void CSlideShowDlg::OnUpdateOpenFileLocation(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(!m_Picture.GetCurrentFileName().IsEmpty());
}

void CSlideShowDlg::OnUpdateProperties(CCmdUI *pCmdUI)
{
	if (pCmdUI)
		pCmdUI->Enable(!m_Picture.GetCurrentFileName().IsEmpty());
}

INT CALLBACK CSlideShowDlg::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lp, LPARAM pData)
{
	switch(uMsg) 
	{
	case BFFM_INITIALIZED: 
		// WParam is TRUE since you are passing a path.
		// It would be FALSE if you were passing a pidl.
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, reinterpret_cast<LPARAM>(m_Picture.GetFolder().GetString()));
		break;
	default:
		break;
	}
	return 0;
}
