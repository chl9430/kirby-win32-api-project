#include "pch.h"
#include "GameScene_Tool.h"

#include "GameCore.h"

#include "GameSceneMgr.h"
#include "GameKeyMgr.h"
#include "GameCamera.h"
#include "GamePathMgr.h"
#include "GameResMgr.h"

#include "GameUI.h"
#include "GamePanelUI.h"
#include "GameBtnUI.h"
#include "GameTile.h"

GameScene_Tool::GameScene_Tool()
	: m_eCurMode{ EDIT_MODE::NONE }
{
}

GameScene_Tool::~GameScene_Tool()
{
}

void GameScene_Tool::Enter()
{
	// 툴 Scene에서 사용할 메뉴를 붙인다.
	GameCore::GetInst()->DockMenu();

	// 타일 생성
	CreateTile(5, 6);

	Vec2 vResolution = GameCore::GetInst()->GetResolution();
	// GameCamera::GetInst()->SetLookAt(vResolution / 2.f);

	GameUI* pPanelUI = new GamePanelUI{ false };
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2{ 300.f, 150.f });
	pPanelUI->SetPos(Vec2{ vResolution.x - pPanelUI->GetScale().x, 0.f });

	GameBtnUI* pBtnUI = new GameBtnUI{ false };
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2{ 150.f, 50.f });
	pBtnUI->SetPos(Vec2{ 0.f, 0.f });
	pBtnUI->SetClickedCallBack(this, (SCENE_MEMFUNC)&GameScene_Tool::SetCurMode);
	pBtnUI->SetIdleTexture(GameResMgr::GetInst()->LoadTexture(L"TileMapButton", L"texture\\Tile_Map_Button.bmp"));
	pBtnUI->SetMouseDownTexture(GameResMgr::GetInst()->LoadTexture(L"TileMapButtonClicked", L"texture\\Tile_Map_Button_Clicked.bmp"));
	pBtnUI->SetCurrentTexture(GameResMgr::GetInst()->FindTexture(L"TileMapButton"));

	pPanelUI->AddChild(pBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);
}

void GameScene_Tool::Exit()
{
	GameCore::GetInst()->DivideMenu();

	DeleteAll();
}

void GameScene_Tool::Update()
{
	GameScene::Update();

	SetTileIdx();

	if (KEY_TAP(KEY::CTRL))
	{
		LoadTileData();
	}

	if (KEY_TAP(KEY::LSHIFT))
	{
		SaveTileData();
	}
}

void GameScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GameCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"All\0*.*\0Tile\0*.tile\0"; // 모든 이름, 모든 확장자
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = GamePathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetSaveFileName(&ofn)) // 저장시 true, 취소시 false
	{
		SaveTile(szName);
	}
}

void GameScene_Tool::SaveTile(const wstring& _strFilePath)
{
	// 파일도 커널 오브젝트(저장장치와 우리 프로그램 사이에서 연결을 잡아주는 역할을 함)
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb"); // 2바이트 오픈
	// 1인자 : 파일 포인터 주소
	// 2인자 : 완전한 경로
	// 3인자 : 모드 L"w" -> 쓰기, L"r" -> 읽기, b가 붙으면 바이너리 모드

	assert(pFile);

	// 타일 가로세로 개수 저장
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// 모든 타일들을 개별적으로 저장할 데이터를 저장하게 함
	const vector<GameObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((GameTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile); // 파일(스트림)을 닫아준다.
}

void GameScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GameCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"All\0*.*\0Tile\0*.tile\0"; // 모든 이름, 모든 확장자
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = GamePathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = GamePathMgr::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}
}

void GameScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = GameCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileX <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<GameObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((GameTile*)vecTile[iIdx])->AddImgIdx();
	}
}

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) // CALLBACK(__stdcall) : 함수호출규약
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false); // 현재 다이얼로그의 데이터를 가져오는 함수(정수형으로)
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false); // 현재 다이얼로그의 데이터를 가져오는 함수

			GameScene* pCurScene = GameSceneMgr::GetInst()->GetCurScene();

			// ToolScene 확인
			GameScene_Tool* pToolScene = dynamic_cast<GameScene_Tool*>(pCurScene);
			assert(pToolScene); // 캐스팅에 성공하면, 현재씬은 툴 씬이다.

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}