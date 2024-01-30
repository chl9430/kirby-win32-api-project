#include "pch.h"
#include "GameAttack.h"

#include "GameCollider.h"

GameAttack::GameAttack(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject{ _strName, _vPos, _vScale }
	, m_pOwner{ nullptr }
	, m_vOffset{}
{
}

GameAttack::~GameAttack()
{
}

void GameAttack::Update()
{
	SetPos(Vec2{ m_pOwner->GetPos().x + (m_vOffset.x * m_pOwner->GetObjDir()), m_pOwner->GetPos().y + m_vOffset.y });
}