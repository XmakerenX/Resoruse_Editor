#include "CCheckboxUI.h"
#include "CDialogUI.h"

//-----------------------------------------------------------------------------
// Name : CCheckboxUI (Constructor)
//-----------------------------------------------------------------------------
CCheckboxUI::CCheckboxUI(int ID, int x, int y, UINT width, UINT height, UINT nHotkey)
:CButtonUI(ID, "", x, y, width, height, nHotkey)
{
	m_type = CHECKBOX;
	m_bChecked = false;
}

//-----------------------------------------------------------------------------
// Name : CCheckboxUI (destructor)
//-----------------------------------------------------------------------------
CCheckboxUI::~CCheckboxUI(void)
{
}

//-----------------------------------------------------------------------------
// Name : Render ()
//-----------------------------------------------------------------------------
void CCheckboxUI::Render( CAssetManager& assetManger)
{
	HRESULT hr;
	LPDIRECT3DTEXTURE9 pTexture;
	RECT rcWindow;

	//no texture was given abort rendering
	if (m_elementsGFX.size() < 2 || m_elementsGFX[BUTTON].iTexture == -1 || m_elementsGFX[MOUSEOVER].iTexture == -1)
		return;

	//acquire a pointer to the texture we need to render the button
	pTexture = assetManger.getTexturePtr(m_elementsGFX[0].iTexture);

	CMySprite* sprite = assetManger.getMySprite();

	//calculate the the button rendering rect
	SetRect(&rcWindow, 0, 0, m_width, m_height);
	OffsetRect(&rcWindow, m_x, m_y);

	POINT dialogPos = m_pParentDialog->getLocation();
	LONG  dialogCaptionHeihgt =  m_pParentDialog->getCaptionHeight();
	dialogPos.y += dialogCaptionHeihgt;

	if (!m_bMouseOver)
	{
		renderRect(m_elementsGFX[BUTTON].rcTexture, rcWindow, sprite, pTexture, D3DCOLOR_ARGB( 255, 200, 200, 200 ), REGLUAR, dialogPos);
		if (m_bChecked)
			renderRect(m_elementsGFX[MOUSEOVER].rcTexMouseOver, rcWindow, sprite, pTexture,  D3DCOLOR_ARGB( 255, 200, 200, 200 ), REGLUAR, dialogPos);
	}
	else
	{
		// if the button is pressed and the cursor is on it darken it to showed it is pressed
		if (m_bMouseOver && m_bPressed)
		{
			renderRect(m_elementsGFX[BUTTON].rcTexture, rcWindow, sprite, pTexture, D3DCOLOR_ARGB( 255, 150, 150, 150 ), REGLUAR, dialogPos );
			if (m_bChecked)
				renderRect(m_elementsGFX[MOUSEOVER].rcTexMouseOver, rcWindow, sprite, pTexture, D3DCOLOR_ARGB( 255, 150, 150, 150 ), REGLUAR, dialogPos);
		}
		else
			// if the button has the cursor on it high light 
			if (m_bMouseOver)
			{
				//drawButtonRect(m_controlGfx.rcTexMouseOver, rcWindow, sprite, pTexture, D3DCOLOR_ARGB( 200, 250, 250, 250 ));
				renderRect(m_elementsGFX[BUTTON].rcTexture, rcWindow, sprite, pTexture, D3DCOLOR_ARGB( 255, 255, 255, 255 ), HiGHLIGHT, dialogPos);
				if (m_bChecked)
					renderRect(m_elementsGFX[MOUSEOVER].rcTexMouseOver, rcWindow, sprite, pTexture, D3DCOLOR_ARGB( 255, 255, 255, 255 ), HiGHLIGHT, dialogPos);
			}
	}
}

//-----------------------------------------------------------------------------
// Name : HandleKeyboard ()
//-----------------------------------------------------------------------------
bool CCheckboxUI::HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	//TODO: implement the HandleKeyboard and check why keyboard messages seems to not work...
	return false;
}

//-----------------------------------------------------------------------------
// Name : HandleMouse ()
//-----------------------------------------------------------------------------
bool CCheckboxUI::HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam, CTimer* timer )
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		{
			if ( ContainsPoint( pt ) )
			{
				m_bPressed = true;

				SetCapture(hWnd);

				if( !m_bHasFocus )
					m_pParentDialog->RequestFocus( this );

				return true;

			}
		}break;

	case WM_LBUTTONUP:
		{
			if (m_bPressed)
			{
				m_bPressed = false;

				ReleaseCapture();

				if (ContainsPoint(pt))
				{
					m_bChecked = !m_bChecked;
					m_pParentDialog->SendEvent(2, true, m_ID, hWnd);
				}

				return true;
			}
		}break;
	}

	return false;
}