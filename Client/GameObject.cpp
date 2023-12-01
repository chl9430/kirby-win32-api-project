#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
	: m_strName{}
	, m_vPos{}
	, m_bAlive{ true }
{
}

GameObject::~GameObject()
{
}