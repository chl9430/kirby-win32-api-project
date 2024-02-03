#include "pch.h"
#include "GameGravity.h"

#include "GameObject.h"
#include "GamePlayer.h"
#include "GameMonster.h"

#include "GameRigidBody.h"

#include "AI.h"
#include "GameState.h"

GameGravity::GameGravity()
	: m_pOwner{ nullptr }
{
}

GameGravity::~GameGravity()
{
}

void GameGravity::FinalUpdate()
{
	if (m_pOwner->GetName() == L"Player")
	{
		GamePlayer* pPlayer = (GamePlayer*)m_pOwner;

		if (!pPlayer->GetTouchBottom())
		{
			if (pPlayer->GetPlayerState() == PLAYER_STATE::FLOAT_START
				|| pPlayer->GetPlayerState() == PLAYER_STATE::FLOAT_IDLE
				|| pPlayer->GetPlayerState() == PLAYER_STATE::FLOAT_END)
			{
				m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2{ 0.f, 400.f });
			}
			else
			{
				m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2{ 0.f, 800.f });
			}
		}
	}

	if (m_pOwner->GetName() == L"Waddle_Dee")
	{
		GameMonster* pMon = (GameMonster*)m_pOwner;

		if (!pMon->GetTouchBottom())
		{
			if (pMon->GetAI()->GetCurState()->GetType() == MON_STATE::LAUNCHED)
			{
				m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2{ 0.f, 0.f });
			}
			else
			{
				m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2{ 0.f, 800.f });
			}
		}
	}
}