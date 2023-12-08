#include "pch.h"
#include "GameScene_Stage.h"

#include "GameCore.h"

#include "GameCollisionMgr.h"
#include "GameCamera.h"

#include "GamePlayer.h"

GameScene_Stage::GameScene_Stage()
{
}

GameScene_Stage::~GameScene_Stage()
{
}

void GameScene_Stage::Render(HDC _dc)
{
	GameScene::Render(_dc);
}

void GameScene_Stage::Enter()
{
	GameObject* pObj = new GamePlayer; // 부모 클래스에서 삭제 담당
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2{ 100.f, 100.f });
	pObj->SetScale(Vec2{ 50.f, 50.f });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	Vec2 vResolution = GameCore::GetInst()->GetResolution();

	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);

	//// Camera Look 지정
	//GameCamera::GetInst()->SetLookAt(vResolution / 2.f);

	Start();
}

void GameScene_Stage::Exit()
{
	DeleteAll();

	// 다른 씬에서는 다른 그룹간의 충돌 체크를 하게될 수 있으니 리셋한다.
	// CCollisionMgr::GetInst()->Reset();
}