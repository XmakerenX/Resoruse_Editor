#include "CRadioButtonUI.h"
#include "CDialogUI.h"

//-----------------------------------------------------------------------------
// Name : CRadioButtonUI (Constructor)
//-----------------------------------------------------------------------------
CRadioButtonUI::CRadioButtonUI(int ID, int x, int y, UINT width, UINT height, UINT nHotkey, UINT nButtonGruop)
	:CCheckboxUI(ID, x, y, width, height, nHotkey)
{
	m_type = RADIOBUTTON;
	m_nButtonGroup = nButtonGruop;
}

//-----------------------------------------------------------------------------
// Name : CRadioButtonUI (destructor)
//-----------------------------------------------------------------------------
CRadioButtonUI::~CRadioButtonUI(void)
{
}

//-----------------------------------------------------------------------------
// Name : HandleKeyboard ()
//-----------------------------------------------------------------------------
bool CRadioButtonUI::HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return false;
}

//-----------------------------------------------------------------------------
// Name : HandleMouse ()
//-----------------------------------------------------------------------------
bool CRadioButtonUI::HandleMouse( HWND hWnd, UINT uMsg, POINT mousePoint, INPUT_STATE inputstate, CTimer* timer )
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		{
			if ( Pressed(hWnd, mousePoint, inputstate, timer))
				return true;
		}break;

	case WM_LBUTTONUP:
		{
			if ( Released(hWnd, mousePoint))
				return true;
		}break;
	}

	return false;
}

//-----------------------------------------------------------------------------
// Name : Pressed ()
//-----------------------------------------------------------------------------
bool CRadioButtonUI::Pressed( HWND hWnd, POINT pt, INPUT_STATE inputState, CTimer* timer)
{
	if ( ContainsPoint( pt ) )
	{
		m_bPressed = true;

		SetCapture(hWnd);

		if( !m_bHasFocus )
			m_pParentDialog->RequestFocus( this );

		return true;

	}
	return false;
}

//-----------------------------------------------------------------------------
// Name : Released ()
//-----------------------------------------------------------------------------
bool CRadioButtonUI::Released( HWND hWnd, POINT pt)
{
	if (m_bPressed)
	{
		m_bPressed = false;

		ReleaseCapture();

		if (ContainsPoint(pt))
		{
			m_pParentDialog->ClearRadioButtonGruop(m_nButtonGroup);
			m_bChecked = !m_bChecked;
			m_clickedSig(this);
			//m_pParentDialog->SendEvent(3, false, m_ID, hWnd);
			//m_pParentDialog->SendEvent(hWnd, 3, true, m_ID);
		}

		return true;
	}
	return false;
}
//-----------------------------------------------------------------------------
// Name : getButtonGroup ()
//-----------------------------------------------------------------------------
UINT CRadioButtonUI::getButtonGroup()
{
	return m_nButtonGroup;
}

//-----------------------------------------------------------------------------
// Name : setChecked ()
//-----------------------------------------------------------------------------
void CRadioButtonUI::setChecked(bool bChecked)
{
	m_bChecked = bChecked;
}