#include "pch.h"
#include "GameScene.h"

#include "GameCamera.h"
#include "GameResMgr.h"
#include "GamePathMgr.h"

#include "GameObject.h"
#include "GameTexture.h"
#include "GameTile.h"
#include "SelectGDI.h"

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
	SelectGDI gdiPen(_dc, PEN_TYPE::GREEN);
	SelectGDI gdiBrush(_dc, BRUSH_TYPE::BLACK);

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 20; j++)
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

			GameTile* pTile = new GameTile{ L"Tile", vTilePos, Vec2{ TILE_SIZE, TILE_SIZE } };
			pTile->SetCurrentTexture(GameResMgr::GetInst()->FindTexture(strTileTexKey));

			AddObject(pTile, GROUP_TYPE::TILE);
		}

		str = szBuff;
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