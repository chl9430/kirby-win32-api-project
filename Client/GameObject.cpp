#include "pch.h"
#include "GameObject.h"

#include "GameCollider.h"
#include "GameRigidBody.h"
#include "GameAnimator.h"
#include "GameGravity.h"

GameObject::GameObject()
	: m_strName{}
	, m_vPos{}
	, m_vScale{}
	, m_bAlive{ true }
	, m_pCollider{ nullptr }
	, m_pRigidBody{ nullptr }
	, m_pAnimator{ nullptr }
	, m_pGravity{ nullptr }
{
}

GameObject::~GameObject()
{
}

void GameObject::CreateCollider()
{
	m_pCollider = new GameCollider;
	m_pCollider->m_pOwner = this;
}

void GameObject::CreateRigidBody()
{
	m_pRigidBody = new GameRigidBody;
	m_pRigidBody->m_pOwner = this;
}

void GameObject::CreateAnimator()
{
	m_pAnimator = new GameAnimator;
	m_pAnimator->m_pOwner = this;
}

void GameObject::CreateGravity()
{
	m_pGravity = new GameGravity;
	m_pGravity->m_pOwner = this;
}