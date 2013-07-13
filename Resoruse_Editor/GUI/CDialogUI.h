#ifndef  _CDIALOGUI_H
#define  _CDIALOGUI_H

#include <Windows.h>
#include <vector>
#include <d3dx9.h>
#include "../rendering/d3d.h"
#include "../CAssetManager.h"
#include "CControlUI.h"
#include "CButtonUI.h"
#include "CStaticUI.h"
#include "CCheckBoxUI.h"
#include "CRadioButtonUI.h"
#include "CComboBoxUI.h"
#include "CListBoxUI.h"
#include "CSliderUI.h"
#include "CEditBoxUI.h"

// the callback function that used to send back GUI events to the main program
typedef VOID ( CALLBACK*PCALLBACKGUIEVENT )(HWND hWnd, UINT nEvent, int nControlID, void* pUserContext );

//struct that holds the default elements for a control type
struct CONTROL_GFX
{
	CONTROL_GFX::CONTROL_GFX()
	{
		nControlType = -1;
	}

	CONTROL_GFX::CONTROL_GFX(UINT newControlType, std::vector<ELEMENT_GFX> &newElementsVec)
	{
		nControlType = newControlType;
		elementsGFXvec = newElementsVec;
	}

	UINT nControlType;
	std::vector<ELEMENT_GFX>  elementsGFXvec; 
	std::vector<ELEMENT_FONT> elementsFontVec;

};

class CDialogUI
{
public:
	CDialogUI(void);
	virtual ~CDialogUI(void);

	HRESULT init	 (UINT width, UINT height, int nCaptionHeight, LPCTSTR captionText, char newTexturePath[MAX_PATH], D3DXCOLOR dialogColor, HWND hWnd, CAssetManager& assetManger);
	HRESULT initDefControlElements(CAssetManager& assetManger);

	bool    MsgProc	 ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, CTimer* timer );
	void	OnMouseMove(POINT pt);

	void    SendEvent(UINT nEvent, bool bTriggeredByUser, int nControlID, HWND hWnd = NULL );
	void    SetCallback( PCALLBACKGUIEVENT pCallback);

	HRESULT OnRender   (float fElapsedTime, D3DXVECTOR3 vPos, LPD3DXEFFECT effect, CAssetManager& assetManger);

	void	UpdateRects();

	//-------------------------------------------------------------------------
	// Functions that handle the Dialog Controls
	//-------------------------------------------------------------------------
	bool	initControl(CControlUI* pControl);

	bool	addStatic		 (int ID, LPCTSTR strText, int x, int y, int width, int height, CStaticUI** ppStaticCreated = NULL);
	bool	addButton		 (int ID, LPCTSTR strText, int x, int y, int width, int height, UINT nHotkey, CButtonUI** ppButtonCreated = NULL);
	bool    addCheckBox		 (int ID, int x, int y, int width, int height, UINT nHotkey, CCheckboxUI** ppCheckBoxCreated = NULL);
	bool	addRadioButton	 (int ID, int x, int y, int width, int height, UINT nHotkey, UINT nButtonGroup, CRadioButtonUI** ppRadioButtonCreated = NULL);
	bool    addComboBox      (int ID, LPCTSTR strText, int x, int y, int width, int height, UINT nHotkey, CComboBoxUI** ppComboxCreated = NULL);
	bool    addListBox		 (int ID, int x, int y, int width, int height, DWORD style = 0, CListBoxUI** ppListBoxCreated = NULL);
	bool    addSlider		 (int ID, int x, int y, int width, int height, int min, int max, int nValue, CSliderUI** ppSliderCreated = NULL);
	bool    addEditbox		 (int ID, LPCTSTR strText, int x, int y, int width, int height, CTimer* timer, CEditBoxUI** ppEditBoxCreated = NULL );

	CControlUI     * getControl		( int ID, UINT nControlType );
	CStaticUI      * getStatic		( int ID );
	CButtonUI      * getButton		( int ID );
	CCheckboxUI    * getCheckBox	( int ID );
	CRadioButtonUI * getRadioButton ( int ID );
	CComboBoxUI	   * getComboBox	( int ID );
	CSliderUI	   * getSlider		( int ID );
	CEditBoxUI	   * getEditBox		( int ID );
	CListBoxUI	   * getListBox		( int ID );

	void    ClearRadioButtonGruop(UINT nButtonGroup);

	CControlUI* getControlAtPoint(POINT pt);

	void	RequestFocus( CControlUI* pControl );
	static void WINAPI  ClearFocus();

	//-------------------------------------------------------------------------
	// get and set Functions 
	//-------------------------------------------------------------------------
	void	setSize			 (UINT width, UINT height);
	void	setLocation		 (int x, int y);

	POINT   getLocation	     ();
	LONG	getCaptionHeight ();



private:
	RECT m_rcBoundingBox;
	RECT m_rcCaptionBox;

	int m_nCaptionHeight;
	char m_captionText[MAX_PATH];

	int  m_x, m_y; 
	UINT m_width;
	UINT m_height;
	UINT m_texWidth;
	UINT m_texHeight;

	//TODO: delete the  vars that aren't needed for the drag operation
	POINT m_startDragPos;
	POINT m_curDragPos;

	HWND m_hWnd; // a handle to the window the dialog sends the event messages through the callback function

	bool m_bVisible;
	bool m_bCaption;
	bool m_bMinimized;
	bool m_bDrag;

	char m_texturePath[MAX_PATH];
	D3DXCOLOR m_dialogColor;

	//CButtonUI m_button;
	std::vector<CControlUI*> m_Controls;

	static CControlUI* s_pControlFocus; // The control which has focus
	CControlUI* m_pMouseOverControl;

	//Default graphics for the controls elements stuff like : textures,Rects
	std::vector<CONTROL_GFX> m_DefControlsGFX;

	// Pointer to the callback event function that the dialog sends events to
	PCALLBACKGUIEVENT m_pCallbackEvent;
};

#endif  //_CDIALOGUI_H