#include "pch.h"
#include "GameScene_Stage.h"

#include "GameCore.h"

#include "GameCollisionMgr.h"
#include "GameResMgr.h"

#include "GameTexture.h"

#include "GamePlayer.h"
#include "GameMonster.h"
#include "GameBackground.h"

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

	// 배경화면
	GameBackground* pBackground_1 = new GameBackground{ L"Stage_01_Background", Vec2{ 0.f, 0.f}, Vec2{ TILE_SIZE, TILE_SIZE } };

	GameTexture* pBackgroundTex = GameResMgr::GetInst()->LoadTexture(L"Stage01Background", L"texture\\tile\\Stage1_Background.bmp");
	pBackground_1->SetOriginSize(pBackgroundTex->Width(), pBackgroundTex->Height());
	Vec2 vNewScale = pBackgroundTex->ChangeImageSizeByRate(Vec2{ TILE_SIZE * MAX_TILE_COUNT_WIDTH, TILE_SIZE * MAX_TILE_COUNT_HEIGHT });

	pBackground_1->SetCurrentTexture(pBackgroundTex);
	pBackground_1->SetScale(vNewScale);
	pBackground_1->SetPos(Vec2{ vNewScale.x / 2, vNewScale.y / 2 });
	AddObject(pBackground_1, GROUP_TYPE::BACKGROUND);

	/*GameMonster* pScarfy = GameMonsterFactory::CreateMonster(MON_TYPE::SCARFY, Vec2{ 140.f, 100.f });
	AddObject(pScarfy, GROUP_TYPE::MONSTER);

	GameMonster* pPengy = GameMonsterFactory::CreateMonster(MON_TYPE::PENGY, Vec2{ 740.f, 80.f });
	AddObject(pPengy, GROUP_TYPE::MONSTER);*/

	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::STAR, GROUP_TYPE::MONSTER);
	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::STAR, GROUP_TYPE::TILE);

	Start();
}

void GameScene_Stage::Exit()
{
	DeleteAll();

	// 다른 씬에서는 다른 그룹간의 충돌 체크를 하게될 수 있으니 리셋한다.
	GameCollisionMgr::GetInst()->Reset();
}

void GameScene_Stage::LoadTile(const wstring& _strRelativePath)
{
	GameScene::LoadTile(_strRelativePath);

	// 타일에 콜라이더 생성
	const vector<GameObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	vector < GameObject*>::const_iterator iter = vecTile.begin();

	for (; iter != vecTile.end(); ++iter)
	{
		(*iter)->CreateCollider();
		(*iter)->GetCollider()->SetOffsetPos(Vec2{ 0.f, 0.f });
		(*iter)->GetCollider()->SetScale(Vec2{ TILE_SIZE, TILE_SIZE });
	}

	// 문에 콜라이더 생성
	const vector<GameObject*>& vecGate = GetGroupObject(GROUP_TYPE::GATE);
	vector < GameObject*>::const_iterator gateIter = vecGate.begin();

	for (; gateIter != vecGate.end(); ++gateIter)
	{
		(*gateIter)->CreateCollider();
		(*gateIter)->GetCollider()->SetOffsetPos(Vec2{ 0.f, 0.f });
		(*gateIter)->GetCollider()->SetScale(Vec2{ TILE_SIZE, TILE_SIZE });
	}

	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TILE);
	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GATE);
	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::TILE, GROUP_TYPE::MONSTER);
}