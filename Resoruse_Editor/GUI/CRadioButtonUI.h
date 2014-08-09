#ifndef  _CRADIOBUTTONUI_H
#define  _CRADIOBUTTONUI_H

#include "CCheckboxUI.h"

class CRadioButtonUI : public CCheckboxUI
{
public:
	CRadioButtonUI(int ID, int x, int y, UINT width, UINT height, UINT nHotkey, UINT nButtonGruop);
	virtual ~CRadioButtonUI(void);

	//virtual void	Render				( CAssetManager& assetManger);

	virtual bool    HandleKeyboard		( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool    HandleMouse			( HWND hWnd, UINT uMsg, POINT mousePoint, INPUT_STATE inputstate, CTimer* timer );

	virtual bool	Pressed				( HWND hWnd, POINT pt, INPUT_STATE inputState, CTimer* timer);
	virtual bool	Released			( HWND hWnd, POINT pt);

	UINT getButtonGroup();
	void setChecked(bool bChecked);

protected:
	UINT m_nButtonGroup;
};

#endif  //_CRADIOBUTTONUI_H

