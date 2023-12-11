#include "pch.h"
#include "GameGravity.h"

#include "GameObject.h"
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
	m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2{ 0.f, 800.f });
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