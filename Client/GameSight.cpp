#include "pch.h"
#include "GameSight.h"

#include "GameCollider.h"

GameSight::GameSight(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject{ _strName, _vPos, _vPos }
	, m_vOffsetPos{ _vPos }
	, m_pOwner{ nullptr }
{
}

GameSight::~GameSight()
{
}

void GameSight::Update()
{
	// Object의 위치를 따라간다.
	Vec2 vObjectPos = m_pOwner->GetPos();
	SetPos(vObjectPos + m_vOffsetPos);
}

void GameSight::Render(HDC _dc)
{
	ComponentRender(_dc);
}