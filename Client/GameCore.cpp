#include "pch.h"
#include "GameCore.h"

#include "GameResMgr.h"
#include "GamePathMgr.h"
#include "GameTimeMgr.h"
#include "GameKeyMgr.h"
#include "GameCamera.h"
#include "GameSceneMgr.h"
#include "GameEventMgr.h"
#include "GameCollisionMgr.h"
#include "GameUIMgr.h"

#include "GameTexture.h"

#include "SelectGDI.h"

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
	ReleaseDC(m_hWnd, m_hDC);

	// CreatePen() 항목 삭제
	for (size_t i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);
}

void GameCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);

	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

int GameCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	ChangeWindowSize(Vec2{ (float)_ptResolution.x, (float)_ptResolution.y }, false);

	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));

	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링용 텍스처 한장을 만든다.
	m_pMemTex = GameResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	CreateBrush();

	// Manager 초기화
	GamePathMgr::GetInst()->Init();
	GameTimeMgr::GetInst()->Init();
	GameKeyMgr::GetInst()->Init();
	GameCamera::GetInst()->Init();
	GameResMgr::GetInst()->Init();
	GameSceneMgr::GetInst()->Init();

	return S_OK;
}

void GameCore::Progress()
{
	// 매니저 업데이트
	GameTimeMgr::GetInst()->Update();
	GameKeyMgr::GetInst()->Update();
	GameCamera::GetInst()->Update();
	GameSceneMgr::GetInst()->Update();

	// 충돌체크
	GameCollisionMgr::GetInst()->Update();

	GameUIMgr::GetInst()->Update();

	// 화면 클리어
	Clear();

	// 렌더링
	GameSceneMgr::GetInst()->Render(m_pMemTex->GetDC());
	// GameCamera::GetInst()->Render();

	// 사본용 DC에 그려진 걸 메인 DC에 복사한다.
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	GameTimeMgr::GetInst()->Render();

	// 이벤트 지연처리
	GameEventMgr::GetInst()->Update();
}

void GameCore::DockMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void GameCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void GameCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0, 0, (long)_vResolution.x, (long)_vResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu); // false일 떄 : 메뉴바를 제외한 상태에서 창의 해상도를 잡아줌
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0); // 윈도우 해상도 설정
}

void GameCore::CreateBrush()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
