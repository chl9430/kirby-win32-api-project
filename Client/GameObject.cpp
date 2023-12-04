#include "pch.h"
#include "GameObject.h"

#include "GameCollider.h"

GameObject::GameObject()
	: m_strName{}
	, m_vPos{}
	, m_bAlive{ true }
	, m_pCollider{ nullptr }
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