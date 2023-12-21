#include "pch.h"
#include "GameGravity.h"

#include "GameObject.h"
#include "GamePlayer.h"
#include "GameRigidBody.h"

GameGravity::GameGravity()
	: m_pOwner{ nullptr }
	, m_bGround{ false }
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
		m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2{ 0.f, 400.f });
	}
	else
	{
		m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2{ 0.f, 800.f });
	}
}

void GameGravity::SetGround(bool _b)
{
	m_bGround = _b;

	if (m_bGround)
	{
		Vec2 vV = m_pOwner->GetRigidBody()->GetVelocity();
		m_pOwner->GetRigidBody()->SetVelocity(Vec2{ vV.x, 0.f });
	}
}