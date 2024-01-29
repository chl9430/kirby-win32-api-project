#include "pch.h"
#include "GameScene_Stage.h"

#include "GameCore.h"

#include "GameCollisionMgr.h"

#include "GamePlayer.h"
#include "GameMonster.h"

#include "GameCollider.h"

#include "GameMonsterFactory.h"
GameScene_Stage::GameScene_Stage()
{
}

GameScene_Stage::~GameScene_Stage()
{
}

void GameScene_Stage::Enter()
{
	LoadTile(L"tile\\1-1");

	GameObject* pObj = new GamePlayer{ L"Player", Vec2{ 600.f, 100.f }, Vec2{ TILE_SIZE, TILE_SIZE } }; // �θ� Ŭ�������� ���� ���
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	GameMonster* pWaddleDee = GameMonsterFactory::CreateMonster(MON_TYPE::WADDLE_DEE, Vec2{ 500.f, 80.f });
	AddObject(pWaddleDee, GROUP_TYPE::MONSTER);

	GameMonster* pScarfy = GameMonsterFactory::CreateMonster(MON_TYPE::SCARFY, Vec2{ 140.f, 100.f });
	AddObject(pScarfy, GROUP_TYPE::MONSTER);

	GameMonster* pPengy = GameMonsterFactory::CreateMonster(MON_TYPE::PENGY, Vec2{ 740.f, 80.f });
	AddObject(pPengy, GROUP_TYPE::MONSTER);

	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);

	Start();
}

void GameScene_Stage::Exit()
{
	DeleteAll();

	// �ٸ� �������� �ٸ� �׷찣�� �浹 üũ�� �ϰԵ� �� ������ �����Ѵ�.
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