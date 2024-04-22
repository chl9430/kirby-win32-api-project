#include "pch.h"
#include "GameHitState.h"

#include "GameMonster.h"

#include "AI.h"

GameHitState::GameHitState()
	: GameState{ MON_STATE::HIT }
	, m_bIsDead{ false }
{
}

GameHitState::~GameHitState()
{
}

void GameHitState::Update()
{
	GameMonster* pMon = GetAI()->GetObj();

	if (pMon->GetMonInfo().fHP <= 0.f)
	{
		m_bIsDead = true;
	}
}

void GameHitState::Enter()
{
}

void GameHitState::Exit()
{
}