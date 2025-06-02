#pragma once

#include <atlimage.h>
#include "SlideShowItem.h"

// CSlideShowCtrl

class CSlideShowCtrl : public CStatic
{
	DECLARE_SERIAL(CSlideShowCtrl)

public:
	enum SlideShowType {Items, Subitems};
	enum SlideShowSpeed {Slow, Medium, Fast};

	CSlideShowCtrl() noexcept;

	virtual void Serialize(CArchive& ar);

	void SetFolder(CString Dir);
	void CloseFolder();
	CString GetFolder();
	CString GetCurrentFileName();
	void DisplayCurrentImage();
	BOOL HasImage() const noexcept;
	void Start();
	void Stop();
	BOOL IsPlaying() const noexcept;
	void ZoomIn(int Increment);
	void ZoomOut(int Increment);
	void SetStretchToFit(BOOL Stretch);
	BOOL GetStretchToFit() const noexcept;
	void SetShuffleItems(BOOL Shuffle);
	BOOL GetShuffleItems() const noexcept;
	void SetShuffleSubitems(BOOL Shuffle);
	BOOL GetShuffleSubitems() const noexcept;
	void SetLoopItems(BOOL Loop) noexcept;
	BOOL GetLoopItems() const noexcept;
	void SetLoopSubitems(BOOL Loop) noexcept;
	BOOL GetLoopSubitems() const noexcept;
	void NextItem(BOOL UseShuffleSetting);
	void PreviousItem(BOOL UseShuffleSetting);
	void NextSubitem(BOOL UseShuffleSetting);
	void PreviousSubitem(BOOL UseShuffleSetting);
	void HomeItem();
	void HomeSubitem();
	void HomeAll();
	void ReshuffleItems();
	void ReshuffleSubitems();
	void ReshuffleAll();
	BOOL HasItems();
	BOOL IsFirstItem();
	BOOL IsLastItem();
	BOOL HasSubitems();
	BOOL IsFirstSubitem();
	BOOL IsLastSubitem();
	void SetSlideShowType(SlideShowType type) noexcept;
	SlideShowType GetSlideShowType() const noexcept;
	void SetSlideShowSpeed(SlideShowSpeed speed);
	SlideShowSpeed GetSlideShowSpeed() const noexcept;
protected:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	DECLARE_MESSAGE_MAP()

private:
	void CalcZoom();
	void CalcDrawPoint();
	void CalcFocusPoint();
	Image* m_CurImage;
	CSlideShowItem m_Items;
	BOOL m_Playing;
	BOOL m_StretchToFit;
	BOOL m_ShuffleItems;
	BOOL m_ShuffleSubitems;
	BOOL m_LoopItems;
	BOOL m_LoopSubitems;
	SlideShowType m_SlideShowType;
	SlideShowSpeed m_SlideShowSpeed;
	double m_Zoom;
	BOOL m_ManualZoom;
	CPoint m_Focus;
	CPoint m_Draw;
	CPoint m_CapturePoint;
	CSize m_Size;
};
