#include "pch.h"
#include "GameLaunchedState.h"

#include "GameMonster.h"

#include "GameRigidBody.h"

#include "AI.h"

GameLaunchedState::GameLaunchedState()
	: GameState{ MON_STATE::LAUNCHED }
	, m_iDir{ 1 }
{
}

GameLaunchedState::~GameLaunchedState()
{
}

void GameLaunchedState::Update()
{
	GetAI()->GetObj()->GetRigidBody()->SetVelocity(Vec2{ 400.f * m_iDir, 0.f });
}

void GameLaunchedState::Enter()
{
}

void GameLaunchedState::Exit()
{
}