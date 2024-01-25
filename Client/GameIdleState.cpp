#include "pch.h"
#include "GameIdleState.h"

#include "GameMonster.h"

#include "GameRigidBody.h"

#include "AI.h"

GameIdleState::GameIdleState()
	: GameState{ MON_STATE::IDLE }
{

}

GameIdleState::~GameIdleState()
{

}

void GameIdleState::Update()
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

void GameIdleState::Enter()
{
}

void GameIdleState::Exit()
{
}
