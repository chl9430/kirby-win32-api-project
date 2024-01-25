#include "pch.h"
#include "GameMonster.h"

#include "AI.h"
#include "GameCollider.h"
#include "GameState.h"
#include "GameAnimator.h"

GameMonster::GameMonster(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject(_strName, _vPos, _vScale)
	, m_tInfo{}
	, m_pAI{ nullptr }
{
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
	case MON_STATE::WALK:
	{
		GetAnimator()->Play(L"WADDLE_DEE_WALK_LEFT", true);
	}
	break;
	case MON_STATE::FLOAT_IDLE:
	{
		GetAnimator()->Play(L"SCARFY_IDLE_LEFT", true);
	}
	break;
	}
}

void GameMonster::SetAI(AI* _pAI)
{
	m_pAI = _pAI;
	m_pAI->m_pOwner = this;
}