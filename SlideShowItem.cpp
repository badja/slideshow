// SlideShowItem.cpp : implementation file
//

#include "stdafx.h"
#include "SlideShow.h"
#include "SlideShowItem.h"


// CSlideShowItem

IMPLEMENT_SERIAL(CSlideShowItem, CObject, 1)

CSlideShowItem::CSlideShowItem()
{
	Clear();
}

CSlideShowItem::~CSlideShowItem()
{
}


// CItem member functions

void CSlideShowItem::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{	// storing code
		ar << m_FileName;
		ar << m_CurrentPosition;
		ar << m_UsingShuffle;
		ar << m_BackCount;
	}
	else
	{	// loading code
		ar >> m_FileName;
		ar >> m_CurrentPosition;
		ar >> m_UsingShuffle;
		ar >> m_BackCount;
	}

	m_Subitems.Serialize(ar);
	m_ShuffledPositions.Serialize(ar);
}

void CSlideShowItem::Clear()
{
	m_FileName.Empty();
	m_Subitems.RemoveAll();
	m_ShuffledPositions.RemoveAll();
	m_CurrentPosition = -1;
	m_UsingShuffle = FALSE;
	m_BackCount = 0;
}

void CSlideShowItem::Initialise(CString Path)
{
	Clear();

	return SetItem(Path, Path, TRUE);
}

void CSlideShowItem::SetShuffle(int Level, BOOL Shuffle)
{
	if (Level > 0)
	{
		// Go deeper one level
		CSlideShowItem* pItem = GetCurrentSubitem();
		if (pItem)
			return pItem->SetShuffle(Level - 1, Shuffle);
	}
	else
	{
		// If changing to non-shuffle, update current position so that we're still pointing to the same item
		if (m_UsingShuffle && !Shuffle)
			m_CurrentPosition = m_ShuffledPositions[GetCurrentPosition()];

		m_UsingShuffle = Shuffle;
	}
}

BOOL CSlideShowItem::NextItem(int Level, BOOL Loop, BOOL LevelShuffle, BOOL SubLevelShuffle)
{
	if (Level > 0)
	{
		// Go deeper one level
		CSlideShowItem* pItem = GetCurrentSubitem();
		if (pItem)
			return pItem->NextItem(Level - 1, Loop, LevelShuffle, SubLevelShuffle);
	}
	else
	{
		// Return if there are no subitems
		INT_PTR SubitemCount = m_Subitems.GetCount();
		if (SubitemCount == 0)
			return FALSE;

		// If changing to non-shuffle, update current position so that we're still pointing to the same item
		if (m_UsingShuffle && !LevelShuffle)
			m_CurrentPosition = m_ShuffledPositions[GetCurrentPosition()];

		// Increment current position, looping if necessary
		if (m_CurrentPosition < SubitemCount - 1)
		{
			m_CurrentPosition++;
		}
		else
		{
			if (!Loop)
				return FALSE;

			m_CurrentPosition = 0;
		}

		m_UsingShuffle = LevelShuffle;

		// Unless user has been backtracking, move to the next subitem too so that we get a different picture
		if (m_BackCount > 0)
		{
			m_BackCount--;
		}
		else
		{
			CSlideShowItem* pItem = GetCurrentSubitem();
			if (pItem)
				pItem->NextItem(0, TRUE, SubLevelShuffle, SubLevelShuffle);
		}
	}

	return TRUE;
}

BOOL CSlideShowItem::PreviousItem(int Level, BOOL Loop, BOOL LevelShuffle)
{
	if (Level > 0)
	{
		// Go deeper one level
		CSlideShowItem* pItem = GetCurrentSubitem();
		if (pItem)
			return pItem->PreviousItem(Level - 1, Loop, LevelShuffle);
	}
	else
	{
		// Return if there are no subitems
		INT_PTR SubitemCount = m_Subitems.GetCount();
		if (SubitemCount == 0)
			return FALSE;

		// If changing to non-shuffle, update current position so that we're still pointing to the same item
		if (m_UsingShuffle && !LevelShuffle)
			m_CurrentPosition = m_ShuffledPositions[GetCurrentPosition()];

		// Decrement current position, looping if necessary
		if (m_CurrentPosition > 0)
		{
			m_CurrentPosition--;
		}
		else
		{
			if (!Loop)
				return FALSE;

			m_CurrentPosition = SubitemCount - 1;
		}

		m_UsingShuffle = LevelShuffle;

		m_BackCount++;
	}

	return TRUE;
}

void CSlideShowItem::ResetBackCount()
{
	m_BackCount = 0;

	INT_PTR SubitemsSize = m_Subitems.GetCount();

	for (INT_PTR i = 0; i < SubitemsSize; i++)
		m_Subitems[i].ResetBackCount();
}

BOOL CSlideShowItem::Home(int Level)
{
	if (Level > 0)
	{
		// Go deeper one level
		CSlideShowItem* pItem = GetCurrentSubitem();
		if (pItem)
			return pItem->Home(Level - 1);
	}
	else
	{
		// Return if there are no subitems
		INT_PTR SubitemCount = m_Subitems.GetCount();
		if (SubitemCount == 0)
			return FALSE;

		if (m_CurrentPosition <= 0)
			return FALSE;

		m_BackCount += m_CurrentPosition;
		m_CurrentPosition = 0;
	}

	return TRUE;
}

void CSlideShowItem::HomeAll()
{
	m_BackCount = 0;

	m_CurrentPosition = -1;

	INT_PTR SubitemsSize = m_Subitems.GetCount();

	for (INT_PTR i = 0; i < SubitemsSize; i++)
		m_Subitems[i].HomeAll();
}

void CSlideShowItem::Reshuffle(int Level)
{
	if (Level > 0)
	{
		// Go deeper one level
		CSlideShowItem* pItem = GetCurrentSubitem();
		if (pItem)
			pItem->Reshuffle(Level - 1);
	}
	else
	{
		ShufflePositions();
	}
}

void CSlideShowItem::ReshuffleAll()
{
	m_BackCount = 0;

	ShufflePositions();

	INT_PTR SubitemsSize = m_Subitems.GetCount();

	for (INT_PTR i = 0; i < SubitemsSize; i++)
		m_Subitems[i].ReshuffleAll();
}

BOOL CSlideShowItem::HasItems(int Level)
{
	if (Level > 0)
	{
		// Go deeper one level
		CSlideShowItem* pItem = GetCurrentSubitem();
		if (pItem)
			return pItem->HasItems(Level - 1);
	}

	return m_Subitems.GetCount() > 0;
}

BOOL CSlideShowItem::IsFirstItem(int Level)
{
	if (Level > 0)
	{
		// Go deeper one level
		CSlideShowItem* pItem = GetCurrentSubitem();
		if (pItem)
			return pItem->IsFirstItem(Level - 1);
	}

	INT_PTR Count = m_Subitems.GetCount();
	return Count == 0 || m_CurrentPosition <= 0;
}

BOOL CSlideShowItem::IsLastItem(int Level)
{
	if (Level > 0)
	{
		// Go deeper one level
		CSlideShowItem* pItem = GetCurrentSubitem();
		if (pItem)
			return pItem->IsLastItem(Level - 1);
	}

	INT_PTR Count = m_Subitems.GetCount();
	return Count == 0 || m_CurrentPosition == (Count - 1);
}

CString CSlideShowItem::GetCurrentFileName(BOOL Recursive, BOOL FullPath)
{
	if (Recursive)
	{
		CSlideShowItem* pItem = GetCurrentSubitem();
		if (pItem)
		{
			if (FullPath)
				return m_FileName + _T('\\') + pItem->GetCurrentFileName(Recursive, FullPath);
			else
				return pItem->GetCurrentFileName(Recursive, FullPath);
		}
	}

	return m_FileName;
}

void CSlideShowItem::SetItem(CString Path, CString FileName, BOOL IsDirectory)
{
	m_FileName = FileName;

	if (IsDirectory)
	{
		CFileFind Finder;
		BOOL Ret = Finder.FindFile(Path + _T("\\*.*"));

		while (Ret)
		{
			Ret = Finder.FindNextFile();

			if (Finder.IsDots() || Finder.IsHidden())
				continue;

			INT_PTR PrevSize = m_Subitems.GetCount();
			m_Subitems.SetSize(PrevSize + 1);
			CSlideShowItem& Item = m_Subitems.GetAt(PrevSize);

			if (Finder.IsDirectory())
				Item.SetItem(Finder.GetFilePath(), Finder.GetFileName(), TRUE);
			else
				Item.SetItem(Path, Finder.GetFileName(), FALSE);
		}

		ShufflePositions();
	}
}

void CSlideShowItem::ShufflePositions()
{
	INT_PTR j;
	INT_PTR SubitemsSize = m_Subitems.GetCount();

	// If there are subitems, shuffle positions into m_ShuffledPositions
	if (SubitemsSize > 0)
	{
		m_ShuffledPositions.SetSize(SubitemsSize);
		m_ShuffledPositions[0] = 0;

		for (INT_PTR i = 1; i < SubitemsSize; i++)
		{
			j = rand() % (i + 1);
			m_ShuffledPositions[i] = m_ShuffledPositions[j];
			m_ShuffledPositions[j] = i;
		}
	}
}

INT_PTR CSlideShowItem::GetCurrentPosition()
{
	return max(0, m_CurrentPosition);
}

CSlideShowItem* CSlideShowItem::GetCurrentSubitem()
{
	if (m_ShuffledPositions.IsEmpty())
		return NULL;

	INT_PTR pos = GetCurrentPosition();

	if (m_UsingShuffle)
		pos = m_ShuffledPositions[pos];

	return &m_Subitems[pos];
}
