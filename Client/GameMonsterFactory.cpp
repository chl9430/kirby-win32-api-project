#include "pch.h"
#include "GameMonsterFactory.h"

#include "GameMonster.h"
#include "GameRigidBody.h"
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
		pMon = new GameMonster;
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 50.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		pMon->SetMonInfo(info);

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

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