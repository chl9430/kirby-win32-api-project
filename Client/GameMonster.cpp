#include "pch.h"
#include "GameMonster.h"

#include "AI.h"
#include "GameCollider.h"
#include "GameState.h"
#include "GameAnimator.h"

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
	UpdateAnimation();

	if (nullptr != m_pAI)
		m_pAI->Update();
}

void GameMonster::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void GameMonster::UpdateAnimation()
{
	MON_STATE eCurMonState = m_pAI->GetCurState()->GetType();

	switch (eCurMonState)
	{
	case MON_STATE::IDLE:
	{
		GetAnimator()->Play(L"WADDLE_DEE_WALK_LEFT", true);
	}
	break;
	}
}

void GameMonster::SetAI(AI* _pAI)
{
	m_pAI = _pAI;
	m_pAI->m_pOwner = this;
}