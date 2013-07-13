#ifndef  _CEDITBOXUI_H
#define  _CEDITBOXUI_H

#include <string>
#include <assert.h>
#include "CControlUI.h"

class CEditBoxUI : public CControlUI
{
public:
	//-------------------------------------------------------------------------
	// Constructors & Destructors for This Class.
	//-------------------------------------------------------------------------
	CEditBoxUI(int ID, LPCTSTR strText, int x, int y, int width, int height, CTimer* timer);
	virtual ~CEditBoxUI(void);

	//-------------------------------------------------------------------------
	// Functions that handle user input logic
	//-------------------------------------------------------------------------
	virtual bool    HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam  );
	virtual bool    HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam, CTimer* timer );
	virtual bool    MsgProc( UINT uMsg, WPARAM wParam, LPARAM lParam );

	//-------------------------------------------------------------------------
	// Functions that handle Rendering Logic
	//-------------------------------------------------------------------------
	virtual bool    CanHaveFocus();
	virtual void    OnFocusIn();
	virtual void    OnFocusOut();

	virtual void    UpdateRects();
	virtual void    Render( CAssetManager& assetManger );

	void            SetText( LPCTSTR strText, bool bSelected = false );
	LPCTSTR         GetText();
	int             GetTextLength();
	HRESULT         GetTextCopy(LPSTR strDest, UINT bufferCount );
	void            ClearText();

	virtual void    SetTextColor( D3DCOLOR Color );
	void            SetSelectedTextColor( D3DCOLOR Color );
	void            SetSelectedBackColor( D3DCOLOR Color );

	void            SetCaretColor( D3DCOLOR Color );
	void            SetBorderWidth( int nBorder );
	void            SetSpacing( int nSpacing );

	//void            ParseFloatArray( float* pNumbers, int nCount );
	void            SetTextFloatArray( const float* pNumbers, int nCount );

protected:
	void            PlaceCaret( int nCP );
	void            DeleteSelectionText();
	void            ResetCaretBlink();
	void            CopyToClipboard();
	void            PasteFromClipboard();

	std::string m_Buffer;     // Buffer to hold text
	int m_nBorder;      // Border of the window
	int m_nSpacing;     // Spacing between the text and the edge of border
	RECT m_rcText;       // Bounding rectangle for the text
	RECT            m_rcRender[9];  // Convenient rectangles for rendering elements
	double m_dfBlink;      // Caret blink time in milliseconds
	double m_dfLastBlink;  // Last timestamp of caret blink
	bool m_bCaretOn;     // Flag to indicate whether caret is currently visible
	int m_nCaret;       // Caret position, in characters
	bool m_bInsertMode;  // If true, control is in insert mode. Else, overwrite mode.
	int m_nSelStart;    // Starting position of the selection. The caret marks the end.
	int m_nFirstVisible;// First visible character in the edit control
	D3DCOLOR m_TextColor;    // Text color
	D3DCOLOR m_SelTextColor; // Selected text color
	D3DCOLOR m_SelBkColor;   // Selected background color
	D3DCOLOR m_CaretColor;   // Caret color

	// Mouse-specific
	bool m_bMouseDrag;       // True to indicate drag in progress

	// Static
	static bool s_bHideCaret;   // If true, we don't render the caret.s
};

#endif  //_CEDITBOXUI_H