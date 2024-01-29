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
#include "GameWalkState.h"
#include "GameFloatIdleState.h"
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
	case MON_TYPE::WADDLE_DEE:
	{
		pMon = new GameMonster{ L"Waddle_Dee", _vPos, Vec2{  TILE_SIZE, TILE_SIZE } };

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 50.f;
		info.fHP = 100.f;
		info.fSpeed = 25.f;

		pMon->SetMonInfo(info);

		pMon->CreateCollider();
		pMon->GetCollider()->SetScale(Vec2{ pMon->GetScale().x, pMon->GetScale().y });

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		pMon->CreateGravity();

		GameTexture* pWalkRightTex = GameResMgr::GetInst()->LoadTexture(L"WaddleDeeWalkRight", L"texture\\Waddle_Dee_Walk_Right.bmp");
		GameTexture* pWalkLeftTex = GameResMgr::GetInst()->LoadTexture(L"WaddleDeeWalkLeft", L"texture\\Waddle_Dee_Walk_Left.bmp");

		pMon->CreateAnimator();

		pMon->GetAnimator()->CreateAnimation(L"WADDLE_DEE_WALK_RIGHT", pWalkRightTex, 0.15f);
		pMon->GetAnimator()->CreateAnimation(L"WADDLE_DEE_WALK_LEFT", pWalkLeftTex, 0.2f);

		AI* pAI = new AI;
		pAI->AddState(new GameWalkState);
		pAI->SetCurState(MON_STATE::WALK);

		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::SCARFY:
	{
		pMon = new GameMonster{ L"Scarfy", _vPos, Vec2{  TILE_SIZE, TILE_SIZE } };

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 50.f;
		info.fHP = 100.f;
		info.fSpeed = 25.f;

		pMon->SetMonInfo(info);

		pMon->CreateCollider();
		pMon->GetCollider()->SetScale(Vec2{ pMon->GetScale().x, pMon->GetScale().y });

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		GameTexture* pIdleRightTex = GameResMgr::GetInst()->LoadTexture(L"ScarfyIdleRight", L"texture\\Scarfy_Idle_Right.bmp");
		GameTexture* pIdleLeftTex = GameResMgr::GetInst()->LoadTexture(L"ScarfyIdleLeft", L"texture\\Scarfy_Idle_Left.bmp");

		pMon->CreateAnimator();

		pMon->GetAnimator()->CreateAnimation(L"SCARFY_IDLE_RIGHT", pIdleRightTex, 0.15f);
		pMon->GetAnimator()->CreateAnimation(L"SCARFY_IDLE_LEFT", pIdleLeftTex, 0.2f);

		AI* pAI = new AI;
		pAI->AddState(new GameFloatIdleState{ pMon->GetPos() });
		pAI->SetCurState(MON_STATE::FLOAT_IDLE);
		GameFloatIdleState* pFloatIdleState = (GameFloatIdleState*)pAI->GetCurState();
		pFloatIdleState->SetFloatingRange(5);

		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::PENGY:
	{
		pMon = new GameMonster{ L"Pengy", _vPos, Vec2{  TILE_SIZE, TILE_SIZE } };

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 50.f;
		info.fHP = 100.f;
		info.fSpeed = 25.f;

		pMon->SetMonInfo(info);

		pMon->CreateCollider();
		pMon->GetCollider()->SetScale(Vec2{ pMon->GetScale().x, pMon->GetScale().y });

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		pMon->CreateGravity();

		GameTexture* pIdleRightTex = GameResMgr::GetInst()->LoadTexture(L"PengyIdleRight", L"texture\\Pengy_Idle_Right.bmp");
		GameTexture* pIdleLeftTex = GameResMgr::GetInst()->LoadTexture(L"PengyIdleLeft", L"texture\\Pengy_Idle_Left.bmp");

		pMon->CreateAnimator();

		pMon->GetAnimator()->CreateAnimation(L"PENGY_IDLE_RIGHT", pIdleRightTex, 0.15f);
		pMon->GetAnimator()->CreateAnimation(L"PENGY_IDLE_LEFT", pIdleLeftTex, 0.2f);

		AI* pAI = new AI;
		pAI->AddState(new GameIdleState);
		pAI->SetCurState(MON_STATE::IDLE);

		pMon->SetAI(pAI);
	}
	break;
	}

	assert(pMon);

	return pMon;
}