#include "pch.h"
#include "GameMonster.h"

#include "AI.h"
#include "GameCollider.h"

GameMonster::GameMonster()
	: m_tInfo{}
	, m_pAI{ nullptr }
{
	CreateCollider();
	GetCollider()->SetScale(Vec2{ 40.f, 40.f });
}

GameMonster::~GameMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}

void GameMonster::Update()
{
	if (nullptr != m_pAI)
		m_pAI->Update();
}

void GameMonster::SetAI(AI* _pAI)
{
	m_pAI = _pAI;
	m_pAI->m_pOwner = this;
}