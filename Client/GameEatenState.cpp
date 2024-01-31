#include "pch.h"
#include "GameEatenState.h"

#include "GameMonster.h"

#include "AI.h"

GameEatenState::GameEatenState()
	: GameState{ MON_STATE::EATEN }
	, m_pPlayer{ nullptr }
{
}

GameEatenState::~GameEatenState()
{
}

void GameEatenState::Update()
{
	GetAI()->GetObj()->SetPos(m_pPlayer->GetPos());
}

void GameEatenState::Enter()
{
}

void GameEatenState::Exit()
{
}