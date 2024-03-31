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

	CSlideShowCtrl();
	virtual ~CSlideShowCtrl();

	virtual void Serialize(CArchive& ar);

	void SetFolder(CString Dir);
	void CloseFolder();
	CString GetFolder();
	CString GetCurrentFileName();
	void DisplayCurrentImage();
	void Start();
	void Stop();
	BOOL IsPlaying();
	void SetStretchToFit(BOOL Stretch);
	BOOL GetStretchToFit();
	void SetShuffleItems(BOOL Shuffle);
	BOOL GetShuffleItems();
	void SetShuffleSubitems(BOOL Shuffle);
	BOOL GetShuffleSubitems();
	void SetLoopItems(BOOL Loop);
	BOOL GetLoopItems();
	void SetLoopSubitems(BOOL Loop);
	BOOL GetLoopSubitems();
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
	void SetSlideShowType(SlideShowType type);
	SlideShowType GetSlideShowType();
	void SetSlideShowSpeed(SlideShowSpeed speed);
	SlideShowSpeed GetSlideShowSpeed();
protected:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	Image *m_CurImage;
	CSlideShowItem m_Items;
	BOOL m_Playing;
	BOOL m_StretchToFit;
	BOOL m_ShuffleItems;
	BOOL m_ShuffleSubitems;
	BOOL m_LoopItems;
	BOOL m_LoopSubitems;
	SlideShowType m_SlideShowType;
	SlideShowSpeed m_SlideShowSpeed;
};
