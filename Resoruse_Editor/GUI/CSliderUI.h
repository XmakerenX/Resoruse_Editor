#ifndef  _CSLIDERUI_H
#define  _CSLIDERUI_H

#include "CControlUI.h"

class CSliderUI : public CControlUI
{
public:
	//-------------------------------------------------------------------------
	// Constructors & Destructors for This Class.
	//-------------------------------------------------------------------------
	CSliderUI( int ID, int x, int y, int width, int height, int min, int max, int nValue );
	virtual ~CSliderUI(void);

	virtual BOOL    ContainsPoint( POINT pt );

	//-------------------------------------------------------------------------
	// functions that handle user input to the control
	//-------------------------------------------------------------------------
	virtual bool    HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam  );
	virtual bool    HandleMouse	  ( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam, CTimer* timer  );

	//-------------------------------------------------------------------------
	// functions that handle Rendering
	//-------------------------------------------------------------------------
	virtual void    UpdateRects();
	virtual bool    CanHaveFocus();

	virtual void    Render( CAssetManager& assetManger );

	void            SetValue( int nValue );
	int             GetValue() const;

	void            GetRange( int& nMin, int& nMax ) const;
	void            SetRange( int nMin, int nMax );

protected:
	void            SetValueInternal( int nValue, bool bFromInput );
	int             ValueFromPos( int x );

	int m_nValue;

	int m_nMin;
	int m_nMax;

	int m_nDragX;      // Mouse position at start of drag
	int m_nDragOffset; // Drag offset from the center of the button
	int m_nButtonX;

	bool m_bPressed;
	RECT m_rcButton;

private:
	enum ELEMENTS{TRACK, BUTTON};
};

#endif  //_CSLIDERUI_H
