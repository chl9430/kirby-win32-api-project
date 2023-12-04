#include "pch.h"
#include "GameObject.h"

#include "GameCollider.h"
#include "GameRigidBody.h"

GameObject::GameObject()
	: m_strName{}
	, m_vPos{}
	, m_vScale{}
	, m_bAlive{ true }
	, m_pCollider{ nullptr }
	, m_pRigidBody{ nullptr }
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