#pragma once

struct Vec2;

class GameCore
{
private:
	HWND m_hWnd;
	POINT m_ptResolution;
	HDC m_hDC;

public:
	static GameCore* GetInst();

	int Init(HWND _hWnd, POINT _ptResolution);

	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

	GameCore();
	~GameCore();
};

