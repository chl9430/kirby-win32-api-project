#include "pch.h"
#include "GameScene_Tool.h"

#include "GameCore.h"

#include "GameSceneMgr.h"
#include "GameKeyMgr.h"
#include "GameCamera.h"
#include "GamePathMgr.h"
#include "GameResMgr.h"
#include "GameTimeMgr.h"

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

	GameTexture* pTileTex = GameResMgr::GetInst()->FindTexture(L"Stage1TileSet");
	UINT iWidth = pTileTex->Width();
	UINT iHeight = pTileTex->Height();

	// Panel ����
	GameUI* pPanelUI = new GamePanelUI{ false, L"ParentUI", Vec2{ vResolution.x - iWidth, 0.f }, Vec2{ (float)iWidth, (float)iHeight + TILE_SIZE * 2 } };

	AddObject(pPanelUI, GROUP_TYPE::UI);

	// Save ��ư ����
	GameBtnUI* pSaveBtn = new GameBtnUI{ false, L"SaveButton", Vec2{ 0, (int)pPanelUI->GetScale().y - TILE_SIZE }, Vec2{ TILE_SIZE, TILE_SIZE } };
	pSaveBtn->SetTexture(GameResMgr::GetInst()->LoadTexture(L"SaveButton", L"texture\\Save_Button.bmp"));
	pSaveBtn->SetMouseDownTexture(GameResMgr::GetInst()->LoadTexture(L"SaveButtonSelected", L"texture\\Save_Button_Selected.bmp"));
	pSaveBtn->SetMouseUpTexture(GameResMgr::GetInst()->FindTexture(L"SaveButton"));
	pSaveBtn->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Tool::SaveTileData);
	pPanelUI->AddChild(pSaveBtn);
	AddObject(pSaveBtn, GROUP_TYPE::UI);

	// Load ��ư ����
	GameBtnUI* pLoadBtn = new GameBtnUI{ false, L"LoadButton", Vec2{ TILE_SIZE, (int)pPanelUI->GetScale().y - TILE_SIZE }, Vec2{ TILE_SIZE, TILE_SIZE } };
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

		GameBtnUI* pTileBtn = new GameBtnUI{ false, L"Stage1TileButton" + to_wstring(i), Vec2{ (float)iX, (float)iY }, Vec2{ TILE_SIZE, TILE_SIZE } };
		pTileBtn->SetTexture(GameResMgr::GetInst()->FindTexture(L"Stage1TileButton" + to_wstring(i)));
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

		if (vMousePos.x < 0.f || MAX_TILE_COUNT_WIDTH <= iCol
			|| vMousePos.y < 0.f || MAX_TILE_COUNT_HEIGHT <= iRow)
		{
			return;
		}

		// ��ġ�� ������� Ÿ�� ����
		GameTile* pTile = new GameTile( L"Tile", Vec2{ (float)(iCol * TILE_SIZE) + TILE_SIZE / 2, (float)(iRow * TILE_SIZE) + TILE_SIZE / 2 }, Vec2{ TILE_SIZE, TILE_SIZE });
		pTile->SetCurrentTexture(GameResMgr::GetInst()->FindTexture(m_strSelectedTileName));

		AddObject(pTile, GROUP_TYPE::TILE);
	}

	// ī�޶� �̵�
	Vec2 vDiff = GameCamera::GetInst()->GetDiff();

	if (KEY_HOLD(KEY::I))
	{
		vDiff.y -= 500.f * fDT;
	}

	if (KEY_HOLD(KEY::K))
	{
		vDiff.y += 500.f * fDT;
	}

	if (KEY_HOLD(KEY::J))
	{
		vDiff.x -= 500.f * fDT;
	}

	if (KEY_HOLD(KEY::L))
	{
		vDiff.x += 500.f * fDT;
	}

	GameCamera::GetInst()->FixDiff(vDiff);

	GameCamera::GetInst()->SetDiff(vDiff);

	/*if (KEY_TAP(KEY::CTRL))
	{
		DeleteGroup(GROUP_TYPE::TILE);
	}*/
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

	// ������ Ÿ�ϵ��� ���͸� ����
	SortObjectGroup(GROUP_TYPE::TILE);

	// ��� Ÿ�ϵ��� ���������� ������ ���͸� �����ϰ� ��
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