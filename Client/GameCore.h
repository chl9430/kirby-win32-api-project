#pragma once

class GameTexture;

class GameCore
{
	SINGLE(GameCore);

private:
	HWND m_hWnd;
	POINT m_ptResolution;
	HDC m_hDC;
	HMENU m_hMenu;
	GameTexture* m_pMemTex; // 백버퍼 텍스처

	// 자주 사용하는 GDI Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

	void Clear();
public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();

	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);
	void CreateBrush();

	HWND GetMainHwnd()
	{
		return m_hWnd;
	}
	POINT GetResolution()
	{
		return m_ptResolution;
	}
	HDC GetMainDC()
	{
		return m_hDC;
	}
	HPEN GetPen(PEN_TYPE _eType)
	{
		return m_arrPen[(UINT)_eType];
	}
	HBRUSH GetBrush(BRUSH_TYPE _eType)
	{
		return m_arrBrush[(UINT)_eType];
	}
};