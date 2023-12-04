#include "pch.h"
#include "GameScene_Stage.h"

#include "GameCore.h"
#include "GameCollisionMgr.h"

#include "GamePlayer.h"

GameScene_Stage::GameScene_Stage()
{
}

GameScene_Stage::~GameScene_Stage()
{
}

void GameScene_Stage::Enter()
{
	GameObject* pObj = new GamePlayer; // 부모 클래스에서 삭제 담당
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2{ 100.f, 100.f });
	pObj->SetScale(Vec2{ 100.f, 100.f });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	Vec2 vResolution = GameCore::GetInst()->GetResolution();

	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);

	Start();
}