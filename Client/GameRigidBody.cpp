#include "pch.h"
#include "GameRigidBody.h"

GameRigidBody::GameRigidBody()
	: m_pOwner{ nullptr }
	, m_vForce{}
	, m_vVelocity{}
{
}

GameRigidBody::~GameRigidBody()
{
}