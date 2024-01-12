#include "pch.h"
#include "GameScene.h"

#include "GameResMgr.h"
#include "GamePathMgr.h"

#include "GameObject.h"
#include "GameTexture.h"
#include "GameTile.h"

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
			delete m_arrObj[i][j];
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
			if (!m_arrObj[i][j]->IsDead()) // ������Ʈ�� ����������� �ƴ϶��
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
			if (!(*iter)->IsDead()) // ������Ʈ�� ���� �ʾҴٸ�
			{
				(*iter)->Render(_dc);
				++iter;
			}
			else // ������Ʈ�� ���� �ʾҴٸ�
			{
				iter = m_arrObj[i].erase(iter); // �ش��ϴ� ���� ���Ϳ��� �����, ���� ������ iter���� ��ȯ
			}
		}
	}
}

//void GameScene::CreateTile(UINT _iXCount, UINT _iYCount)
//{
//	DeleteGroup(GROUP_TYPE::TILE);
//
//	m_iTileX = _iXCount;
//	m_iTileY = _iYCount;
//
//	GameTexture* pTileTex = GameResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\Stage1_Tile_Set.bmp");
//
//	for (UINT i = 0; i < _iYCount; ++i)
//	{
//		for (UINT j = 0; j < _iXCount; ++j)
//		{
//			GameTile* pTile = new GameTile();
//
//			pTile->SetPos(Vec2{ (float)(j * TILE_SIZE), (float)(i * TILE_SIZE) });
//			pTile->SetTexture(pTileTex);
//
//			AddObject(pTile, GROUP_TYPE::TILE);
//		}
//	}
//}

void GameScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = GamePathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// ���ϵ� Ŀ�� ������Ʈ(������ġ�� �츮 ���α׷� ���̿��� ������ ����ִ� ������ ��)
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb"); // 2����Ʈ ����
	// 1���� : ���� ������ �ּ�
	// 2���� : ������ ���
	// 3���� : ��� L"w" -> ����, L"r" -> �б�

	assert(pFile);

	wchar_t szBuff[256] = {};

	wstring str = {};

	Vec2 vTilePos = {};
	wstring strTileTexKey = {};

	while (WScanf(szBuff, pFile))
	{
		if (wcscmp(L"[Tile Pos]", szBuff) == 0)
		{
			int iX = 0;
			int iY = 0;

			fwscanf_s(pFile, L"%d %d", &iX, &iY);

			vTilePos = { POINT{ iX, iY } };
		}

		if (wcscmp(L"[Tile Texture]", str.c_str()) == 0)
		{
			str = szBuff;

			strTileTexKey = str;

			GameTile* pTile = new GameTile();

			pTile->SetPos(vTilePos);
			pTile->SetScale(Vec2{ TILE_SIZE, TILE_SIZE });
			pTile->SetCurrentTexture(GameResMgr::GetInst()->FindTexture(strTileTexKey));

			AddObject(pTile, GROUP_TYPE::TILE);
		}

		str = szBuff;
	}

	fclose(pFile); // ����(��Ʈ��)�� �ݾ��ش�.
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