#include "CStaticUI.h"
#include "CDialogUI.h"

//-----------------------------------------------------------------------------
// Name : CStaticUI (Default Constructor)
//-----------------------------------------------------------------------------
// CStaticUI::CStaticUI(void)
// {
// 	m_strText[0] = '\0';
// 	m_textColor = D3DCOLOR_ARGB(255, 255, 255, 255);
// }

//-----------------------------------------------------------------------------
// Name : CStaticUI (Constructor)
//-----------------------------------------------------------------------------
CStaticUI::CStaticUI(int ID, LPCTSTR strText, int x, int y, UINT width, UINT height)
{
	//sets the Control type
	m_type = STATIC;

	m_ID = ID;

	setText(strText);

	//sets Static location and size
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;

	//sets the color by Default to white
	m_textColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}

//-----------------------------------------------------------------------------
// Name : CStaticUI (Destructor)
//-----------------------------------------------------------------------------
CStaticUI::~CStaticUI(void)
{
}

//-----------------------------------------------------------------------------
// Name : setText ()
// Desc : copy the given string to the static string buffer if no string was given
//	      mark the string as empty using '\0'
//-----------------------------------------------------------------------------
void CStaticUI::setText(const char strText[])
{
	if (strText == NULL)
		m_strText[0] = '\0';
	else
	{
		strcpy_s(m_strText, MAX_PATH, strText);
	}
}

//-----------------------------------------------------------------------------
// Name : setFont ()
//-----------------------------------------------------------------------------
// void CStaticUI::setFont(UINT fontIndex)
// {
// 	m_fontIndex = fontIndex;
// }

//-----------------------------------------------------------------------------
// Name : setText ()
//-----------------------------------------------------------------------------
void CStaticUI::setTextColor(D3DXCOLOR textColor)
{
	m_textColor = textColor;
}

//-----------------------------------------------------------------------------
// Name : getText ()
//-----------------------------------------------------------------------------
const char* CStaticUI::getText() const
{
	return m_strText;
}

//-----------------------------------------------------------------------------
// Name : Render ()
// Desc : Render the text store in the static to the screen 
// TODO : use the RenderText function instead of the code in the render function
//-----------------------------------------------------------------------------
void CStaticUI::Render( CAssetManager& assetManger)
{
	RECT rcWindow;
	// if there is no text in the static no reason to render it
	if (m_strText[0] == '\0')
		return;

	LPD3DXSPRITE pSprite = assetManger.getSprite();

	if (!pSprite)
		return;

	LPD3DXFONT pFont;
	if (m_elementsFonts.size() > 0)
		pFont = assetManger.getFontPtr(m_elementsFonts[0].fontIndex);
	else
		return;

	if (pFont)
	{
		//RECT rcWindow;
		POINT dialogPos = m_pParentDialog->getLocation();
		LONG  dialogCaptionHeihgt =  m_pParentDialog->getCaptionHeight();
		dialogPos.y += dialogCaptionHeihgt;

		SetRect(&rcWindow, 0, 0, m_width, m_height);
		OffsetRect(&rcWindow, m_x + dialogPos.x, m_y + dialogPos.y);

		//Sets the sprite scale to 1 since the buttons and other controls can change the scale
		D3DXMATRIXA16 matTransform;
		D3DXMatrixScaling( &matTransform, 1.0f, 1.0f, 1.0f );

		pSprite->SetTransform( &matTransform );

		pFont->DrawTextA(pSprite, m_strText, -1, &rcWindow,/* DT_NOCLIP |*/ DT_CENTER | DT_VCENTER ,m_textColor);
		//temp = pFont->DrawTextA(pSprite, m_strText, -1, &rcWindow, DT_NOCLIP , m_textColor);
	}
}
