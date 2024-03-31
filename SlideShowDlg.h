// SlideShowDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "SlideShowCtrl.h"
#include "afxcmn.h"

// CSlideShowDlg dialog
class CSlideShowDlg : public CDialog
{
// Construction
public:
	CSlideShowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SLIDESHOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
public:
	void LoadSettings(CFile& File);
	void SaveSettings(CFile& File);

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnOpenFolder();
	afx_msg void OnRescanFolder();
	afx_msg void OnCloseFolder();
	afx_msg void OnPlay();
	afx_msg void OnPause();
	afx_msg void OnPlayPause();
	afx_msg void OnFullScreen();
	afx_msg void OnStretchToFit();
	afx_msg void OnItemsShuffle();
	afx_msg void OnItemsLoop();
	afx_msg void OnItemsNext();
	afx_msg void OnItemsNextAlt();
	afx_msg void OnItemsPrevious();
	afx_msg void OnItemsPreviousAlt();
	afx_msg void OnItemsHome();
	afx_msg void OnItemsReshuffle();
	afx_msg void OnSubitemsShuffle();
	afx_msg void OnSubitemsLoop();
	afx_msg void OnSubitemsNext();
	afx_msg void OnSubitemsNextAlt();
	afx_msg void OnSubitemsPrevious();
	afx_msg void OnSubitemsPreviousAlt();
	afx_msg void OnSubitemsHome();
	afx_msg void OnSubitemsReshuffle();
	afx_msg void OnAllHome();
	afx_msg void OnAllReshuffle();
	afx_msg void OnSlideShowItems();
	afx_msg void OnSlideShowSubitems();
	afx_msg void OnSlideShowSpeedSlow();
	afx_msg void OnSlideShowSpeedMedium();
	afx_msg void OnSlideShowSpeedFast();
	afx_msg void OnOpenFile();
	afx_msg void OnOpenFileLocation();
	afx_msg void OnProperties();
	afx_msg void OnExit();
	afx_msg void OnUpdateRescanFolder(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCloseFolder(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePlay(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePause(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFullScreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStretchToFit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateItemsShuffle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateItemsLoop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateItemsNext(CCmdUI *pCmdUI);
	afx_msg void OnUpdateItemsPrevious(CCmdUI *pCmdUI);
	afx_msg void OnUpdateItemsHome(CCmdUI *pCmdUI);
	afx_msg void OnUpdateItemsReshuffle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSubitemsShuffle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSubitemsLoop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSubitemsNext(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSubitemsPrevious(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSubitemsHome(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSubitemsReshuffle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAllHome(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAllReshuffle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSlideShowItems(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSlideShowSubitems(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSlideShowSpeedSlow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSlideShowSpeedMedium(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSlideShowSpeedFast(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenFile(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenFileLocation(CCmdUI *pCmdUI);
	afx_msg void OnUpdateProperties(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_Brush;
	static CSlideShowCtrl m_Picture;
	HACCEL m_AccelTable;
	CMenu m_PopupMenu;
	CRect m_WindowRect;

	static INT CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lp, LPARAM pData);
};
