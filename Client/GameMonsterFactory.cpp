#include "pch.h"
#include "GameMonsterFactory.h"

#include "GameResMgr.h"

#include "GameTexture.h"

#include "GameMonster.h"
#include "GameSight.h"

#include "GameRigidBody.h"
#include "GameCollider.h"
#include "GameAnimator.h"

#include "AI.h"
#include "GameIdleState.h"

GameMonsterFactory::GameMonsterFactory()
{
}

GameMonsterFactory::~GameMonsterFactory()
{
}

GameMonster* GameMonsterFactory::CreateMonster(MON_TYPE _eType, Vec2 _vPos)
{
	GameMonster* pMon = nullptr;

	switch (_eType)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new GameMonster{ L"Monster", _vPos, Vec2{  TILE_SIZE, TILE_SIZE } };

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 50.f;
		info.fHP = 100.f;
		info.fSpeed = 25.f;

		pMon->SetMonInfo(info);

		pMon->CreateCollider();
		pMon->GetCollider()->SetScale(Vec2{ 40.f, 40.f });

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		pMon->CreateGravity();

		GameTexture* pWalkRightTex = GameResMgr::GetInst()->LoadTexture(L"WaddleDeeWalkRight", L"texture\\Waddle_Dee_Walk_Right.bmp");
		GameTexture* pWalkLeftTex = GameResMgr::GetInst()->LoadTexture(L"WaddleDeeWalkLeft", L"texture\\Waddle_Dee_Walk_Left.bmp");

		pMon->CreateAnimator();

		pMon->GetAnimator()->CreateAnimation(L"WADDLE_DEE_WALK_RIGHT", pWalkRightTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.15f, 4);
		pMon->GetAnimator()->CreateAnimation(L"WADDLE_DEE_WALK_LEFT", pWalkLeftTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.2f, 4);

		AI* pAI = new AI;
		pAI->AddState(new GameIdleState);
		// pAI->AddState(new GameTraceState);
		pAI->SetCurState(MON_STATE::IDLE);

		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::RANGE:
	{

	}
	break;
	}

	assert(pMon);

	return pMon;
}