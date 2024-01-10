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
	// �� Scene���� ����� �޴��� ���δ�.
	GameCore::GetInst()->DockMenu();

	Vec2 vResolution = GameCore::GetInst()->GetResolution();

	GameTexture* pTileTex = GameResMgr::GetInst()->LoadTexture(L"Stage1TileSet", L"texture\\tile\\Stage1_Tile_Set.bmp");
	UINT iWidth = pTileTex->Width();
	UINT iHeight = pTileTex->Height();

	// Panel ����
	GameUI* pPanelUI = new GamePanelUI{ false };
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2{ (float)iWidth, (float)iHeight + TILE_SIZE * 2 });
	pPanelUI->SetPos(Vec2{ vResolution.x - pPanelUI->GetScale().x, 0.f });

	AddObject(pPanelUI, GROUP_TYPE::UI);

	// Save ��ư ����
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

	// Load ��ư ����
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

	// ���� �� �ִ� Tile�� ���� ���� ��������
	UINT iTileCount = (iWidth * iHeight) / (TILE_SIZE * TILE_SIZE);

	UINT iX = 0;
	UINT iY = TILE_SIZE;

	// Ÿ�� ��ư ����
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

	// ���� �� Ÿ�� ��ư�� ��� ó�� �Ѵ�.
	for (; iter != vecChildUI.end(); ++iter)
	{
		// Ÿ�� ��ư�� �˻��Ѵ�.
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

	// �� ���� � ��ġ�� ����Ű�� �ִ��� üũ
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

		// ��ġ�� ������� Ÿ�� ����
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
	ofn.lpstrFilter = L"All\0*.*\0Tile\0*.tile\0"; // ��� �̸�, ��� Ȯ����
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = GamePathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetSaveFileName(&ofn)) // ����� true, ��ҽ� false
	{
		SaveTile(szName);
	}
}

void GameScene_Tool::SaveTile(const wstring& _strFilePath)
{
	// ���ϵ� Ŀ�� ������Ʈ(������ġ�� �츮 ���α׷� ���̿��� ������ ����ִ� ������ ��)
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb"); // 2����Ʈ ����
	// 1���� : ���� ������ �ּ�
	// 2���� : ������ ���
	// 3���� : ��� L"w" -> ����, L"r" -> �б�, b�� ������ ���̳ʸ� ���

	assert(pFile);

	// ��� Ÿ�ϵ��� ���������� ������ �����͸� �����ϰ� ��
	const vector<GameObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((GameTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile); // ����(��Ʈ��)�� �ݾ��ش�.
}

void GameScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GameCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"All\0*.*\0Tile\0*.tile\0"; // ��� �̸�, ��� Ȯ����
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

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) // CALLBACK(__stdcall) : �Լ�ȣ��Ծ�
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false); // ���� ���̾�α��� �����͸� �������� �Լ�(����������)
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false); // ���� ���̾�α��� �����͸� �������� �Լ�

			GameScene* pCurScene = GameSceneMgr::GetInst()->GetCurScene();

			// ToolScene Ȯ��
			GameScene_Tool* pToolScene = dynamic_cast<GameScene_Tool*>(pCurScene);
			assert(pToolScene); // ĳ���ÿ� �����ϸ�, ������� �� ���̴�.

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