#include "pch.h"
#include "GameScene.h"

#include "GameObject.h"

GameScene::GameScene()
	: m_strName{}
	, m_arrObj{}
	, m_pPlayer{ nullptr }
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
}