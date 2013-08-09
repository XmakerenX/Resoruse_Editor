#include "CButtonUI.h"
#include "CDialogUI.h"

//-----------------------------------------------------------------------------
// Name : CButtonUI (constructor)
//-----------------------------------------------------------------------------
// CButtonUI::CButtonUI(void)
// {
// 	m_bPressed = false;
// 	m_nHotkey = 0;
// 
// 	m_strText[0] = '\0'; 
// 
// 	m_textColor = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
// }

//-----------------------------------------------------------------------------
// Name : CButtonUI (constructor)
//-----------------------------------------------------------------------------
CButtonUI::CButtonUI(int ID, LPCTSTR strText, int x, int y, UINT width, UINT height, UINT nHotkey)
	:CStaticUI(ID, strText, x, y, width, height)
{
	m_type = CControlUI::BUTTON;
	//m_ID = ID;

	//strcpy_s(m_strText,MAX_PATH, strText);

	//m_x = x;
	//m_y = y;

	//m_width = width;
	//m_height = height;

	m_nHotkey = nHotkey;

	m_bPressed = false;

	//m_fontIndex = fontIndex;

	//m_controlGfx.iTexture = -1;

	m_textColor = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
}
//-----------------------------------------------------------------------------
// Name : CButtonUI (detractor)
//-----------------------------------------------------------------------------
CButtonUI::~CButtonUI(void)
{
}

//-----------------------------------------------------------------------------
// Name : Render ()
// Desc : renders the button 
//-----------------------------------------------------------------------------
void CButtonUI::Render( CAssetManager& assetManger)
{
	HRESULT hr;
	LPDIRECT3DTEXTURE9 pTexture;
	
	//no texture was given abort rendering
	if (m_elementsGFX.size() < 2 ||m_elementsGFX[BUTTON].iTexture == -1 || m_elementsGFX[MOUSEOVER].iTexture == -1)
		return;

	//acquire a pointer to the texture we need to render the button
	pTexture = assetManger.getTexturePtr(m_elementsGFX[0].iTexture);

	RECT rcWindow;

// 	LPD3DXSPRITE sprite = assetManger.getSprite();
// 	if (!sprite)
// 		return;

	CMySprite* sprite = assetManger.getMySprite();

	//calculate the the button rendering rect
	SetRect(&rcWindow, 0, 0, m_width, m_height);
	OffsetRect(&rcWindow, m_x , m_y);

	POINT dialogPos = m_pParentDialog->getLocation();
	LONG  dialogCaptionHeihgt =  m_pParentDialog->getCaptionHeight();
	dialogPos.y += dialogCaptionHeihgt;

	//if the button is not pressed or doesn't have the cursor on it render it normally
	if (!m_bMouseOver)
	{
		renderRect(m_elementsGFX[BUTTON].rcTexture, rcWindow, sprite, pTexture, D3DCOLOR_ARGB( 255, 200, 200, 200 ), REGLUAR, dialogPos );
	}
	else
	{
		// if the button is pressed and the cursor is on it darken it to showed it is pressed
		if (m_bMouseOver && m_bPressed)
			renderRect(m_elementsGFX[MOUSEOVER].rcTexMouseOver, rcWindow, sprite, pTexture, D3DCOLOR_ARGB( 255, 150, 150, 150 ), REGLUAR, dialogPos );
		else
			// if the button has the cursor on it high light 
			if (m_bMouseOver)
				//drawButtonRect(m_controlGfx.rcTexMouseOver, rcWindow, sprite, pTexture, D3DCOLOR_ARGB( 200, 250, 250, 250 ));
				renderRect(m_elementsGFX[MOUSEOVER].rcTexMouseOver, rcWindow, sprite, pTexture, D3DCOLOR_ARGB( 255, 255, 255, 255 ), HiGHLIGHT, dialogPos);
	}
	
	LPD3DXFONT pFont;
	//acquire a pointer to the font we need to use to render the text
	if (m_elementsFonts.size() > 0)
		pFont = assetManger.getFontPtr(m_elementsFonts[0].fontIndex);
	else
		return;

	// continue to render the text only if we got a valid pointer
	if (pFont)
	{
		LPD3DXSPRITE pSprite = assetManger.getSprite();

		if (!pSprite)
			return;

		SetRect(&rcWindow, 0, 0, m_width, m_height);
		OffsetRect(&rcWindow, m_x + dialogPos.x, m_y + dialogPos.y);

		D3DXMATRIXA16 matTransform;
		D3DXMatrixScaling( &matTransform, 1.0f, 1.0f, 1.0f );

		pSprite->SetTransform( &matTransform );

		pFont->DrawTextA(pSprite, m_strText, -1, &rcWindow, DT_NOCLIP | DT_CENTER | DT_VCENTER, m_textColor);
	}
}

//-----------------------------------------------------------------------------
// Name : HandleMouse ()
// Desc : handles mouse events for this button
//-----------------------------------------------------------------------------
bool CButtonUI::HandleMouse(HWND hWnd,UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam, CTimer* timer )
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

				//TODO: something here about keyboard input from dialog...

				if (ContainsPoint(pt))
					m_pParentDialog->SendEvent(1, true, m_ID, hWnd);

				return true;
			}
		}break;
	}

	return false;
}

//-----------------------------------------------------------------------------
// Name : HandleKeyboard ()
// Desc : handles keyboard events for this button
//-----------------------------------------------------------------------------
bool CButtonUI::HandleKeyboard(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_SPACE:
				m_bPressed = true;
				return true;
			};
		}break;
		
	case WM_KEYUP:
		{
			switch(wParam)
			{
			case VK_SPACE:
				{
					if ( m_bPressed == true )
					{
						m_bPressed = false;
						m_pParentDialog->SendEvent(1, true, m_ID, hWnd);
						return true;
					}
				}break;
			}
		}

	}

	return false;
}

//-----------------------------------------------------------------------------
// Name : setHotKey ()
//-----------------------------------------------------------------------------
void CButtonUI::setHotKey(UINT nHotKey)
{
	m_nHotkey = nHotKey;
}

//-----------------------------------------------------------------------------
// Name : CanHaveFocus ()
//-----------------------------------------------------------------------------
bool CButtonUI::CanHaveFocus()
{
	//return true; 
	return ( m_bVisible && m_bEnabled );
}