#include "pch.h"
#include "GameSceneMgr.h"

#include "GameScene_Title.h"
#include "GameScene_Tool.h"
#include "GameScene_Stage.h"

GameSceneMgr::GameSceneMgr()
	: m_arrScene{}
	, m_pCurScene{ nullptr }
{

}

GameSceneMgr::~GameSceneMgr()
{
	// ¸ðµç ¾À ÇÒ´ç ÇØÁ¦
	for (size_t i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (m_arrScene[i] != nullptr)
		{
			delete m_arrScene[i];
		}
	}
}

void GameSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];

	m_pCurScene->Start();
}

void GameSceneMgr::Init()
{
	// ¾À »ý¼º
	m_arrScene[(UINT)SCENE_TYPE::TITLE] = new GameScene_Title;
	m_arrScene[(UINT)SCENE_TYPE::TITLE]->SetName(L"Title Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new GameScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new GameScene_Stage;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Stage Scene");

	// ÇöÀç ¾À ÁöÁ¤
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::STAGE_01];
	m_pCurScene->Enter();
}

void GameSceneMgr::Update()
{
	m_pCurScene->Update();

	m_pCurScene->FinalUpdate();
}

void GameSceneMgr::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);
}