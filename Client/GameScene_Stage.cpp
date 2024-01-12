#include "pch.h"
#include "GameScene_Stage.h"

#include "GameCore.h"

#include "GameCollisionMgr.h"

#include "GamePlayer.h"
#include "GameMonster.h"
#include "GameMonsterFactory.h"
#include "GameCollider.h"

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
	LoadTile(L"tile\\1-1");

	GameObject* pObj = new GamePlayer; // 부모 클래스에서 삭제 담당
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2{ 0.f, 0.f });
	pObj->SetScale(Vec2{ 50.f, 50.f });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	/*GameMonster* pMon = GameMonsterFactory::CreateMonster(MON_TYPE::NORMAL, Vec2{ 300.f, 320.f });
	pMon->SetName(L"Monster");
	AddObject(pMon, GROUP_TYPE::MONSTER);*/

	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);

	Start();
}

void GameScene_Stage::Exit()
{
	DeleteAll();

	// 다른 씬에서는 다른 그룹간의 충돌 체크를 하게될 수 있으니 리셋한다.
	// CCollisionMgr::GetInst()->Reset();
}

void GameScene_Stage::LoadTile(const wstring& _strRelativePath)
{
	GameScene::LoadTile(_strRelativePath);

	const vector<GameObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	vector < GameObject*>::const_iterator iter = vecTile.begin();

	for (; iter != vecTile.end(); ++iter)
	{
		(*iter)->CreateCollider();
		(*iter)->GetCollider()->SetOffsetPos(Vec2{ 0.f, 0.f });
		(*iter)->GetCollider()->SetScale(Vec2{ TILE_SIZE, TILE_SIZE });
	}

	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TILE);
	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::TILE, GROUP_TYPE::MONSTER);
}