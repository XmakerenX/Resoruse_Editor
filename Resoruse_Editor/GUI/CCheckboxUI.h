#ifndef  _CCHECKBOXUI_H
#define  _CCHECKBOXUI_H

#include "CButtonUI.h"

class CCheckboxUI : public CButtonUI
{
public:
	//CCheckboxUI(void);
	CCheckboxUI					(int ID, int x, int y, UINT width, UINT height, UINT nHotkey);
	virtual ~CCheckboxUI		(void);

	virtual void	Render				( CAssetManager& assetManger);

	virtual bool    HandleKeyboard		( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool    HandleMouse			( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam, CTimer* timer );

protected:
	bool m_bChecked;

private:
	enum ELEMENTS{BUTTON, MOUSEOVER};
};

#endif  //_CCHECKBOXUI_H

