#include "CControlUI.h"
#include "CDialogUI.h"

//-----------------------------------------------------------------------------
// Name : CControlUI(constructor) 
//-----------------------------------------------------------------------------
CControlUI::CControlUI(void)
{
	m_pParentDialog = NULL;

	m_x = 0;
	m_y = 0;

	m_width  = 0;
	m_height = 0;

	m_ID = -1;

	m_bVisible   = false;
	m_bMouseOver = false;
	m_bHasFocus  = false;
	//m_bHasFocus  = false;

}

//-----------------------------------------------------------------------------
// Name : ~CControlUI(destructor) 
//-----------------------------------------------------------------------------
CControlUI::~CControlUI(void)
{
}

//-----------------------------------------------------------------------------
// Name : onInit() 
// Desc : called after the control is created by the dialog
//		  help to initialize sub controls of the control like the scrollbar
//-----------------------------------------------------------------------------
bool CControlUI::onInit()
{
	return true;
}

//-----------------------------------------------------------------------------
// Name : HandleKeyboard() 
// Desc : handles keyboard input
// Note : returns false by default for the basic control class which means
//        the control does nothing with the keyboard input
//-----------------------------------------------------------------------------
bool CControlUI::HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return false;
}

//-----------------------------------------------------------------------------
// Name : HandleMouse() 
// Desc : handles mouse input
// Note : returns false by default for the basic control class which means
//        the control does nothing with the mouse input
//-----------------------------------------------------------------------------
bool CControlUI::HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam, CTimer* timer )
{
	return false;
}

//-----------------------------------------------------------------------------
// Name : HandleMouse() 
// Desc : handles windows messages while control is focused
// Note : returns false by default for the basic control class which means
//        the control does nothing with the windows messages
//-----------------------------------------------------------------------------
bool CControlUI::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return false;
}

//-----------------------------------------------------------------------------
// Name : ContainsPoint() 
// Desc : check if the given point is inside the control
//-----------------------------------------------------------------------------
BOOL CControlUI::ContainsPoint(POINT pt)
{
	RECT rcBoundingBox;
	SetRect( &rcBoundingBox, m_x, m_y, m_x + m_width, m_y + m_height );
	return PtInRect( &rcBoundingBox, pt );
}

//-----------------------------------------------------------------------------
// Name : onMouseEnter() 
//-----------------------------------------------------------------------------
void CControlUI::onMouseEnter()
{
	m_bMouseOver = true;
}

//-----------------------------------------------------------------------------
// Name : onMouseLeave() 
//-----------------------------------------------------------------------------
void CControlUI::onMouseLeave()
{
	m_bMouseOver = false;
}

//-----------------------------------------------------------------------------
// Name : SetID ()
//-----------------------------------------------------------------------------
void CControlUI::SetID(int ID)
{
	m_ID = ID;
}

//-----------------------------------------------------------------------------
// Name : setLocation ()
//-----------------------------------------------------------------------------
void CControlUI::setLocation(int x, int y)
{
	m_x = x;
	m_y = y;
	UpdateRects();
}

//-----------------------------------------------------------------------------
// Name : setSize ()
//-----------------------------------------------------------------------------
void CControlUI::setSize(UINT width, UINT height)
{
	m_width = width;
	m_height = height;
	UpdateRects();
}

//-----------------------------------------------------------------------------
// Name : setParent ()
//-----------------------------------------------------------------------------
void CControlUI::setParent(CDialogUI* pParentDialog)
{
	m_pParentDialog = pParentDialog;
}

//-----------------------------------------------------------------------------
// Name : setControlGFX ()
//-----------------------------------------------------------------------------
void CControlUI::setControlGFX(std::vector<ELEMENT_GFX>& elementsGFX)
{
	m_elementsGFX = elementsGFX;
}

//-----------------------------------------------------------------------------
// Name : setControlFonts ()
//-----------------------------------------------------------------------------
void CControlUI::setControlFonts(std::vector<ELEMENT_FONT>& elementsFonts)
{
	m_elementsFonts = elementsFonts;
}

//-----------------------------------------------------------------------------
// Name : getType ()
//-----------------------------------------------------------------------------
UINT CControlUI::getType()
{
	return m_type;
}

//-----------------------------------------------------------------------------
// Name : renderRect ()
// Desc : render a Rect using the given texture and texture Rect
// Note : the function also scale the texture to fit the Rect being rendered
//-----------------------------------------------------------------------------
void CControlUI::renderRect(RECT& rcTexture, RECT& rcWindow, CMySprite* sprite, LPDIRECT3DTEXTURE9 pTexture, D3DCOLOR color, bool bHighLight, bool bTop, POINT offset)
{
	UINT m_texWidth = rcTexture.right - rcTexture .left;
	UINT m_texHeight = rcTexture.bottom - rcTexture.top;

	//D3DXMATRIXA16 matTransform;
	//D3DXMatrixScaling( &matTransform, fScaleX, fScaleY, 1.0f );

	//sprite->SetTransform( &matTransform );
	if (pTexture)
	{
		float fScaleX = ( float )(rcWindow.right - rcWindow.left)  / m_texWidth;
		float fScaleY = ( float )(rcWindow.bottom- rcWindow.top)   / m_texHeight;

		sprite->setScale(fScaleX, fScaleY);
	}
	else
		sprite->setScale(1,1);

	POINT pos;
	pos.x = rcWindow.left + offset.x;
	pos.y = rcWindow.top + offset.y;
	//D3DXVECTOR3 vPos( (float)rcWindow.left , (float)rcWindow.top, 0.0f);

	// 	vPos.x /= fScaleX;
	// 	vPos.y /= fScaleY;

	//pos.x /= fScaleX;
	//pos.y /= fScaleY;

	if (pTexture)
		sprite->createQuad(pTexture, rcTexture, pos, color, bHighLight, bTop);
	else
		sprite->createQuad(pTexture, rcWindow, pos, color, bHighLight, bTop);
	//sprite->Draw( pTexture, &rcTexture, NULL, &vPos, color);
}

//-----------------------------------------------------------------------------
// Name : RenderText ()
// Desc : Render the text store in the static to the screen 
//-----------------------------------------------------------------------------
void CControlUI::RenderText(const char strText[], RECT rcDest, LPD3DXFONT pFont, DWORD format, LPD3DXSPRITE pSprite, D3DCOLOR textColor, POINT offset)
{
	// checks the parameters are valid
	if (!strText || !pFont ||  !pSprite || strText[0] == '\0')
		return;

	OffsetRect(&rcDest, offset.x, offset.y);

	//pFont->DrawTextA(pSprite, strText, -1, &rcDest,/* DT_NOCLIP |*/ DT_CENTER | DT_VCENTER ,textColor);
	pFont->DrawTextA(pSprite, strText, -1, &rcDest, format ,textColor);

}

//-----------------------------------------------------------------------------
// Name : UpdateRects 
//-----------------------------------------------------------------------------
void CControlUI::UpdateRects()
{
	SetRect( &m_rcBoundingBox, m_x, m_y, m_x + m_width, m_y + m_height );
}

//-----------------------------------------------------------------------------
// Name : CanHaveFocus 
//-----------------------------------------------------------------------------
bool CControlUI::CanHaveFocus()
{
	return false;
}

//-----------------------------------------------------------------------------
// Name : OnFocusIn 
//-----------------------------------------------------------------------------
void CControlUI::OnFocusIn()
{
	m_bHasFocus = true;
}

//-----------------------------------------------------------------------------
// Name : OnFocusOut 
//-----------------------------------------------------------------------------
void CControlUI::OnFocusOut()
{
	m_bHasFocus = false;
}

//-----------------------------------------------------------------------------
// Name : setEnabled 
//-----------------------------------------------------------------------------
void CControlUI::setEnabled(bool bEnabled)
{
	m_bEnabled = bEnabled;
}

//-----------------------------------------------------------------------------
// Name : getEnabled 
//-----------------------------------------------------------------------------
bool CControlUI::getEnabled()
{
	return m_bEnabled;
}

//-----------------------------------------------------------------------------
// Name : getParentDialog 
//-----------------------------------------------------------------------------
CDialogUI* CControlUI::getParentDialog()
{
	return m_pParentDialog;
}

//-----------------------------------------------------------------------------
// Name : getID 
//-----------------------------------------------------------------------------
int CControlUI::getID()
{
	return m_ID;
}