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
#include "GameTexture.h"

#include "SelectGDI.h"

GameScene_Tool::GameScene_Tool()
	: m_eCurMode{ EDIT_MODE::NONE }
	, m_strSelectedTileName{}
	, m_pPanel{ nullptr }
{
}

GameScene_Tool::~GameScene_Tool()
{
}

void GameScene_Tool::Enter()
{
	// 툴 Scene에서 사용할 메뉴를 붙인다.
	GameCore::GetInst()->DockMenu();

	Vec2 vResolution = GameCore::GetInst()->GetResolution();

	GameTexture* pTileTex = GameResMgr::GetInst()->LoadTexture(L"Stage1TileSet", L"texture\\tile\\Stage1_Tile_Set.bmp");
	UINT iWidth = pTileTex->Width();
	UINT iHeight = pTileTex->Height();

	// Panel 생성
	GameUI* pPanelUI = new GamePanelUI{ false };
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2{ (float)iWidth, (float)iHeight + TILE_SIZE * 2 });
	pPanelUI->SetPos(Vec2{ vResolution.x - pPanelUI->GetScale().x, 0.f });

	AddObject(pPanelUI, GROUP_TYPE::UI);

	// Save 버튼 생성
	GameBtnUI* pSaveBtn = new GameBtnUI{ false };
	pSaveBtn->SetName(L"SaveButton");
	pSaveBtn->SetScale(Vec2{ TILE_SIZE, TILE_SIZE });
	pSaveBtn->SetPos(Vec2{ 0, (int)pPanelUI->GetScale().y - TILE_SIZE });
	pSaveBtn->SetTexture(GameResMgr::GetInst()->LoadTexture(L"SaveButton", L"texture\\Save_Button.bmp"));
	pSaveBtn->SetMouseDownTexture(GameResMgr::GetInst()->LoadTexture(L"SaveButtonSelected", L"texture\\Save_Button_Selected.bmp"));
	pSaveBtn->SetMouseUpTexture(GameResMgr::GetInst()->FindTexture(L"SaveButton"));
	pSaveBtn->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Tool::SaveTileData);
	pPanelUI->AddChild(pSaveBtn);
	AddObject(pSaveBtn, GROUP_TYPE::UI);

	// Load 버튼 생성
	GameBtnUI* pLoadBtn = new GameBtnUI{ false };
	pLoadBtn->SetName(L"LoadButton");
	pLoadBtn->SetScale(Vec2{ TILE_SIZE, TILE_SIZE });
	pLoadBtn->SetPos(Vec2{ TILE_SIZE, (int)pPanelUI->GetScale().y - TILE_SIZE });
	pLoadBtn->SetTexture(GameResMgr::GetInst()->LoadTexture(L"LoadButton", L"texture\\Load_Button.bmp"));
	pLoadBtn->SetMouseDownTexture(GameResMgr::GetInst()->LoadTexture(L"LoadButtonSelected", L"texture\\Load_Button_Selected.bmp"));
	pLoadBtn->SetMouseUpTexture(GameResMgr::GetInst()->FindTexture(L"LoadButton"));
	pLoadBtn->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Tool::LoadTileData);
	pPanelUI->AddChild(pLoadBtn);
	AddObject(pLoadBtn, GROUP_TYPE::UI);

	// 만들 수 있는 Tile의 종류 개수 가져오기
	UINT iTileCount = (iWidth * iHeight) / (TILE_SIZE * TILE_SIZE);

	UINT iX = 0;
	UINT iY = TILE_SIZE;

	// 타일 버튼 생성
	for (UINT i = 0; i < iTileCount; ++i)
	{
		iX = i * TILE_SIZE % (UINT)pPanelUI->GetScale().x;

		GameBtnUI* pTileBtn = new GameBtnUI{ false };
		pTileBtn->SetName(L"Stage1TileButton" + to_wstring(i));
		pTileBtn->SetScale(Vec2{ TILE_SIZE, TILE_SIZE });
		pTileBtn->SetPos(Vec2{ (float)iX, (float)iY });
		pTileBtn->SetTexture(GameResMgr::GetInst()->LoadTexture(L"Stage1TileButton" + to_wstring(i), L"texture\\tile\\Stage1_Tile_Button_" + to_wstring(i) + L".bmp"));
		pTileBtn->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Tool::SetSelectedTileName, pTileBtn->GetName());

		pPanelUI->AddChild(pTileBtn);
		AddObject(pTileBtn, GROUP_TYPE::UI);

		if (iX == TILE_SIZE * 2)
		{
			iY += TILE_SIZE;
		}
	}

	m_pPanel = pPanelUI;
}

void GameScene_Tool::Exit()
{
	GameCore::GetInst()->DivideMenu();

	DeleteAll();
}

void GameScene_Tool::Update()
{
	GameScene::Update();

	const vector<GameUI*>& vecChildUI = m_pPanel->GetChildUI();
	vector<GameUI*>::const_iterator iter = vecChildUI.begin();

	// 선택 된 타일 버튼은 흑백 처리 한다.
	for (; iter != vecChildUI.end(); ++iter)
	{
		// 타일 버튼만 검사한다.
		if ((*iter)->GetName().find(L"Stage1TileButton") != string::npos)
		{
			if (m_strSelectedTileName == (*iter)->GetName())
			{
				wstring strTileName = (*iter)->GetName();

				(*iter)->SetCurrentTexture(GameResMgr::GetInst()->LoadTexture(strTileName + L"Selected", L"texture\\tile\\Stage1_Tile_Button_" + strTileName.substr(16, 1) + L"_Selected.bmp"));
			}
			else
			{
				(*iter)->SetCurrentTexture(GameResMgr::GetInst()->FindTexture((*iter)->GetName()));
			}
		}
	}

	// 맵 안의 어떤 위치를 가리키고 있는지 체크
	if (KEY_TAP(KEY::LBTN))
	{
		if (MOUSE_POS.x >= m_pPanel->GetPos().x
			&& MOUSE_POS.x <= m_pPanel->GetPos().x + m_pPanel->GetScale().x
			&& MOUSE_POS.y >= m_pPanel->GetPos().y
			&& MOUSE_POS.y <= m_pPanel->GetPos().y + m_pPanel->GetScale().y)
		{
			return;
		}

		if (m_strSelectedTileName == L"")
		{
			return;
		}

		Vec2 vMousePos = MOUSE_POS;
		vMousePos = GameCamera::GetInst()->GetRealPos(vMousePos);

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0.f || 30 <= iCol
			|| vMousePos.y < 0.f || 20 <= iRow)
		{
			return;
		}

		// 위치를 기반으로 타일 생성
		GameTile* pTile = new GameTile();

		pTile->SetPos(Vec2{ (float)(iCol * TILE_SIZE) + TILE_SIZE / 2, (float)(iRow * TILE_SIZE) + TILE_SIZE / 2 });
		pTile->SetScale(Vec2{ TILE_SIZE, TILE_SIZE });
		pTile->SetCurrentTexture(GameResMgr::GetInst()->FindTexture(m_strSelectedTileName));
		// pTile->SetTexture(GameResMgr::GetInst()->FindTexture(m_strSelectedTileName));

		AddObject(pTile, GROUP_TYPE::TILE);

		// UINT iIdx = iRow * 30 + iCol;
	}

	/*if (KEY_TAP(KEY::CTRL))
	{
		DeleteGroup(GROUP_TYPE::TILE);
	}*/
}

void GameScene_Tool::Render(HDC _dc)
{
	SelectGDI gdiPen(_dc, PEN_TYPE::GREEN);
	SelectGDI gdiBrush(_dc, BRUSH_TYPE::BLACK);

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			Rectangle(_dc, i * TILE_SIZE, j * TILE_SIZE, (i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
		}
	}

	GameScene::Render(_dc);
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
			/*pToolScene->CreateTile(iXCount, iYCount);*/

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