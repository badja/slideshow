#pragma once
#include <span>

// CSlideShowItem command target

class CSlideShowItem : public CObject
{
public:
	DECLARE_SERIAL(CSlideShowItem)

	CSlideShowItem() noexcept;

	virtual void Serialize(CArchive& ar);

	void Clear();
	void Initialise(CString Path);
	void SetShuffle(int Level, BOOL Shuffle);
	BOOL NextItem(int Level, BOOL Loop, BOOL LevelShuffle, BOOL SubLevelShuffle);
	BOOL PreviousItem(int Level, BOOL Loop, BOOL LevelShuffle);
	void ResetBackCount();
	BOOL Home(int Level);
	void HomeAll();
	void Reshuffle(int Level);
	void ReshuffleAll();
	BOOL HasItems(int Level);
	BOOL IsFirstItem(int Level);
	BOOL IsLastItem(int Level);
	CString GetCurrentFileName(BOOL Recursive, BOOL FullPath);

private:
	void SetItem(CString Path, CString FileName, BOOL IsDirectory);
	void ShufflePositions();
	INT_PTR GetCurrentPosition() const noexcept;
	CSlideShowItem* GetCurrentSubitem();

	CString m_FileName;
	CArray<CSlideShowItem> m_Subitems;
	CArray<INT_PTR> m_ShuffledPositions;
	INT_PTR m_CurrentPosition;
	BOOL m_UsingShuffle;
	INT_PTR m_BackCount;
};

template<class TYPE>
void AFXAPI SerializeElements(CArchive& ar, CSlideShowItem* pElements, INT_PTR nCount)
{
	if (!pElements)
		return;

	std::span Elements{ pElements, static_cast<UINT>(nCount) };
	for (auto& e : Elements)
		e.Serialize(ar);
}
