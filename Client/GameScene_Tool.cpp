#include "pch.h"
#include "GameScene_Tool.h"

#include "GameCore.h"

#include "GameSceneMgr.h"
#include "GameKeyMgr.h"
#include "GameCamera.h"
#include "GamePathMgr.h"
#include "GameResMgr.h"
#include "GameTimeMgr.h"
#include "GameEventMgr.h"
#include "GameCollisionMgr.h"

#include "GameTexture.h"
#include "GameSound.h"

#include "GameUI.h"
#include "GamePanelUI.h"
#include "GameBtnUI.h"
#include "GameTile.h"

#include "SelectGDI.h"

GameScene_Tool::GameScene_Tool()
	: m_eCurMode{ EDIT_MODE::TILE }
	, m_strSelectedTileName{}
	, m_pBGM{ nullptr }
	, m_pPanel{ nullptr }
{
}

GameScene_Tool::~GameScene_Tool()
{
	delete m_pBGM;
}

void GameScene_Tool::Enter()
{
	m_strSelectedTileName = {};
	// �� Scene���� ����� �޴��� ���δ�.
	GameCore::GetInst()->DockMenu();

	Vec2 vResolution = GameCore::GetInst()->GetResolution();

	m_pBGM = new GameSound{};

	m_pBGM->Load(L"sound\\Tool.wav");
	m_pBGM->PlayToBGM(true);
	m_pBGM->SetVolume(100.f);

	GameTexture* pDragBoxTex = GameResMgr::GetInst()->LoadTexture(L"DragBoxPanel", L"texture\\Drag_Box_Panel.bmp");

	GameTexture* pTileTex = GameResMgr::GetInst()->FindTexture(L"Stage1TileSet");
	UINT iWidth = pTileTex->Width();
	UINT iHeight = pTileTex->Height();

	// Panel ����
	GameUI* pDragBoxUI = new GamePanelUI{ false, L"DragBox", Vec2{ vResolution.x - pDragBoxTex->Width(), 0.f }, Vec2{ (int)pDragBoxTex->Width(), (int)pDragBoxTex->Height() }};
	pDragBoxUI->SetCurrentTexture(pDragBoxTex);
	AddObject(pDragBoxUI, GROUP_TYPE::UI);

	// ������ ��ư ����
	GameBtnUI* pExitButtonUI = new GameBtnUI{ false, L"BtnArea", Vec2{ pDragBoxUI->GetScale().x - TILE_SIZE, 0.f }, Vec2{TILE_SIZE, TILE_SIZE}};
	pExitButtonUI->SetTexture(GameResMgr::GetInst()->LoadTexture(L"ExitButton", L"texture\\Exit_Button.bmp"));
	pExitButtonUI->SetMouseDownTexture(GameResMgr::GetInst()->LoadTexture(L"ExitButtonSelected", L"texture\\Exit_Button_Selected.bmp"));
	pExitButtonUI->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Tool::ExitBtnChangeScene);
	pDragBoxUI->AddChild(pExitButtonUI);

	// ��ư ���� ����
	GameUI* pTileAreaUI = new GamePanelUI{ false, L"BtnArea", Vec2{ 0.f, 0.f }, Vec2{(int)iWidth, (int)iHeight + (TILE_SIZE * 2) }};
	pTileAreaUI->SetPos(Vec2{ pDragBoxUI->GetScale().x / 2 - pTileAreaUI->GetScale().x / 2, pDragBoxUI->GetScale().y / 2 - pTileAreaUI->GetScale().y / 2 });
	pDragBoxUI->AddChild(pTileAreaUI);

	// Ŀ�� ��ư ����
	GameBtnUI* pKirbyBtn = new GameBtnUI{ false, L"KirbyButton", Vec2{ 0, 0 }, Vec2{ TILE_SIZE, TILE_SIZE } };
	pKirbyBtn->SetTexture(GameResMgr::GetInst()->LoadTexture(L"KirbyButton", L"texture\\Kirby_Button.bmp"));
	pKirbyBtn->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Tool::SetSelectedTileName, pKirbyBtn->GetName());
	pTileAreaUI->AddChild(pKirbyBtn);

	// ���̵�� ��ư ����
	GameBtnUI* pWaddleDeeBtn = new GameBtnUI{ false, L"WaddleDeeButton", Vec2{ TILE_SIZE, 0 }, Vec2{ TILE_SIZE, TILE_SIZE } };
	pWaddleDeeBtn->SetTexture(GameResMgr::GetInst()->LoadTexture(L"WaddleDeeButton", L"texture\\Waddle_Dee_Button.bmp"));
	pWaddleDeeBtn->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Tool::SetSelectedTileName, pWaddleDeeBtn->GetName());
	pTileAreaUI->AddChild(pWaddleDeeBtn);

	// ����Ʈ ��ư ����
	GameBtnUI* pGateBtn = new GameBtnUI{ false, L"GateButton", Vec2{ (int)pTileAreaUI->GetScale().x - TILE_SIZE, 0 }, Vec2{TILE_SIZE, TILE_SIZE}};
	pGateBtn->SetTexture(GameResMgr::GetInst()->LoadTexture(L"GateButton", L"texture\\Gate_Button.bmp"));
	pGateBtn->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Tool::SetSelectedTileName, pGateBtn->GetName());
	pTileAreaUI->AddChild(pGateBtn);

	// Save ��ư ����
	GameBtnUI* pSaveBtn = new GameBtnUI{ false, L"SaveButton", Vec2{ 0, (int)pTileAreaUI->GetScale().y - TILE_SIZE }, Vec2{ TILE_SIZE, TILE_SIZE } };
	pSaveBtn->SetTexture(GameResMgr::GetInst()->LoadTexture(L"SaveButton", L"texture\\Save_Button.bmp"));
	pSaveBtn->SetMouseDownTexture(GameResMgr::GetInst()->LoadTexture(L"SaveButtonSelected", L"texture\\Save_Button_Selected.bmp"));
	pSaveBtn->SetMouseUpTexture(GameResMgr::GetInst()->FindTexture(L"SaveButton"));
	pSaveBtn->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Tool::SaveTileData);
	pTileAreaUI->AddChild(pSaveBtn);

	// Load ��ư ����
	GameBtnUI* pLoadBtn = new GameBtnUI{ false, L"LoadButton", Vec2{ TILE_SIZE, (int)pTileAreaUI->GetScale().y - TILE_SIZE }, Vec2{ TILE_SIZE, TILE_SIZE } };
	pLoadBtn->SetTexture(GameResMgr::GetInst()->LoadTexture(L"LoadButton", L"texture\\Load_Button.bmp"));
	pLoadBtn->SetMouseDownTexture(GameResMgr::GetInst()->LoadTexture(L"LoadButtonSelected", L"texture\\Load_Button_Selected.bmp"));
	pLoadBtn->SetMouseUpTexture(GameResMgr::GetInst()->FindTexture(L"LoadButton"));
	pLoadBtn->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Tool::LoadTileData);
	pTileAreaUI->AddChild(pLoadBtn);

	// Erase ��ư ����
	GameBtnUI* pEraserBtn = new GameBtnUI{ false, L"EraserButton", Vec2{ (int)pTileAreaUI->GetScale().x - TILE_SIZE, (int)pTileAreaUI->GetScale().y - TILE_SIZE }, Vec2{ TILE_SIZE, TILE_SIZE } };
	pEraserBtn->SetTexture(GameResMgr::GetInst()->LoadTexture(L"EraserButton", L"texture\\Eraser_Button.bmp"));
	pEraserBtn->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Tool::SetSelectedTileName, pEraserBtn->GetName());
	pTileAreaUI->AddChild(pEraserBtn);

	// ���� �� �ִ� Tile�� ���� ���� ��������
	UINT iTileCount = (iWidth * iHeight) / (TILE_SIZE * TILE_SIZE);

	UINT iX = 0;
	UINT iY = TILE_SIZE;

	// Ÿ�� ��ư ����
	for (UINT i = 0; i < iTileCount; ++i)
	{
		iX = i * TILE_SIZE % (UINT)pTileAreaUI->GetScale().x;

		GameBtnUI* pTileBtn = new GameBtnUI{ false, L"Stage1TileButton" + to_wstring(i), Vec2{ (float)iX, (float)iY }, Vec2{ TILE_SIZE, TILE_SIZE } };
		pTileBtn->SetTexture(GameResMgr::GetInst()->FindTexture(L"Stage1TileButton" + to_wstring(i)));
		pTileBtn->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Tool::SetSelectedTileName, pTileBtn->GetName());

		pTileAreaUI->AddChild(pTileBtn);
		// AddObject(pTileBtn, GROUP_TYPE::UI);

		if (iX == TILE_SIZE * 2)
		{
			iY += TILE_SIZE;
		}
	}

	 m_pPanel = pDragBoxUI;
}

void GameScene_Tool::Exit()
{
	GameCore::GetInst()->DivideMenu();

	DeleteAll();

	GameCamera::GetInst()->ResetCameraPos();

	// �ٸ� �������� �ٸ� �׷찣�� �浹 üũ�� �ϰԵ� �� ������ �����Ѵ�.
	GameCollisionMgr::GetInst()->Reset();
}

void GameScene_Tool::Update()
{
	GameScene::Update();

	const vector<GameUI*>& vecChildUI = m_pPanel->GetChildUI()[1]->GetChildUI();
	vector<GameUI*>::const_iterator iter = vecChildUI.begin();

	// ���� �� Ÿ�� ��ư�� ��� ó�� �Ѵ�.
	for (; iter != vecChildUI.end(); ++iter)
	{
		// Ÿ�ϵ��� �˻��Ѵ�.
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
		else if ((*iter)->GetName().find(L"EraserButton") != string::npos)
		{
			if (m_strSelectedTileName == (*iter)->GetName())
			{
				wstring strTileName = (*iter)->GetName();

				(*iter)->SetCurrentTexture(GameResMgr::GetInst()->LoadTexture(L"EraserButtonSelected", L"texture\\Eraser_Button_Selected.bmp"));
			}
			else
			{
				(*iter)->SetCurrentTexture(GameResMgr::GetInst()->FindTexture((*iter)->GetName()));
			}
		}
		else if ((*iter)->GetName().find(L"KirbyButton") != string::npos)
		{
			if (m_strSelectedTileName == (*iter)->GetName())
			{
				wstring strTileName = (*iter)->GetName();

				(*iter)->SetCurrentTexture(GameResMgr::GetInst()->LoadTexture(L"KirbyButtonSelected", L"texture\\Kirby_Button_Selected.bmp"));
			}
			else
			{
				(*iter)->SetCurrentTexture(GameResMgr::GetInst()->FindTexture((*iter)->GetName()));
			}
		}
		else if ((*iter)->GetName().find(L"WaddleDeeButton") != string::npos)
		{
			if (m_strSelectedTileName == (*iter)->GetName())
			{
				wstring strTileName = (*iter)->GetName();

				(*iter)->SetCurrentTexture(GameResMgr::GetInst()->LoadTexture(L"WaddleDeeButtonSelected", L"texture\\Waddle_Dee_Button_Selected.bmp"));
			}
			else
			{
				(*iter)->SetCurrentTexture(GameResMgr::GetInst()->FindTexture((*iter)->GetName()));
			}
		}
		else if ((*iter)->GetName().find(L"GateButton") != string::npos)
		{
			if (m_strSelectedTileName == (*iter)->GetName())
			{
				wstring strTileName = (*iter)->GetName();

				(*iter)->SetCurrentTexture(GameResMgr::GetInst()->LoadTexture(L"GateButtonSelected", L"texture\\Gate_Button_Selected.bmp"));
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

		// ���� ��ġ�� Ÿ���� �ִ� �� Ȯ���Ѵ�.
		const vector<GameObject*>& vecTileGroup = GetGroupObject(GROUP_TYPE::TILE);

		for (GameObject* pObj : vecTileGroup) 
		{
			// Ŭ���� ���� Ÿ���� �̹� �ִ��� Ȯ��
			if (pObj->GetPos().x == (iCol * TILE_SIZE) + TILE_SIZE / 2 
				&& pObj->GetPos().y == (iRow * TILE_SIZE) + TILE_SIZE / 2)
			{
				if (m_strSelectedTileName != L"EraserButton")
				{
					return;
				}
				else // ���찳 ��ư�� ���õ� ���¶��
				{
					pObj->DestroyObj();
				}
			}
		}

		// ��ġ�� ������� Ÿ�� ����
		if (m_strSelectedTileName != L"EraserButton")
		{
			if (m_strSelectedTileName == L"KirbyButton")
			{
				// �̹� Ŀ�� �ִ��� ã�´�.
				auto kirby = find_if(vecTileGroup.begin(), vecTileGroup.end(), [&](GameObject* _pObj) {
					return _pObj->GetName() == L"Kirby";
				});

				// Ŀ�� �̹� �ִٸ�
				if (kirby != vecTileGroup.end()) {
					// ��ġ�� �ٲ۴�.
					(*kirby)->SetPos(Vec2{ (float)(iCol * TILE_SIZE) + TILE_SIZE / 2, (float)(iRow * TILE_SIZE) + TILE_SIZE / 2 });
				}
				else { // Ŀ�� ���ٸ�
					// ���� �����Ѵ�.
					GameObject* pTile = nullptr;

					pTile = new GameTile(L"Kirby", Vec2{ (float)(iCol * TILE_SIZE) + TILE_SIZE / 2, (float)(iRow * TILE_SIZE) + TILE_SIZE / 2 }, Vec2{ TILE_SIZE, TILE_SIZE });
					pTile->SetCurrentTexture(GameResMgr::GetInst()->FindTexture(m_strSelectedTileName));

					AddObject(pTile, GROUP_TYPE::TILE);
				}
			}
			else
			{
				GameObject* pTile = nullptr;

				pTile = new GameTile(L"Tile", Vec2{(float)(iCol * TILE_SIZE) + TILE_SIZE / 2, (float)(iRow * TILE_SIZE) + TILE_SIZE / 2}, Vec2{TILE_SIZE, TILE_SIZE});
				pTile->SetCurrentTexture(GameResMgr::GetInst()->FindTexture(m_strSelectedTileName));

				AddObject(pTile, GROUP_TYPE::TILE);
			}
		}
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

void GameScene_Tool::Render(HDC _dc)
{
	SelectGDI gdiPen(_dc, PEN_TYPE::GREEN);
	SelectGDI gdiBrush(_dc, BRUSH_TYPE::BLACK);

	for (int i = 0; i < MAX_TILE_COUNT_WIDTH; i++)
	{
		for (int j = 0; j < MAX_TILE_COUNT_HEIGHT; j++)
		{
			Vec2 vPos = GameCamera::GetInst()->GetRenderPos(Vec2{ i * TILE_SIZE, j * TILE_SIZE });

			Rectangle(_dc
				, (int)vPos.x
				, (int)vPos.y
				, (int)(vPos.x + TILE_SIZE)
				, (int)(vPos.y + TILE_SIZE)
			);
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

void GameScene_Tool::ExitBtnChangeScene()
{
	tEvent tEve = {};
	tEve.eEven = EVENT_TYPE::SCENE_CHANGE;
	tEve.lParam = (DWORD_PTR)SCENE_TYPE::TITLE;

	GameEventMgr::GetInst()->AddEvent(tEve);
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