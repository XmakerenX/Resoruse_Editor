#ifndef  _CCONTROLUI_H
#define  _CCONTROLUI_H

#include <Windows.h>
#include "../CTimer.h"
#include "../CAssetManager.h"

//-----------------------------------------------------------------------------
// Typedefs, Structures and Enumerators
//-----------------------------------------------------------------------------
#define EVENT_BUTTON_CLICKED                0x0101
#define EVENT_COMBOBOX_SELECTION_CHANGED    0x0201
#define EVENT_RADIOBUTTON_CHANGED           0x0301
#define EVENT_CHECKBOX_CHANGED              0x0401
#define EVENT_SLIDER_VALUE_CHANGED          0x0501
#define EVENT_EDITBOX_STRING                0x0601
// EVENT_EDITBOX_CHANGE is sent when the listbox content changes
// due to user input.
#define EVENT_EDITBOX_CHANGE                0x0602
#define EVENT_LISTBOX_ITEM_DBLCLK           0x0701
// EVENT_LISTBOX_SELECTION is fired off when the selection changes in
// a single selection list box.
#define EVENT_LISTBOX_SELECTION             0x0702
#define EVENT_LISTBOX_SELECTION_END         0x0703

struct ELEMENT_FONT
{
	ELEMENT_FONT::ELEMENT_FONT()
	{
		fontIndex = -1;
		nFontHeight = -1;
		nFontWidth = -1;
	}

	ELEMENT_FONT::ELEMENT_FONT(UINT newFontIndex, UINT newNFontHeight, UINT newNFontWidth)
	{
		fontIndex = newFontIndex;
		nFontHeight = newNFontHeight;  
		nFontWidth = newNFontWidth;
	}

	void ELEMENT_FONT::setFont(UINT newFontIndex, UINT newNFontHeight, UINT newNFontWidth)
	{
		fontIndex = newFontIndex;
		nFontHeight = newNFontHeight;  
		nFontWidth =  newNFontWidth;
	}

	UINT fontIndex;
	LONG nFontHeight;
	LONG nFontWidth;
};

struct ELEMENT_GFX
{
	ELEMENT_GFX::ELEMENT_GFX()
	{
		iTexture = -1;
	}

	ELEMENT_GFX::ELEMENT_GFX(UINT newITexture, RECT newRcTexture, RECT newRcTexMouseOver)
	{
		setGFX(newITexture, newRcTexture, newRcTexMouseOver);
// 		iTexture	   = newITexture;
// 		rcTexture	   = newRcTexture;
// 		rcTexMouseOver = newRcTexMouseOver;
	}

	void ELEMENT_GFX::setGFX(UINT newITexture, RECT newRcTexture, RECT newRcTexMouseOver)
	{
		iTexture	   = newITexture;
		rcTexture	   = newRcTexture;
		rcTexMouseOver = newRcTexMouseOver;
	}

	UINT iTexture;
	RECT rcTexture;
	RECT rcTexMouseOver;

};

//-----------------------------------------------------------------------------
// Classes forward declaration
//-----------------------------------------------------------------------------
class CDialogUI;

//-----------------------------------------------------------------------------
// CControlUI Class declaration
//-----------------------------------------------------------------------------
class CControlUI
{
public:
	//-----------------------------------------------------------------------------
	// Public Enumerators
	//-----------------------------------------------------------------------------
	enum CONTROLS{STATIC, BUTTON, CHECKBOX, RADIOBUTTON, COMBOBOX, EDITBOX, LISTBOX, SCROLLBAR, SLIDER};

	CControlUI(void);
	virtual ~CControlUI(void);

	virtual bool onInit();

	//-------------------------------------------------------------------------
	// functions that handle user input
	//-------------------------------------------------------------------------
	virtual bool    HandleKeyboard		(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool    HandleMouse			(HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam, CTimer* timer );

	//-------------------------------------------------------------------------
	// Windows message handler
	//-------------------------------------------------------------------------
	virtual bool    MsgProc				(UINT uMsg, WPARAM wParam, LPARAM lParam );

// 	virtual bool    HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam );
// 	virtual bool    HandleMouse   ( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam ,CTimer* timer );

	 //TODO: need to decide how time between frames will be given to the render function
	virtual void    Render	(CAssetManager& assetManger) = 0; //pure abstract function 
	
	void	renderRect		(RECT& rcTexture, RECT& rcWindow, CMySprite* sprite, LPDIRECT3DTEXTURE9 pTexture, D3DCOLOR color, STREAMTYPE streamType, POINT offset);
	void	RenderText		(const char strText[], RECT rcDest, LPD3DXFONT pFont, DWORD format, LPD3DXSPRITE pSprite, D3DCOLOR textColor, POINT offset);

	BOOL ContainsPoint(POINT pt);

	virtual void onMouseEnter();
	virtual void onMouseLeave();

	virtual bool CanHaveFocus();
	virtual void OnFocusIn();
	virtual void OnFocusOut();

	void	SetID				(int ID);
	void	setLocation			(int x, int y);
	void	setSize				(UINT width, UINT height);
	void	setParent			(CDialogUI* pParentDialog);
	void    setControlGFX		(std::vector<ELEMENT_GFX>& elementsGFX);
	void    setControlFonts     (std::vector<ELEMENT_FONT>& elementsFonts);
	void	setEnabled			(bool bEnabled);
	void    setVisible			(bool bVisible);

	int		getID				();
	UINT    getType				();
	bool	getEnabled			();
	bool    getVisible			();
	CDialogUI* getParentDialog  ();
	

	virtual void UpdateRects();
protected:

	CDialogUI* m_pParentDialog;

	// Size, scale, and positioning members
	int m_x, m_y;
	int m_width, m_height;

	int m_ID;
	UINT m_type;
	
	RECT m_rcBoundingBox;           // Rectangle defining the active region of the control

	bool m_bVisible;                // Shown/hidden flag
	bool m_bEnabled;                // Enabled/disabled flag

	bool m_bMouseOver;              // Mouse pointer is above control
	bool m_bHasFocus;               // Control has input focus;

	//CONTROL_GFX m_controlGfx;
	std::vector<ELEMENT_GFX>  m_elementsGFX;
	std::vector<ELEMENT_FONT> m_elementsFonts;
// 	UINT m_iTextire;
// 	RECT m_rcTexture;
};

#endif  //_CCONTROLUI_H