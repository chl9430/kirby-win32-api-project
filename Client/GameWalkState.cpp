#include "pch.h"
#include "GameWalkState.h"

#include "GameMonster.h"

#include "GameRigidBody.h"

#include "AI.h"

GameWalkState::GameWalkState()
	: GameState{ MON_STATE::WALK }
{
}

GameWalkState::~GameWalkState()
{
}

void GameWalkState::Update()
{
	GameMonster* pMonster = GetAI()->GetObj();

	if (pMonster->GetTouchLeft())
	{
		pMonster->SetObjDir(1);
	}
	else if (pMonster->GetTouchRight())
	{
		pMonster->SetObjDir(-1);
	}

	pMonster->GetRigidBody()->SetVelocity(Vec2{ pMonster->GetMonInfo().fSpeed * pMonster->GetObjDir(), pMonster->GetRigidBody()->GetVelocity().y });
}

void GameWalkState::Enter()
{
}

void GameWalkState::Exit()
{
}