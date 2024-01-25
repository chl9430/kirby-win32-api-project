#include "pch.h"
#include "GameGravity.h"

#include "GameObject.h"
#include "GamePlayer.h"
#include "GameRigidBody.h"

GameGravity::GameGravity()
	: m_pOwner{ nullptr }
{
}

GameGravity::~GameGravity()
{
}

void GameGravity::FinalUpdate()
{
	GamePlayer* pPlayer = (GamePlayer*)m_pOwner;

	if (pPlayer->GetPlayerState() == PLAYER_STATE::FLOAT_START
		|| pPlayer->GetPlayerState() == PLAYER_STATE::FLOAT_IDLE
		|| pPlayer->GetPlayerState() == PLAYER_STATE::FLOAT_END)
	{
		if (!pPlayer->GetTouchBottom())
		{
			m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2{ 0.f, 400.f });
		}
		else
		{
			m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2{ 0.f, 0.f });
		}
	}
	else
	{
		if (!pPlayer->GetTouchBottom())
		{
			m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2{ 0.f, 800.f });
		}
		else
		{
			m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2{ 0.f, 0.f });
		}
	}
}