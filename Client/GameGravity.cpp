#include "pch.h"
#include "GameGravity.h"

#include "GameObject.h"
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
	m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2{ 0.f, 800.f });
}