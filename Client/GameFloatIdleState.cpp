#include "pch.h"
#include "GameFloatIdleState.h"

#include "GameMonster.h"

#include "GameRigidBody.h"

#include "AI.h"

GameFloatIdleState::GameFloatIdleState(Vec2 _vPos)
	: GameState{ MON_STATE::FLOAT_IDLE }
	, m_vInitialPos{ _vPos }
	, m_vfFloatRange{ TILE_SIZE }
	, m_iCurDir{ 1 }
{
}

GameFloatIdleState::~GameFloatIdleState()
{
}

void GameFloatIdleState::Update()
{
	Vec2 vCurPos = GetAI()->GetObj()->GetPos();
	GameRigidBody* pRigid = GetAI()->GetObj()->GetRigidBody();

	if (abs(vCurPos.y - m_vInitialPos.y) > m_vfFloatRange) // 94.9 > 95
	{
		float fDiff = abs(vCurPos.y - m_vInitialPos.y) - m_vfFloatRange;

		if (m_iCurDir == 1)
		{
			vCurPos.y -= fDiff;
			m_iCurDir = -1;
		}
		else if (m_iCurDir == -1)
		{
			vCurPos.y += fDiff;
			m_iCurDir = 1;
		}

		GetAI()->GetObj()->SetPos(vCurPos);
	}

	pRigid->SetVelocity(Vec2{ pRigid->GetVelocity().x, 50.f * m_iCurDir });
}

void GameFloatIdleState::Enter()
{
}

void GameFloatIdleState::Exit()
{
}