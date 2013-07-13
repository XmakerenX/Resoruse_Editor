#include "CDialogUI.h"

CControlUI* CDialogUI::s_pControlFocus = NULL;

//-----------------------------------------------------------------------------
// Name : CDialogUI (constructor)
//-----------------------------------------------------------------------------
CDialogUI::CDialogUI(void)
{
	ZeroMemory(&m_rcBoundingBox, sizeof(m_rcBoundingBox));
	ZeroMemory(&m_rcCaptionBox, sizeof(m_rcCaptionBox));

	m_nCaptionHeight = 18;

	m_bVisible = true;
	m_bCaption = false;
	m_bMinimized = false;
	m_bDrag = false;

	m_x = 0;
	m_y = 0;

	m_width = 0;
	m_height = 0;
	m_texWidth = 0;
	m_texHeight = 0;

	m_texturePath[0] = '\0';
	m_captionText[0] = '\0';

	m_pMouseOverControl = NULL;
}

//-----------------------------------------------------------------------------
// Name : CDialogUI (destructor)
//-----------------------------------------------------------------------------
CDialogUI::~CDialogUI(void)
{
	for (UINT i = 0; i < m_Controls.size(); i++)
	{
		if (m_Controls[i])
		{
			delete m_Controls[i];
			m_Controls[i] = NULL; // just to be safe
		}
	}

	m_Controls.clear();
}

//-----------------------------------------------------------------------------
// Name : init ()
// Desc : initialize the dialog size , texture and caption
//-----------------------------------------------------------------------------
HRESULT CDialogUI::init(UINT width, UINT height, int nCaptionHeight, LPCTSTR captionText, char newTexturePath[MAX_PATH], D3DXCOLOR dialogColor, HWND hWnd, CAssetManager& assetManger)
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DSURFACE_DESC textureDesc;

	//-------------------------------------
	// Init dialog elements
	//-------------------------------------
	// sets dialog size
	setSize(width,height);

	m_nCaptionHeight = nCaptionHeight;
	if (captionText == NULL)
		m_captionText[0] = '\0';
	else
	{
		strcpy_s(m_captionText, MAX_PATH, captionText);
	}

	SetRect(&m_rcBoundingBox, m_x, m_y, m_x + m_width, m_y + m_height);
	SetRect(&m_rcCaptionBox, m_x, m_y , m_x + m_width, m_y + m_nCaptionHeight);

	// sets dialog background texture
	// checks first that there is a texutre to load
	if (newTexturePath[0] == '\0')
	{
		// no texture to load so ignore texutre vars
		m_texturePath[0] = '\0';
		m_texWidth = 0;
		m_texHeight = 0;

	}
	else
	{
		// load the texture for the dialog background
		pTexture = assetManger.getTexture(newTexturePath);
		// get the texture size
		pTexture->GetLevelDesc(0, &textureDesc);

		// sets what part of the  dialog texture to use
		m_texWidth = textureDesc.Width;
		m_texHeight = textureDesc.Height; 

		// save the texture path to load it when device is lost I think...
		strcpy_s(m_texturePath, MAX_PATH, newTexturePath);
	}

	m_dialogColor = dialogColor;
	m_hWnd = hWnd;

	//-------------------------------------
	// init Controls
	//-------------------------------------
	//addButton(2, "button", 50, 100, 150, 50, 0);
	//addButton(3, "Gend", 250, 100, 150, 50, 0);

	//addCheckBox(4, 50, 50, 50, 50 , 0);
	//addRadioButton(5, 50, 20, 50, 50, 0, 1);
	//addRadioButton(6, 250, 20, 50, 50, 0, 1);

// 	addComboBox(5, "ComboBox", 20, 20, 250, 75, 0, fontIndex);
// 	((CComboBoxUI*)m_Controls[2])->SetDropHeight(106);
// 	((CComboBoxUI*)m_Controls[2])->AddItem("Gendlin", NULL);
// 	((CComboBoxUI*)m_Controls[2])->AddItem("Item2", NULL);
// 	((CComboBoxUI*)m_Controls[2])->AddItem("Item3", NULL);
// 	((CComboBoxUI*)m_Controls[2])->AddItem("Item4", NULL);
// 	((CComboBoxUI*)m_Controls[2])->AddItem("Item5", NULL);
// 	((CComboBoxUI*)m_Controls[2])->AddItem("Item6", NULL);
// 	((CComboBoxUI*)m_Controls[2])->AddItem("Item7", NULL);
// 	((CComboBoxUI*)m_Controls[2])->AddItem("Item8", NULL);
// 	((CComboBoxUI*)m_Controls[2])->AddItem("Item9", NULL);
// 	((CComboBoxUI*)m_Controls[2])->AddItem("Item10", NULL);
// 	((CComboBoxUI*)m_Controls[2])->AddItem("Item11", NULL);
// 	((CComboBoxUI*)m_Controls[2])->AddItem("Item12", NULL);
// 	((CComboBoxUI*)m_Controls[2])->AddItem("Item13", NULL);
// 
// 	addListBox(6, 20, 20 ,150, 150, CListBoxUI::MULTISELECTION );
// 	((CListBoxUI*)m_Controls[2])->AddItem("gend1", NULL);
// 	((CListBoxUI*)m_Controls[2])->AddItem("gend2", NULL);
// 	((CListBoxUI*)m_Controls[2])->AddItem("gend3", NULL);
// 	((CListBoxUI*)m_Controls[2])->AddItem("gend4", NULL);
// 	((CListBoxUI*)m_Controls[2])->AddItem("gend5", NULL);
// 	((CListBoxUI*)m_Controls[2])->AddItem("gend6", NULL);
// 	((CListBoxUI*)m_Controls[2])->AddItem("gend7", NULL);
// 	((CListBoxUI*)m_Controls[2])->AddItem("gend8", NULL);
// 	((CListBoxUI*)m_Controls[2])->AddItem("gend9", NULL);
// 	((CListBoxUI*)m_Controls[2])->AddItem("gend10", NULL);
// 
// 	addSlider(7, 20, 20, 200, 50, 0, 100, 50);
// 
// 	addEditbox(8, "The gend is Coming", 20, 20, 200, 50, assetManger.getTimer());
// 
// 	if (!assetManger.getFont(16, 0 ,FW_NORMAL, FALSE, fontIndex))
// 		return S_FALSE;

//	addStatic(20, "This is a static text", 100, 300, 200, 50, fontIndex);
	//addButton(2, "button", 100, 100, 256, 128, 0, fontIndex);
	//m_Controls[0]->setParent(this);

// 	m_button.setLocation(300,100);
// 	m_button.SetID(2);
// 	m_button.setParent(this);
	initDefControlElements(assetManger);

	return S_OK;
}

HRESULT CDialogUI::initDefControlElements(CAssetManager& assetManger)
{
	std::vector<ELEMENT_GFX>  elementGFXvec;
	std::vector<ELEMENT_FONT> elementFontVec;
	CONTROL_GFX	controlGFX;

	UINT textureIndex, fontIndex;

	// create the controls font
	if (!assetManger.getFont(16, 20, FW_BOLD, FALSE, fontIndex))
		return S_FALSE;

	UINT nFontHeight = assetManger.getFontItem(fontIndex).height;
	ELEMENT_FONT elementFont(fontIndex,nFontHeight, assetManger.getFontItem(fontIndex).width);

	ELEMENT_GFX elementGFX;

	//-------------------------------------
	// Init Static elements
	//-------------------------------------
	// sets the Static default font
	// this font is also used for all other controls ... for now..
	// create the controls font
	if (!assetManger.getFont(16, 10, FW_BOLD, FALSE, fontIndex))
		return S_FALSE;

	nFontHeight = assetManger.getFontItem(fontIndex).height;
	ELEMENT_FONT elementFont2(fontIndex,nFontHeight, assetManger.getFontItem(fontIndex).width);

	elementFontVec.push_back(elementFont2);
	elementGFXvec.clear();

	controlGFX.nControlType =  CControlUI::STATIC;
	controlGFX.elementsGFXvec = elementGFXvec;
	controlGFX.elementsFontVec = elementFontVec;
	m_DefControlsGFX.push_back(controlGFX);

	//-------------------------------------
	// Init Button elements
	//-------------------------------------
	// loads the button default texture
	if (!assetManger.getTexture("button.png", &textureIndex))
		return S_FALSE;

	// sets what parts of the texture to use for the button
	RECT rcTexture, rcTexMouseOver;
	SetRect(&rcTexture, 0, 0, 256, 128);

	// add the main button element
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	// add the mouse over button element
	SetRect(&rcTexMouseOver, 0, 128, 256, 256);
	elementGFX.setGFX(textureIndex, rcTexMouseOver, rcTexMouseOver);
	elementGFXvec.push_back(elementGFX);

	// create the button control default GFX and adds to the vector
	controlGFX.nControlType =  CControlUI::BUTTON;
	controlGFX.elementsGFXvec = elementGFXvec;
	controlGFX.elementsFontVec = elementFontVec;
	m_DefControlsGFX.push_back(controlGFX);

	//-------------------------------------
	// Init CheckBox elements
	//-------------------------------------
	elementGFXvec.clear();

	//loads the CheckBox default texture
	if (!assetManger.getTexture("tex.dds", &textureIndex))
		return S_FALSE;

	// sets what parts of the texture to use for the main element of the CheckBox
	SetRect( &rcTexture, 0, 54, 27, 81 );
	// add the main CheckBox element to the vector
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	// sets what parts of the texture to use for the CheckBox mouse over
	SetRect( &rcTexMouseOver, 27, 54, 54, 81 );
	// add the mouse over CheckBox element to the vector
	elementGFX.setGFX(textureIndex, rcTexMouseOver, rcTexMouseOver);
	elementGFXvec.push_back(elementGFX);

	// create the CheckBox control default GFX and adds to the vector
	controlGFX.nControlType = CControlUI::CHECKBOX;
	controlGFX.elementsGFXvec = elementGFXvec;
	controlGFX.elementsFontVec = elementFontVec;
	m_DefControlsGFX.push_back(controlGFX);

	//-------------------------------------
	// Init RadioButton elements
	//-------------------------------------
	elementGFXvec.clear();

	// sets what parts of the texture to use for the main element of the RadioButton
	SetRect( &rcTexture, 54, 54, 81, 81 );
	// add the main element of  RadioButton elements to the vector
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	// sets what parts of the texture to use for the mouse over element of the RadioButton
	SetRect( &rcTexMouseOver, 81, 54, 108, 81 );
	// add the mouse over element of  RadioButton elements to the vector
	elementGFX.setGFX(textureIndex, rcTexMouseOver, rcTexMouseOver);
	elementGFXvec.push_back(elementGFX);

	// create the RadioButton control default GFX and adds to the vector
	controlGFX.nControlType =  CControlUI::RADIOBUTTON;
	controlGFX.elementsGFXvec = elementGFXvec;
	controlGFX.elementsFontVec = elementFontVec;
	m_DefControlsGFX.push_back(controlGFX);

	//-------------------------------------
	// Init ComboBox elements
	//-------------------------------------
	elementGFXvec.clear();

	//-------------------------------------
	// ComboBox - Main
	//-------------------------------------
	SetRect( &rcTexture, 7, 81, 247, 123 );

	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	//-------------------------------------
	// ComboBox - Button
	//-------------------------------------
	SetRect( &rcTexture, 98, 189, 151, 238 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	//-------------------------------------
	// ComboBox - Dropdown
	//-------------------------------------
	SetRect( &rcTexture, 13, 123, 241, 160 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	//-------------------------------------
	// ComboBox - Selection
	//-------------------------------------
	SetRect( &rcTexture, 12, 163, 239, 183 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	// create the ComboBox control default GFX and adds to the vector
	controlGFX.nControlType =  CControlUI::COMBOBOX;
	controlGFX.elementsGFXvec = elementGFXvec;
	controlGFX.elementsFontVec = elementFontVec;
	m_DefControlsGFX.push_back(controlGFX);

	//-------------------------------------
	// Init ScrollBar elements
	//-------------------------------------
	elementGFXvec.clear();

	//-------------------------------------
	// ScrollBar - Track
	//-------------------------------------
	int nScrollBarStartX = 196;
	int nScrollBarStartY = 191;
	SetRect( &rcTexture, nScrollBarStartX + 0, nScrollBarStartY + 21, nScrollBarStartX + 22, nScrollBarStartY + 32 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	//-------------------------------------
	// ScrollBar - Up Arrow
	//-------------------------------------
	SetRect( &rcTexture, nScrollBarStartX + 0, nScrollBarStartY + 1, nScrollBarStartX + 22, nScrollBarStartY + 21 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	//-------------------------------------
	// ScrollBar - Down Arrow
	//-------------------------------------
	SetRect( &rcTexture, nScrollBarStartX + 0, nScrollBarStartY + 32, nScrollBarStartX + 22, nScrollBarStartY + 53 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	//-------------------------------------
	// ScrollBar - Button
	//-------------------------------------
	SetRect( &rcTexture, 220, 192, 238, 234 );
	elementGFX.setGFX(textureIndex, rcTexture,rcTexture);
	elementGFXvec.push_back(elementGFX);

	// create the ScrollBar control default GFX and adds to the vector
	controlGFX.nControlType =  CControlUI::SCROLLBAR;
	controlGFX.elementsGFXvec = elementGFXvec;
	controlGFX.elementsFontVec = elementFontVec;
	m_DefControlsGFX.push_back(controlGFX);

	//-------------------------------------
	// Init ListBox elements
	//-------------------------------------
	elementGFXvec.clear();

	//-------------------------------------
	// ListBox - Main
	//-------------------------------------
	SetRect( &rcTexture, 13, 123, 241, 160 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	//Element.SetFont( 0, D3DCOLOR_ARGB( 255, 0, 0, 0 ), DT_LEFT | DT_TOP );

	//-------------------------------------
	//ListBox - Selection
	//-------------------------------------
	SetRect( &rcTexture, 16, 166, 240, 183 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	// create the ListBox control default GFX and adds to the vector
	controlGFX.nControlType =  CControlUI::LISTBOX;
	controlGFX.elementsGFXvec = elementGFXvec;
	controlGFX.elementsFontVec = elementFontVec;
	m_DefControlsGFX.push_back(controlGFX);

	//-------------------------------------
	// Init Slider elements
	//-------------------------------------
	elementGFXvec.clear();

	//-------------------------------------
	// Slider - Track
	//-------------------------------------
	SetRect( &rcTexture, 1, 187, 93, 228 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	//-------------------------------------
	// Slider - Button
	//-------------------------------------
	SetRect( &rcTexture, 151, 193, 192, 234 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	// create the Slider control default GFX and adds to the vector
	controlGFX.nControlType =  CControlUI::SLIDER;
	controlGFX.elementsGFXvec = elementGFXvec;
	controlGFX.elementsFontVec = elementFontVec;
	m_DefControlsGFX.push_back(controlGFX);

	//-------------------------------------
	// EditBox
	//-------------------------------------
	elementGFXvec.clear();

	// Element assignment:
	//   0 - text area
	//   1 - top left border
	//   2 - top border
	//   3 - top right border
	//   4 - left border
	//   5 - right border
	//   6 - lower left border
	//   7 - lower border
	//   8 - lower right border

	//Element.SetFont( 0, D3DCOLOR_ARGB( 255, 0, 0, 0 ), DT_LEFT | DT_TOP );

	// Assign the style
	SetRect( &rcTexture, 14, 90, 241, 113 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	SetRect( &rcTexture, 8, 82, 14, 90 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	SetRect( &rcTexture, 14, 82, 241, 90 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	SetRect( &rcTexture, 241, 82, 246, 90 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	SetRect( &rcTexture, 8, 90, 14, 113 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	SetRect( &rcTexture, 241, 90, 246, 113 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	SetRect( &rcTexture, 8, 113, 14, 121 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	SetRect( &rcTexture, 14, 113, 241, 121 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	SetRect( &rcTexture, 241, 113, 246, 121 );
	elementGFX.setGFX(textureIndex, rcTexture, rcTexture);
	elementGFXvec.push_back(elementGFX);

	// create the Slider control default GFX and adds to the vector
	controlGFX.nControlType =  CControlUI::EDITBOX;
	controlGFX.elementsGFXvec = elementGFXvec;
	controlGFX.elementsFontVec = elementFontVec;
	m_DefControlsGFX.push_back(controlGFX);
}

//-----------------------------------------------------------------------------
// Name : OnRender ()
// Desc : renders the dialog and all of his controls
//-----------------------------------------------------------------------------
HRESULT CDialogUI::OnRender(float fElapsedTime, D3DXVECTOR3 vPos, LPD3DXEFFECT effect, CAssetManager& assetManger)
{
	LPDIRECT3DTEXTURE9 pTexture = NULL;

	if (m_texturePath[0] != '\0')
	{
		pTexture = assetManger.getTexture(m_texturePath);
		if (!pTexture)
			return E_FAIL;
	}
	else
		pTexture = NULL;

	LPD3DXSPRITE sprite = assetManger.getSprite();
	if (!sprite)
		return S_FALSE;

	LPD3DXSPRITE pTopSprite = assetManger.getTopSprite();
	if (!pTopSprite)
		return S_FALSE;

	CMySprite* pMySprite = assetManger.getMySprite();
	if (!pMySprite)
		return S_FALSE;

	float fScaleX, fScaleY;
	if (pTexture)
	{
 		fScaleX = ( float )m_width  / m_texWidth;
 		fScaleY = ( float )m_height / m_texHeight;
	}
	else
	{
		fScaleX = 1.0f;
		fScaleY = 1.0f;
	}
// 
 	D3DXMATRIXA16 matTransform;
// 	D3DXMatrixScaling( &matTransform, fScaleX, fScaleY, 1.0f );

	//sprite->SetTransform( &matTransform );

	//sprite->Begin(D3DXSPRITE_DONOTMODIFY_RENDERSTATE);

	POINT pos;
	pos.x = m_x;
	pos.y = m_y;

	RECT rcDialogBox;
	if (pTexture)
		SetRect(&rcDialogBox, 0, 0, m_texWidth, m_texHeight);
	else
		SetRect(&rcDialogBox, 0, 0, m_width, m_height);

	pMySprite->setScale(fScaleX, fScaleY);
	pMySprite->createQuad(pTexture, rcDialogBox, pos, m_dialogColor, false, false);
	pMySprite->setScale(1.0f, 1.0f);
	pMySprite->createQuad(NULL, m_rcCaptionBox, pos, D3DCOLOR_ARGB(200,255,0,0), false, true);

	//sprite->Draw( texture, NULL, NULL, &vPos, d3d::WHITE);
	//m_Controls[0]->Render(assetManger);

	D3DXMatrixScaling( &matTransform, 1.0f, 1.0f, 1.0f );

	sprite->SetTransform( &matTransform );

	bool drawFocusedControl = false;

	for(UINT i = 0; i < m_Controls.size(); i++)
	{
		if (m_Controls[i] == s_pControlFocus)
		{
			drawFocusedControl = true;
			continue;
		}

		m_Controls[i]->Render(assetManger);
	}

	if (drawFocusedControl)
			s_pControlFocus->Render(assetManger);

	//pMySprite->render(effect);

	LPD3DXFONT pFont = assetManger.getFontPtr(0);
	if (pFont)
	{
		pFont->DrawTextA(pTopSprite, m_captionText, -1, &m_rcCaptionBox, DT_LEFT, d3d::WHITE);
	}

	//sprite->End();


	return S_OK;
	//sprite->Draw()
}

//-----------------------------------------------------------------------------
// Name : SendEvent ()
// Desc : sends an event to the guiEvent message handler
//-----------------------------------------------------------------------------
void CDialogUI::SendEvent(UINT nEvent, bool bTriggeredByUser, int nControlID, HWND hWnd /*= NULL */)
{
	if (m_pCallbackEvent == NULL)
		return;

	// if a window handle was given use it instead of the window handle stored in the class
	if (hWnd != NULL)
		m_pCallbackEvent(hWnd, nEvent, nControlID, NULL);
	else
		m_pCallbackEvent(hWnd, nEvent, nControlID, NULL);
}

//-----------------------------------------------------------------------------
// Name : MsgProc ()
// Desc : process messages that were sent to the dialog
//-----------------------------------------------------------------------------
bool CDialogUI::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, CTimer* timer )
{
	bool bHandled = false;
	
	// If a control is in focus, it belongs to this dialog, and it's enabled, then give
	// it the first chance at handling the message.
	if( s_pControlFocus &&
		s_pControlFocus->getParentDialog() == this &&
		s_pControlFocus->getEnabled() )
	{
		// If the control MsgProc handles it, then we don't.
		if( s_pControlFocus->MsgProc( uMsg, wParam, lParam ) )
			return true;
	}

	switch (uMsg)
	{

	case WM_SIZE:
	case WM_MOVE:
		{
			// Handle sizing and moving messages so that in case the mouse cursor is moved out
			// of an UI control because of the window adjustment, we can properly
			// unhighlight the highlighted control.
			POINT pt = {-1, -1};
			OnMouseMove(pt);
		}break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		{
			// If a control is in focus, it belongs to this dialog, and it's enabled, then give
			// it the first chance at handling the message.
			if( s_pControlFocus && s_pControlFocus->getParentDialog() == this &&
				s_pControlFocus->getEnabled() )
			{
				if( s_pControlFocus->HandleKeyboard( hWnd, uMsg, wParam, lParam ) )
					return true;
			}

// 			for (UINT i = 0; i < m_Controls.size(); i++)
// 			{
// 				if (m_Controls[i]->HandleKeyboard(hWnd, uMsg, wParam, lParam))
// 					return true;
// 			}
		}break;

	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_XBUTTONDBLCLK:
	case WM_MOUSEWHEEL:
		{
			//next let controls handle the mouse message
			POINT mousePoint;
			GetCursorPos(&mousePoint);
			ScreenToClient(hWnd,&mousePoint);
			mousePoint.x -= m_x;
			mousePoint.y -= m_y + getCaptionHeight();

			// If a control is in focus, it belongs to this dialog, and it's enabled, then give
			// it the first chance at handling the message.
			if( s_pControlFocus && s_pControlFocus->getParentDialog() == this &&
				s_pControlFocus->getEnabled() )
			{
				if( s_pControlFocus->HandleMouse( hWnd, uMsg, mousePoint, wParam, lParam, timer ) )
					return true;
			}

			for (UINT i = 0; i < m_Controls.size(); i++)
			{
				if (m_Controls[i]->HandleMouse(hWnd,uMsg,mousePoint, wParam, lParam,timer))
				{
					bHandled = true;
					break;
				}
			}

			//bHandled = m_Controls[0]->HandleMouse(hWnd,uMsg,mousePoint, wParam, lParam,timer);
			if (bHandled)
				return bHandled;

		}break;

	}

	// Mouse not over any controls in this dialog, if there was a control
	// which had focus it just lost it
	if( uMsg == WM_LBUTTONDOWN && s_pControlFocus &&
		s_pControlFocus->getParentDialog() == this )
	{
		s_pControlFocus->OnFocusOut();
		s_pControlFocus = NULL;
	}

	// the message was not for any of the controls 
	// lets the dialog handle the message
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			// check if we need to highlight a control as the mouse is over it
			POINT mousePoint;
			GetCursorPos(&mousePoint);
			ScreenToClient(hWnd,&mousePoint);
			//mousePoint.y -=  m_rcCaptionBox.bottom;
// 			mousePoint.x -= m_x;
// 			mousePoint.y -= m_y;

			OnMouseMove(mousePoint);

			// return false to allow the message to be handled by app for mouse camera
			return false; 
		}break;

	case WM_LBUTTONDOWN:
		{
			GetCursorPos(&m_startDragPos);
			ScreenToClient(hWnd,&m_startDragPos);

			if (PtInRect(&m_rcCaptionBox, m_startDragPos))
			{
				m_bDrag = true;
				SetCapture(hWnd);
				return true;
			}
		}break;

	case WM_LBUTTONUP:
		{
			if (m_bDrag)
			{
				m_bDrag = false;
				ReleaseCapture();
				return true;
			}
		}break;
	}

// 	for (UINT i = 0; i <  m_Controls.size(); i++)
// 	{
// 		if ( m_Controls[i]->MsgProc(uMsg, wParam, lParam) )
// 			return true;
// 	}

	return false;
}

//-----------------------------------------------------------------------------
// Name : SetCallback 
//-----------------------------------------------------------------------------
void CDialogUI::SetCallback( PCALLBACKGUIEVENT pCallback)
{
	m_pCallbackEvent = pCallback;
}

//-----------------------------------------------------------------------------
// Name : ClearRadioButtonGruop
// Desc : Clears the selection from the selected radio button group
//-----------------------------------------------------------------------------
void CDialogUI::ClearRadioButtonGruop(UINT nButtonGroup)
{
	for (UINT i = 0; i < m_Controls.size(); i++)
	{
		if (m_Controls[i]->getType() == CControlUI::RADIOBUTTON)
		{
			CRadioButtonUI* curRadioButton = (CRadioButtonUI*)m_Controls[i];
			if (curRadioButton->getButtonGroup() == nButtonGroup)
				curRadioButton->setChecked(false);
		}
	}
}

//-----------------------------------------------------------------------------
// Name : OnMouseMove 
// Desc : being called each time the mouse is moved 
//		  check if the mouse is over a control 
//		  if it is highlight that control.
//-----------------------------------------------------------------------------
void CDialogUI::OnMouseMove(POINT pt)
{
	if (m_bDrag)
	{
		int dx = pt.x - m_startDragPos.x;
		int dy = pt.y - m_startDragPos.y;

		//TODO: use setLocation instead of manually adding the values
		//setLocation(m_x + dx, m_y + dy);
		m_x += dx;
		m_y += dy;
		UpdateRects();

		m_startDragPos = pt;
		return;
	}

	pt.x -= m_x;
	pt.y -= m_y;
	pt.y -= getCaptionHeight();

	CControlUI* pControl = getControlAtPoint(pt);

	// check if the current control was already highlighted 
	if (pControl == m_pMouseOverControl)
		return; 

	// if there was a control highlighted restore it to normal
	if (m_pMouseOverControl)
		m_pMouseOverControl->onMouseLeave();
	
	// sets the new mouseOverControl and highlight it
	m_pMouseOverControl = pControl;
	if (pControl)
		pControl->onMouseEnter();
	
}

//-----------------------------------------------------------------------------
// Name : getControlAtPoint 
// Desc : check if the given point is inside 
//        one of the controls that is in the dialog
//		  and if found returns a pointer to that control
//-----------------------------------------------------------------------------
CControlUI* CDialogUI::getControlAtPoint(POINT pt)
{
	for (UINT i = 0; i < m_Controls.size(); i++)
	{
		if (m_Controls[i]->ContainsPoint(pt)) //TODO: add checks for if the control is enable and not hidden
		{
			return m_Controls[i];
		}
	}

	// if no control was found to have the point within it return null
	return NULL;
}

//-----------------------------------------------------------------------------
// Name : addStatic
// Desc : add a control of type static to the dialog
//-----------------------------------------------------------------------------
bool CDialogUI::addStatic(int ID, LPCTSTR strText, int x, int y, int width, int height, CStaticUI** ppStaticCreated/* = NULL*/)
{
	//initialized the static control
	CStaticUI* pControl = new CStaticUI(ID, strText, x, y, width, height);

	initControl(pControl);

	//add it to the controls vector
	m_Controls.push_back(pControl);

	if (ppStaticCreated != NULL)
		*ppStaticCreated = pControl;

	return true;
}

//-----------------------------------------------------------------------------
// Name : addButton
// Desc : add a control of type button to the dialog
//-----------------------------------------------------------------------------
bool CDialogUI::addButton(int ID, LPCTSTR strText, int x, int y, int width, int height, UINT nHotkey, CButtonUI** ppButtonCreated/* = NULL*/)
{
	//initialized the button control
	CButtonUI* pButton = new  CButtonUI(ID, strText, x, y, width, height, nHotkey);

	initControl(pButton);

	//add it to the controls vector
	m_Controls.push_back(pButton);

	if (ppButtonCreated != NULL)
		*ppButtonCreated = pButton;

	return true;
}

//-----------------------------------------------------------------------------
// Name : addCheckBox()
// Desc : add a control of type checkBox to the dialog
//-----------------------------------------------------------------------------
bool CDialogUI::addCheckBox(int ID, int x, int y, int width, int height, UINT nHotkey, CCheckboxUI** ppCheckBoxCreated/* = NULL*/)
{
	//initialized the checkBox control
	CCheckboxUI* pCheckBox = new CCheckboxUI(ID, x, y, width, height, nHotkey);

	initControl(pCheckBox);

	//add it to the controls vector
	m_Controls.push_back(pCheckBox);

	if (ppCheckBoxCreated != NULL)
		*ppCheckBoxCreated = pCheckBox;

	return true;


}

//-----------------------------------------------------------------------------
// Name : addRadioButton()
// Desc : add a control of type radio button to the dialog
//-----------------------------------------------------------------------------
bool CDialogUI::addRadioButton(int ID, int x, int y, int width, int height, UINT nHotkey, UINT nButtonGroup, CRadioButtonUI** ppRadioButtonCreated/* = NULL*/)
{
	CRadioButtonUI* pRadioButton = new CRadioButtonUI(ID, x, y, width, height, nHotkey, nButtonGroup);

	initControl(pRadioButton);

	//add it to the controls vector
	m_Controls.push_back(pRadioButton);

	if (ppRadioButtonCreated != NULL)
		*ppRadioButtonCreated = pRadioButton;

	return true;
}

//-----------------------------------------------------------------------------
// Name : addComboBox()
// Desc : add a control of type Combobox to the dialog
//-----------------------------------------------------------------------------
bool CDialogUI::addComboBox(int ID, LPCTSTR strText, int x, int y, int width, int height, UINT nHotkey, CComboBoxUI** ppComboxCreated/* = NULL*/)
{
	CComboBoxUI* pComboBox = new CComboBoxUI(ID, strText, x, y, width, height, nHotkey);

	initControl(pComboBox);

	pComboBox->UpdateRects();

	m_Controls.push_back(pComboBox);

	if (ppComboxCreated != NULL)
		*ppComboxCreated = pComboBox;

	return true;
}

//-----------------------------------------------------------------------------
// Name : addListBox()
// Desc : add a control of type ListBox to the dialog
//-----------------------------------------------------------------------------
bool CDialogUI::addListBox(int ID, int x, int y, int width, int height, DWORD style/* = 0*/, CListBoxUI** ppListBoxCreated/* = NULL*/)
{
	CListBoxUI* pListBox = new CListBoxUI(ID, x, y, width, height, style);

	initControl(pListBox);
	// !!! list box needs to update it's Rects on init
	pListBox->UpdateRects();

	//add it to the controls vector
	m_Controls.push_back(pListBox);

	if (ppListBoxCreated != NULL)
		*ppListBoxCreated = pListBox;

	return true;

}

//-----------------------------------------------------------------------------
// Name : addSlider()
// Desc : add a control of type Slider to the dialog
//-----------------------------------------------------------------------------
bool CDialogUI::addSlider( int ID, int x, int y, int width, int height, int min, int max, int nValue, CSliderUI** ppSliderCreated/* = NULL*/ )
{
	CSliderUI* pSlider = new CSliderUI(ID, x, y, width, height, min, max, nValue);

	initControl(pSlider);
	// !!! slider needs to update it's Rects on init
	pSlider->UpdateRects();

	//add it to the controls vector
	m_Controls.push_back(pSlider);

	if (ppSliderCreated != NULL)
		*ppSliderCreated = pSlider;

	return true;
}

//-----------------------------------------------------------------------------
// Name : addEditbox()
// Desc : add a control of type EditBox to the dialog
//-----------------------------------------------------------------------------
bool CDialogUI::addEditbox( int ID, LPCTSTR strText, int x, int y, int width, int height, CTimer* timer, CEditBoxUI** ppEditBoxCreated/* = NULL*/)
{
	CEditBoxUI* pEditBox = new CEditBoxUI(ID, strText, x, y, width, height, timer);

	initControl(pEditBox);
	// !!! EditBox needs to update it's Rects on init
	pEditBox->UpdateRects();

	//add it to the controls vector
	m_Controls.push_back(pEditBox);

	if (ppEditBoxCreated != NULL)
		*ppEditBoxCreated = pEditBox;

	return true;
}

//-----------------------------------------------------------------------------
// Name : initControl()
// Desc : initialize a control by giving it the default control settings
//-----------------------------------------------------------------------------
bool CDialogUI::initControl(CControlUI* pControl)
{
	if (pControl == NULL)
		return false;

	// look for a default graphics for the control
	for (UINT i = 0; i < m_DefControlsGFX.size(); i++)
	{
		if (m_DefControlsGFX[i].nControlType == pControl->getType())
		{
			pControl->setControlGFX(m_DefControlsGFX[i].elementsGFXvec);
			pControl->setControlFonts(m_DefControlsGFX[i].elementsFontVec);
			break;
		}
	}

	//sets the check box parent aka this dialog
	pControl->setParent(this);

	return pControl->onInit();
}

//-----------------------------------------------------------------------------
// Name : setSize()
//-----------------------------------------------------------------------------
void CDialogUI::setSize(UINT width, UINT height)
{
	m_width = width;
	m_height = height;
	UpdateRects();
}

//-----------------------------------------------------------------------------
// Name : setLocation()
//-----------------------------------------------------------------------------
void CDialogUI::setLocation(int x, int y)
{
	m_x = x;
	m_y = y;
	UpdateRects();
}

//-----------------------------------------------------------------------------
// Name : UpdateRects()
// Desc : Update the dialog bounding box and it's caption box every tine the dialog
//		  is moved
//-----------------------------------------------------------------------------
void CDialogUI::UpdateRects()
{
	SetRect(&m_rcBoundingBox, m_x ,m_y, m_x + m_width, m_y + m_height);
	SetRect(&m_rcCaptionBox, m_x, m_y, m_x + m_width, m_y + m_nCaptionHeight);
}

//-----------------------------------------------------------------------------
// Name : getLocation()
//-----------------------------------------------------------------------------
POINT CDialogUI::getLocation()
{
	POINT loc = {m_x,m_y};
	return loc;
}

//-----------------------------------------------------------------------------
// Name : getCaptionStartPoint()
//-----------------------------------------------------------------------------
LONG CDialogUI::getCaptionHeight()
{
	return m_rcCaptionBox.bottom - m_rcCaptionBox.top;
}

//-----------------------------------------------------------------------------
// Name : RequestFocus()
//-----------------------------------------------------------------------------
void CDialogUI::RequestFocus( CControlUI* pControl)
{
	if( s_pControlFocus == pControl )
		return;

	if( !pControl->CanHaveFocus() )
		return;

	if( s_pControlFocus )
		s_pControlFocus->OnFocusOut();

	pControl->OnFocusIn();
	s_pControlFocus = pControl;
}

//-----------------------------------------------------------------------------
// Name : ClearFocus 
//-----------------------------------------------------------------------------
void CDialogUI::ClearFocus()
{
	if( s_pControlFocus )
	{
		s_pControlFocus->OnFocusOut();
		s_pControlFocus = NULL;
	}

	ReleaseCapture();
}

//-----------------------------------------------------------------------------
// Name : GetControl 
// Desc : searches for a control base on ID and Control Type
//-----------------------------------------------------------------------------
CControlUI* CDialogUI::getControl( int ID, UINT nControlType )
{	
	// Try to find the control with the given ID
	for( UINT i = 0; i < m_Controls.size(); i++ )
	{
		CControlUI* pControl = m_Controls[i];

		if( pControl->getID() == ID && pControl->getType() == nControlType )
		{
			return pControl;
		}
	}

	// Not found
	return NULL;
}

//-----------------------------------------------------------------------------
// Name : getStatic 
//-----------------------------------------------------------------------------
CStaticUI* CDialogUI::getStatic( int ID )
{
	return static_cast< CStaticUI* >(getControl( ID, CControlUI::STATIC ) );
	//return ( CStaticUI* )getControl( ID, CControlUI::STATIC );
}

//-----------------------------------------------------------------------------
// Name : getButton 
//-----------------------------------------------------------------------------
CButtonUI* CDialogUI::getButton( int ID )
{
	return static_cast< CButtonUI* > (getControl(ID, CControlUI::BUTTON) );
	//return ( CButtonUI* )GetControl( ID, DXUT_CONTROL_BUTTON );
}

//-----------------------------------------------------------------------------
// Name : getCheckBox 
//-----------------------------------------------------------------------------
CCheckboxUI * CDialogUI::getCheckBox( int ID )
{
	return static_cast< CCheckboxUI* > ( getControl(ID, CControlUI::CHECKBOX) );
	//return ( CCheckBox3D* )GetControl( ID, DXUT_CONTROL_CHECKBOX );
}

//-----------------------------------------------------------------------------
// Name : getRadioButton 
//-----------------------------------------------------------------------------
CRadioButtonUI * CDialogUI::getRadioButton ( int ID )
{
	return static_cast< CRadioButtonUI* > ( getControl(ID, CControlUI::RADIOBUTTON) );
	//return ( CRadioButton3D* )GetControl( ID, DXUT_CONTROL_RADIOBUTTON );
}

//-----------------------------------------------------------------------------
// Name : GetComboBox 
//-----------------------------------------------------------------------------
CComboBoxUI * CDialogUI::getComboBox( int ID )
{
	return static_cast< CComboBoxUI* > (getControl(ID, CControlUI::COMBOBOX));
}

//-----------------------------------------------------------------------------
// Name : GetSlider 
//-----------------------------------------------------------------------------
CSliderUI * CDialogUI::getSlider( int ID )
{
	return static_cast< CSliderUI* > (getControl(ID, CControlUI::SLIDER));

}

//-----------------------------------------------------------------------------
// Name : GetEditBox 
//-----------------------------------------------------------------------------
CEditBoxUI * CDialogUI::getEditBox( int ID )
{
	return static_cast< CEditBoxUI* > (getControl(ID, CControlUI::EDITBOX));
}

//-----------------------------------------------------------------------------
// Name : GetListBox 
//-----------------------------------------------------------------------------
CListBoxUI * CDialogUI::getListBox( int ID )
{
	return static_cast< CListBoxUI* > (getControl(ID, CControlUI::LISTBOX));
}