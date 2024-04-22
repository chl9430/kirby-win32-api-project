#include "pch.h"
#include "GameScene.h"

#include "GameCamera.h"
#include "GameResMgr.h"
#include "GamePathMgr.h"

#include "GameTexture.h"

#include "GameObject.h"
#include "GamePlayer.h"
#include "GameMonster.h"
#include "GameTile.h"
#include "GameGate.h"

#include "SelectGDI.h"

#include "GameMonsterFactory.h"

GameScene::GameScene()
	: m_strName{}
	, m_arrObj{}
	, m_pPlayer{ nullptr }
	, m_iTileX{ 0 }
	, m_iTileY{ 0 }
{
}

GameScene::~GameScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			Safe_Delete_Vec(m_arrObj[i]);
		}
	}
}

void GameScene::Start()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->Start();
		}
	}
}

void GameScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead()) // 오브젝트가 사라질예정이 아니라면
			{
				m_arrObj[i][j]->Update();
			}
		}
	}
}

void GameScene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->FinalUpdate();
		}
	}
}

void GameScene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		/*if ((UINT)GROUP_TYPE::TILE == i)
		{
			Render_Tile(_dc);
			continue;
		}*/

		vector<GameObject*>::iterator iter = m_arrObj[i].begin();

		for ( ; iter != m_arrObj[i].end(); )
		{
			if (!(*iter)->IsDead()) // 오브젝트가 죽지 않았다면
			{
				(*iter)->Render(_dc);
				++iter;
			}
			else // 오브젝트가 죽지 않았다면
			{
				iter = m_arrObj[i].erase(iter); // 해당하는 값을 벡터에서 지우고, 다음 원소의 iter값을 반환
			}
		}
	}
}

void GameScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = GamePathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// 파일도 커널 오브젝트(저장장치와 우리 프로그램 사이에서 연결을 잡아주는 역할을 함)
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb"); // 2바이트 오픈
	// 1인자 : 파일 포인터 주소
	// 2인자 : 완전한 경로
	// 3인자 : 모드 L"w" -> 쓰기, L"r" -> 읽기

	assert(pFile);

	char szBuff[256] = {};

	wstring str = {};

	Vec2 vTilePos = {};
	wstring strTileTexKey = {};

	while (FScanf(szBuff, pFile))
	{
		if (strcmp("[Tile Pos]", szBuff) == 0)
		{
			int iX = 0;
			int iY = 0;

			fscanf_s(pFile, "%d %d", &iX, &iY);

			vTilePos = { POINT{ iX, iY } };
		}

		if (strcmp("[Tile Texture]", szBuff) == 0)
		{
			char textureKeyBuff[256] = {};

			FScanf(textureKeyBuff, pFile);

			strTileTexKey = L"";

			for (int i = 0; textureKeyBuff[i] != '\0'; i++) {
				strTileTexKey += wchar_t(textureKeyBuff[i]);
			}

			// 스테이지 씬일 때만
			if (m_strName == L"Stage Scene")
			{
				if (strTileTexKey == L"KirbyButton")
				{
					GamePlayer* pObj = new GamePlayer{ L"Player", vTilePos, Vec2{ TILE_SIZE, TILE_SIZE } }; // 부모 클래스에서 삭제 담당
					pObj->SetObjScene(this);
					pObj->CreateInhale();
					AddObject(pObj, GROUP_TYPE::PLAYER);

					RegisterPlayer(pObj);
				}
				else if (strTileTexKey == L"WaddleDeeButton")
				{
					GameMonster* pWaddleDee = GameMonsterFactory::CreateMonster(MON_NAME::WADDLE_DEE, Vec2{ vTilePos });
					AddObject(pWaddleDee, GROUP_TYPE::MONSTER);
				}
				else if (strTileTexKey == L"GateButton")
				{
					GameGate* pGate = new GameGate{ L"Gate", vTilePos, Vec2{ TILE_SIZE, TILE_SIZE } };
					pGate->SetCurrentTexture(GameResMgr::GetInst()->LoadTexture(L"Gate", L"texture\\Gate.bmp"));
					AddObject(pGate, GROUP_TYPE::GATE);
				}
				else if (strTileTexKey.find(L"Stage1TileButton") != string::npos)
				{
					GameTile* pTile = new GameTile{ L"Tile", vTilePos, Vec2{ TILE_SIZE, TILE_SIZE } };
					pTile->SetCurrentTexture(GameResMgr::GetInst()->FindTexture(strTileTexKey));

					AddObject(pTile, GROUP_TYPE::TILE);
				}
			}
			else // 툴씬이라면
			{
				GameTile* pTile = new GameTile{ L"Tile", vTilePos, Vec2{ TILE_SIZE, TILE_SIZE } };
				pTile->SetCurrentTexture(GameResMgr::GetInst()->FindTexture(strTileTexKey));

				AddObject(pTile, GROUP_TYPE::TILE);
			}
		}
	}

	fclose(pFile); // 파일(스트림)을 닫아준다.
}

void GameScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		Safe_Delete_Vec<GameObject*>(m_arrObj[i]);
	}
}

void GameScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<GameObject*>(m_arrObj[(UINT)_eTarget]);
}

void GameScene::AddObject(GameObject* _pObj, GROUP_TYPE _eType)
{
	m_arrObj[(UINT)_eType].push_back(_pObj);
	_pObj->SetGroupType(_eType);
}

void GameScene::SortObjectGroup(GROUP_TYPE _eType)
{
	sort(m_arrObj[(UINT)_eType].begin(), m_arrObj[(UINT)_eType].end()
		, [](GameObject* _pLeftTile, GameObject* _pRightTile)
		{
			Vec2 vLeftTilePos = _pLeftTile->GetPos();
			Vec2 vRightTilePos = _pRightTile->GetPos();

			if (vLeftTilePos.y < vRightTilePos.y)
			{
				return true;
			}
			else if (vLeftTilePos.y == vRightTilePos.y)
			{
				return vLeftTilePos.x < vRightTilePos.x;
			}
			else
			{
				return false;
			}
		}
	);
}