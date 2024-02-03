#include "pch.h"
#include "GameDrawnState.h"

#include "GameTimeMgr.h"

#include "GameMonster.h"

#include "AI.h"

GameDrawnState::GameDrawnState()
	: GameState{ MON_STATE::DRAWN }
	, m_vDestPos{}
{
}

GameDrawnState::~GameDrawnState()
{
}

void GameDrawnState::Update()
{
	Vec2 vPos = GetAI()->GetObj()->GetPos();
	Vec2 vDiff = m_vDestPos - vPos;
	vDiff.Normalize();

	vPos += (vDiff * 300.f * fDT);

	GetAI()->GetObj()->SetPos(vPos);
}

void GameDrawnState::Enter()
{
}

void GameDrawnState::Exit()
{
}