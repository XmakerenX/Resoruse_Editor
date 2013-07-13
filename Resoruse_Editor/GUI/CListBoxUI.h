#ifndef  _CLISTBOXUI_H
#define  _CLISTBOXUI_H

#include "CControlUI.h"
#include "CScrollBarUI.h"

//-------------------------------------------------------------------------
// Enumerators and Structures
//-------------------------------------------------------------------------
struct ListBoxItemUI
{
	char strText[256];
	void* pData;

	RECT rcActive;
	bool bSelected;
};

class CListBoxUI : public CControlUI
{
public:
	//-------------------------------------------------------------------------
	// Constructors & Destructors for This Class.
	//-------------------------------------------------------------------------
	CListBoxUI(int ID, int x, int y, int width, int height, DWORD dwStyle);
	virtual ~CListBoxUI(void);

	virtual bool onInit();

	//-------------------------------------------------------------------------
	// functions that handle user Input
	//-------------------------------------------------------------------------
	virtual bool    HandleKeyboard(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam  );
	virtual bool    HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam, CTimer* timer );

	virtual void    Render( CAssetManager& assetManger );
	virtual void    UpdateRects();

	virtual bool    CanHaveFocus();

	DWORD           GetStyle() const;
	void            SetStyle( DWORD dwStyle );
	int             GetSize() const;

	int             GetScrollBarWidth() const;
	void            SetScrollBarWidth( int nWidth );
	void            SetBorder( int nBorder, int nMargin );

	//-------------------------------------------------------------------------
	// functions that ListBox actions
	//-------------------------------------------------------------------------
	HRESULT         AddItem				( const char* strText, void* pData );
	HRESULT         InsertItem			( int nIndex, const char* strText, void* pData );
	void            RemoveItem			( int nIndex );
	void            RemoveItemByData	( void* pData );
	void            RemoveAllItems		();

	ListBoxItemUI*  GetItem				( int nIndex );
	int             GetSelectedIndex	( int nPreviousSelected = -1 );
	ListBoxItemUI*  GetSelectedItem		( int nPreviousSelected = -1 );
	void            SelectItem			( int nNewIndex );

	enum STYLE
	{
		MULTISELECTION = 1
	};

protected:
	RECT m_rcText;      // Text rendering bound
	RECT m_rcSelection; // Selection box bound

	CScrollBarUI m_ScrollBar;
	int m_nSBWidth;

	int m_nBorder;
	int m_nMargin;
	int m_nTextHeight;  // Height of a single line of text
	DWORD m_dwStyle;    // List box style
	int m_nSelected;    // Index of the selected item for single selection list box
	int m_nSelStart;    // Index of the item where selection starts (for handling multi-selection)
	bool m_bDrag;       // Whether the user is dragging the mouse to select

	std::vector<ListBoxItemUI*> m_Items;
};

#endif  //_CLISTBOXUI_H