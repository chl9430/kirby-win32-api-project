#include "pch.h"
#include "GameCore.h"

#include "GameResMgr.h"

GameCore::GameCore() 
	: m_hWnd{ 0 }
	, m_ptResolution{}
	, m_hDC{ 0 }
	, m_pMemTex{ nullptr }
	, m_hMenu{}
{
}

GameCore::~GameCore()
{
}

int GameCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	ChangeWindowSize(Vec2{ (float)_ptResolution.x, (float)_ptResolution.y }, false);

	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));

	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링용 텍스처 한장을 만든다.
	// m_pMemTex = GameResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);
	m_pMemTex = GameResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	return S_OK;
}

void GameCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0, 0, (long)_vResolution.x, (long)_vResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu); // false일 떄 : 메뉴바를 제외한 상태에서 창의 해상도를 잡아줌
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0); // 윈도우 해상도 설정
}
