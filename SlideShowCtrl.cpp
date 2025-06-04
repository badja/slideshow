// SlideShowCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "SlideShowCtrl.h"
#include "Resource.h"

constexpr double ZOOM_INCREMENT = 0.1;
constexpr double ZOOM_MIN = 0.01;
constexpr double ZOOM_MAX = 8.0;


// CSlideShowCtrl

IMPLEMENT_SERIAL(CSlideShowCtrl, CObject, 1)
CSlideShowCtrl::CSlideShowCtrl() noexcept
: m_CurImage(NULL)
, m_Playing(FALSE)
, m_StretchToFit(FALSE)
, m_ShuffleItems(FALSE)
, m_ShuffleSubitems(FALSE)
, m_LoopItems(FALSE)
, m_LoopSubitems(FALSE)
, m_SlideShowType(Items)
, m_SlideShowSpeed(Medium)
, m_Zoom(1.0)
, m_ManualZoom(FALSE)
{
}


BEGIN_MESSAGE_MAP(CSlideShowCtrl, CStatic)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// CSlideShowCtrl message handlers
void CSlideShowCtrl::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{	// storing code
		ar << m_StretchToFit;
		ar << m_ShuffleItems;
		ar << m_ShuffleSubitems;
		ar << m_LoopItems;
		ar << m_LoopSubitems;
		ar << (int)m_SlideShowType;
		ar << (int)m_SlideShowSpeed;
	}
	else
	{	// loading code
		int Enum;
		ar >> m_StretchToFit;
		ar >> m_ShuffleItems;
		ar >> m_ShuffleSubitems;
		ar >> m_LoopItems;
		ar >> m_LoopSubitems;
		ar >> Enum;
		m_SlideShowType = static_cast<SlideShowType>(Enum);
		ar >> Enum;
		m_SlideShowSpeed = static_cast<SlideShowSpeed>(Enum);
	}

	m_Items.Serialize(ar);
}

void CSlideShowCtrl::SetFolder(CString Path)
{
	if (!Path.IsEmpty())
	{
		CWaitCursor Cursor;
		m_Items.Initialise(Path);
		delete m_CurImage;
		m_CurImage = NULL;
		m_Items.NextItem(0, m_LoopItems, m_ShuffleItems, m_ShuffleSubitems);
		DisplayCurrentImage();
	}
}

void CSlideShowCtrl::CloseFolder()
{
	m_Items.Clear();
	DisplayCurrentImage();
}

CString CSlideShowCtrl::GetFolder()
{
	return m_Items.GetCurrentFileName(FALSE, TRUE);
}

CString CSlideShowCtrl::GetCurrentFileName()
{
	return m_Items.GetCurrentFileName(TRUE, TRUE);
}

void CSlideShowCtrl::DisplayCurrentImage()
{
	CString Text(AfxGetAppName());
	CString FileName(m_Items.GetCurrentFileName(TRUE, FALSE));

	if (!FileName.IsEmpty())
		Text += _T(" - ") + FileName;

	AfxGetMainWnd()->SetWindowTextW(Text);

	Image *TempImage;
	TempImage = Image::FromFile(GetCurrentFileName());

	if (TempImage && TempImage->GetLastStatus() == Ok)
	{
		delete m_CurImage;
		m_CurImage = TempImage;
	}
	else if (TempImage)
	{
		delete TempImage;
		m_CurImage = NULL;
	}

	if (HasImage())
	{
		CRect Rect;
		GetClientRect(&Rect);

		CalcZoom();
		CalcDrawPoint();
	}

	Invalidate();
}

BOOL CSlideShowCtrl::HasImage() const noexcept
{
	return m_CurImage != NULL;
}

void CSlideShowCtrl::Start()
{
	UINT Interval{};

	switch (m_SlideShowSpeed)
	{
	case Slow:
		Interval = 10000;
		break;
	case Medium:
	default:
		Interval = 5000;
		break;
	case Fast:
		Interval = 3000;
		break;
	}

	if (m_SlideShowType == Items)
	{
		if (m_Items.IsLastItem(0))
			m_Items.NextItem(0, TRUE, m_ShuffleItems, m_ShuffleSubitems);
	}
	else
	{
		if (m_Items.IsLastItem(1))
			m_Items.NextItem(1, TRUE, m_ShuffleSubitems, m_ShuffleSubitems);
	}

	DisplayCurrentImage();
	SetTimer(100, Interval, NULL);

	m_Playing = TRUE;
}

void CSlideShowCtrl::Stop()
{
	KillTimer(100);

	m_Playing = FALSE;
}

BOOL CSlideShowCtrl::IsPlaying() const noexcept
{
	return m_Playing;
}

void CSlideShowCtrl::ZoomIn(int Increment)
{
	if (HasImage())
	{
		constexpr double Multiplier = 1.0 / ZOOM_INCREMENT;
		m_Zoom = floor(m_Zoom * Multiplier + Increment) / Multiplier;
		m_Zoom = min(m_Zoom, ZOOM_MAX);
		m_ManualZoom = TRUE;

		CalcDrawPoint();
		Invalidate();
	}
}

void CSlideShowCtrl::ZoomOut(int Increment)
{
	if (HasImage())
	{
		constexpr double Multiplier = 1.0 / ZOOM_INCREMENT;
		m_Zoom = ceil(m_Zoom * Multiplier - Increment) / Multiplier;
		m_Zoom = max(m_Zoom, ZOOM_MIN);
		m_ManualZoom = TRUE;

		CalcDrawPoint();
		Invalidate();
	}
}

BOOL CSlideShowCtrl::CanZoomIn() const noexcept
{
	return HasImage() && m_Zoom < ZOOM_MAX;
}

BOOL CSlideShowCtrl::CanZoomOut() const noexcept
{
	return HasImage() && m_Zoom > ZOOM_MIN;
}

void CSlideShowCtrl::Scroll(int DeltaX, int DeltaY)
{
	CRect Rect;
	GetClientRect(&Rect);

	const bool WidthCropped = m_CurImage->GetWidth() * m_Zoom > Rect.Width();
	const bool HeightCropped = m_CurImage->GetHeight() * m_Zoom > Rect.Height();

	if (WidthCropped)
	{
		m_Draw.x -= DeltaX;
		m_Draw.x = min(m_Draw.x, 0);
		m_Draw.x = max(m_Draw.x, static_cast<int>(Rect.Width() - m_CurImage->GetWidth() * m_Zoom));
	}

	if (HeightCropped)
	{
		m_Draw.y -= DeltaY;
		m_Draw.y = min(m_Draw.y, 0);
		m_Draw.y = max(m_Draw.y, static_cast<int>(Rect.Height() - m_CurImage->GetHeight() * m_Zoom));
	}

	CalcFocusPoint();
	Invalidate();
}

void CSlideShowCtrl::SetStretchToFit(BOOL Stretch)
{
	m_StretchToFit = Stretch;

	if (HasImage())
	{
		CalcZoom();
		CalcDrawPoint();

		Invalidate();
	}
}

BOOL CSlideShowCtrl::GetStretchToFit() const noexcept
{
	return m_StretchToFit;
}

void CSlideShowCtrl::SetShuffleItems(BOOL Shuffle)
{
	m_ShuffleItems = Shuffle;
	m_Items.SetShuffle(0, Shuffle);
	m_Items.ResetBackCount();
	DisplayCurrentImage();
}

BOOL CSlideShowCtrl::GetShuffleItems() const noexcept
{
	return m_ShuffleItems;
}

void CSlideShowCtrl::SetShuffleSubitems(BOOL Shuffle)
{
	m_ShuffleSubitems = Shuffle;
	m_Items.SetShuffle(1, Shuffle);
	m_Items.ResetBackCount();
	DisplayCurrentImage();
}

BOOL CSlideShowCtrl::GetShuffleSubitems() const noexcept
{
	return m_ShuffleSubitems;
}

void CSlideShowCtrl::SetLoopItems(BOOL Loop) noexcept
{
	m_LoopItems = Loop;
}

BOOL CSlideShowCtrl::GetLoopItems() const noexcept
{
	return m_LoopItems;
}

void CSlideShowCtrl::SetLoopSubitems(BOOL Loop) noexcept
{
	m_LoopSubitems = Loop;
}

BOOL CSlideShowCtrl::GetLoopSubitems() const noexcept
{
	return m_LoopSubitems;
}

void CSlideShowCtrl::NextItem(BOOL UseShuffleSetting)
{
	BOOL Success = FALSE;

	if (UseShuffleSetting)
		Success = m_Items.NextItem(0, m_LoopItems, m_ShuffleItems, m_ShuffleSubitems);
	else
		Success = m_Items.NextItem(0, m_LoopItems, !m_ShuffleItems, !m_ShuffleSubitems);

	if (Success)
		DisplayCurrentImage();
}

void CSlideShowCtrl::PreviousItem(BOOL UseShuffleSetting)
{
	BOOL Success = FALSE;

	if (UseShuffleSetting)
		Success = m_Items.PreviousItem(0, m_LoopItems, m_ShuffleItems);
	else
		Success = m_Items.PreviousItem(0, m_LoopItems, !m_ShuffleItems);

	if (Success)
		DisplayCurrentImage();
}

void CSlideShowCtrl::NextSubitem(BOOL UseShuffleSetting)
{
	BOOL Success = FALSE;

	if (UseShuffleSetting)
		Success = m_Items.NextItem(1, m_LoopSubitems, m_ShuffleSubitems, m_ShuffleSubitems);
	else
		Success = m_Items.NextItem(1, m_LoopSubitems, !m_ShuffleSubitems, !m_ShuffleSubitems);

	if (Success)
		DisplayCurrentImage();
}

void CSlideShowCtrl::PreviousSubitem(BOOL UseShuffleSetting)
{
	BOOL Success = FALSE;

	if (UseShuffleSetting)
		Success = m_Items.PreviousItem(1, m_LoopSubitems, m_ShuffleSubitems);
	else
		Success = m_Items.PreviousItem(1, m_LoopSubitems, !m_ShuffleSubitems);

	if (Success)
		DisplayCurrentImage();
}

void CSlideShowCtrl::HomeItem()
{
	if (m_Items.Home(0))
		DisplayCurrentImage();
}

void CSlideShowCtrl::HomeSubitem()
{
	if (m_Items.Home(1))
		DisplayCurrentImage();
}

void CSlideShowCtrl::HomeAll()
{
	m_Items.HomeAll();
	NextItem(TRUE);
}

void CSlideShowCtrl::ReshuffleItems()
{
	m_Items.Reshuffle(0);
	DisplayCurrentImage();
}

void CSlideShowCtrl::ReshuffleSubitems()
{
	m_Items.Reshuffle(1);
	DisplayCurrentImage();
}

void CSlideShowCtrl::ReshuffleAll()
{
	m_Items.ReshuffleAll();
	DisplayCurrentImage();
}

BOOL CSlideShowCtrl::HasItems()
{
	return m_Items.HasItems(0);
}

BOOL CSlideShowCtrl::IsFirstItem()
{
	return m_Items.IsFirstItem(0);
}

BOOL CSlideShowCtrl::IsLastItem()
{
	return m_Items.IsLastItem(0);
}

BOOL CSlideShowCtrl::HasSubitems()
{
	return m_Items.HasItems(1);
}

BOOL CSlideShowCtrl::IsFirstSubitem()
{
	return m_Items.IsFirstItem(1);
}

BOOL CSlideShowCtrl::IsLastSubitem()
{
	return m_Items.IsLastItem(1);
}

void CSlideShowCtrl::SetSlideShowType(SlideShowType type) noexcept
{
	m_SlideShowType = type;
}

CSlideShowCtrl::SlideShowType CSlideShowCtrl::GetSlideShowType() const noexcept
{
	return m_SlideShowType;
}

void CSlideShowCtrl::SetSlideShowSpeed(SlideShowSpeed speed)
{
	m_SlideShowSpeed = speed;

	if (m_Playing)
	{
		Stop();
		Start();
	}
}

CSlideShowCtrl::SlideShowSpeed CSlideShowCtrl::GetSlideShowSpeed() const noexcept
{
	return m_SlideShowSpeed;
}

void CSlideShowCtrl::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 100)
	{
		BOOL Success = FALSE;

		if (m_SlideShowType == Items)
			Success = m_Items.NextItem(0, m_LoopItems, m_ShuffleItems, m_ShuffleSubitems);
		else
			Success = m_Items.NextItem(1, m_LoopSubitems, m_ShuffleSubitems, m_ShuffleSubitems);

		if (Success)
			DisplayCurrentImage();
		else
			Stop();
	}

	CStatic::OnTimer(nIDEvent);
}

void CSlideShowCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect Rect;
	GetClientRect(&Rect);
	
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap Bmp;
	Bmp.CreateCompatibleBitmap(&dc, Rect.Width(), Rect.Height());
	const int SavedDC = MemDC.SaveDC();
	MemDC.SelectObject(&Bmp);

	MemDC.FillSolidRect(Rect, RGB(0, 0, 0));

	if (HasImage())
	{
		Graphics TheDC(MemDC.GetSafeHdc());
		TheDC.DrawImage(m_CurImage, m_Draw.x, m_Draw.y, static_cast<INT>(m_CurImage->GetWidth()*m_Zoom), static_cast<INT>(m_CurImage->GetHeight()*m_Zoom));
	}

	dc.BitBlt(0, 0, Rect.Width(), Rect.Height(), &MemDC, 0, 0, SRCCOPY);
	MemDC.RestoreDC(SavedDC);
}

void CSlideShowCtrl::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);

	if (HasImage())
	{
		CRect Rect;
		GetClientRect(&Rect);

		if (m_StretchToFit || m_ManualZoom)
		{
			const double ImageRatio = static_cast<double>(m_CurImage->GetWidth()) / static_cast<double>(m_CurImage->GetHeight());
			const double ViewRatio = static_cast<double>(m_Size.cx) / static_cast<double>(m_Size.cy);

			if (ImageRatio > ViewRatio)
				m_Zoom = m_Zoom * cx / m_Size.cx;
			else
				m_Zoom = m_Zoom * cy / m_Size.cy;
		}
		else
		{
			CalcZoom();
		}

		CalcDrawPoint();
		Invalidate();
	}

	m_Size = CSize(cx, cy);
}

void CSlideShowCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (HasImage())
	{
		SetCapture();
		m_CapturePoint = point;
	}

	CStatic::OnLButtonDown(nFlags, point);
}

void CSlideShowCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	CalcFocusPoint();

	CStatic::OnLButtonUp(nFlags, point);
}

void CSlideShowCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	if (CWnd::GetCapture())
	{
		Scroll(m_CapturePoint.x - point.x, m_CapturePoint.y - point.y);
		m_CapturePoint = point;
	}

	CStatic::OnMouseMove(nFlags, point);
}

BOOL CSlideShowCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta > 0)
		ZoomIn(zDelta / WHEEL_DELTA);
	else if (zDelta < 0)
		ZoomOut(-zDelta / WHEEL_DELTA);

	return CStatic::OnMouseWheel(nFlags, zDelta, pt);
}

void CSlideShowCtrl::CalcZoom()
{
	CRect Rect;
	GetClientRect(&Rect);

	m_Zoom = 1.0;
	if (m_StretchToFit || static_cast<long long>(m_CurImage->GetWidth()) > Rect.Width())
	{
		m_Zoom = static_cast<double>(Rect.Width()) / static_cast<double>(m_CurImage->GetWidth());
	}
	if (m_StretchToFit || static_cast<long long>(m_CurImage->GetHeight()) > Rect.Height())
	{
		m_Zoom = min(m_Zoom, static_cast<double>(Rect.Height()) / static_cast<double>(m_CurImage->GetHeight()));
	}
	m_ManualZoom = FALSE;

	m_Focus.x = m_CurImage->GetWidth() / 2;
	m_Focus.y = m_CurImage->GetHeight() / 2;
}

void CSlideShowCtrl::CalcDrawPoint()
{
	CRect Rect;
	GetClientRect(&Rect);

	const bool WidthCropped = m_CurImage->GetWidth() * m_Zoom > Rect.Width();
	const bool HeightCropped = m_CurImage->GetHeight() * m_Zoom > Rect.Height();

	if (!WidthCropped)
		m_Focus.x = m_CurImage->GetWidth() / 2;

	if (!HeightCropped)
		m_Focus.y = m_CurImage->GetHeight() / 2;

	m_Draw.x = static_cast<int>(Rect.Width() / 2.0 - m_Focus.x * m_Zoom);
	m_Draw.y = static_cast<int>(Rect.Height() / 2.0 - m_Focus.y * m_Zoom);

	const CPoint OldDraw = m_Draw;

	if (WidthCropped)
	{
		m_Draw.x = min(m_Draw.x, 0);
		m_Draw.x = max(m_Draw.x, static_cast<int>(Rect.Width() - m_CurImage->GetWidth() * m_Zoom));
	}
	if (HeightCropped)
	{
		m_Draw.y = min(m_Draw.y, 0);
		m_Draw.y = max(m_Draw.y, static_cast<int>(Rect.Height() - m_CurImage->GetHeight() * m_Zoom));
	}

	if (m_Draw != OldDraw)
		CalcFocusPoint();
}

void CSlideShowCtrl::CalcFocusPoint()
{
	CRect Rect;
	GetClientRect(&Rect);

	m_Focus.x = static_cast<int>((Rect.Width() / 2.0 - m_Draw.x) / m_Zoom);
	m_Focus.y = static_cast<int>((Rect.Height() / 2.0 - m_Draw.y) / m_Zoom);
}
