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

	HMENU m_hMenu;

public:
	int Init(HWND _hWnd, POINT _ptResolution);

	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

	HDC GetMainDC()
	{
		return m_hDC;
	}
};

