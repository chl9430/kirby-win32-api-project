#pragma once

class GameTexture;

class GameCore
{
	SINGLE(GameCore);

private:
	HWND m_hWnd;
	POINT m_ptResolution;
	HDC m_hDC;

	GameTexture* m_pMemTex; // 백버퍼 텍스처

	// 자주 사용하는 GDI Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

	HMENU m_hMenu;

public:
	int Init(HWND _hWnd, POINT _ptResolution);

	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);
	void CreateBrush();

	HDC GetMainDC()
	{
		return m_hDC;
	}

	POINT GetResolution()
	{
		return m_ptResolution;
	}
};

