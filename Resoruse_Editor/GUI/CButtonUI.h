#ifndef  _CBUTTONUI_H
#define  _CBUTTONUI_H

#include <windows.h>
#include <d3dx9.h>
#include "../rendering/d3d.h"
#include "../CAssetManager.h"
#include "../CTimer.h"
#include "CStaticUI.h"

class CButtonUI : public CStaticUI
{
public:
	//CButtonUI					(void);
	CButtonUI					(int ID, LPCTSTR strText, int x, int y, UINT width, UINT height, UINT nHotkey);
	virtual ~CButtonUI			(void);

	virtual void	Render				( CAssetManager& assetManger);

	virtual bool    HandleKeyboard		( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool    HandleMouse			( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam, CTimer* timer );

	virtual bool    CanHaveFocus();


	void	setHotKey			( UINT nHotKey);

	//void	drawButtonRect		(RECT& rcTexture, RECT& rcWindow, LPD3DXSPRITE sprite, LPDIRECT3DTEXTURE9 pTexture, D3DCOLOR color);
	//void	drawButtonRect		(RECT& rcTexture, RECT& rcWindow, CMySprite* sprite, LPDIRECT3DTEXTURE9 pTexture, D3DCOLOR color, bool bHighLight);

protected:
	UINT	    m_nHotkey;

	bool	    m_bPressed;

private:
	enum ELEMENTS{BUTTON, MOUSEOVER};
};

#endif  //_CBUTTONUI_H