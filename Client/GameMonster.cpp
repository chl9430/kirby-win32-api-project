#include "pch.h"
#include "GameMonster.h"

#include "GamePlayer.h"
#include "GameAttack.h"

#include "AI.h"
#include "GameCollider.h"
#include "GameState.h"
#include "GameAnimator.h"

GameMonster::GameMonster(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject(_strName, _vPos, _vScale)
	, m_tInfo{}
	, m_pAI{ nullptr }
	, m_strWalkRightAnimKey{  }
	, m_strWalkLeftAnimKey{  }
	, m_strDrawnRightAnimKey{  }
	, m_strDrawnLeftAnimKey{  }
	, m_pInhale{ nullptr }
	, m_pPowerInhale{ nullptr }
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

	if ((m_pInhale != nullptr && ((GamePlayer*)((GameAttack*)m_pInhale)->GetOwner())->GetPlayerState() == PLAYER_STATE::INHALE)
		|| (m_pPowerInhale != nullptr && ((GamePlayer*)((GameAttack*)m_pPowerInhale)->GetOwner())->GetPlayerState() == PLAYER_STATE::POWER_INHALE))
	{
		m_pAI->SetCurState(MON_STATE::DRAWN);
	}
	else
	{
		m_pAI->SetCurState(MON_STATE::WALK);
	}
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
		if (GetObjDir() == 1)
			GetAnimator()->Play(m_strWalkRightAnimKey, true);
		else
			GetAnimator()->Play(m_strWalkLeftAnimKey, true);
	}
	break;
	case MON_STATE::FLOAT_IDLE:
	{
		GetAnimator()->Play(L"SCARFY_IDLE_LEFT", true);
	}
	break;
	case MON_STATE::IDLE:
	{
		GetAnimator()->Play(L"PENGY_IDLE_LEFT", true);
	}
	break;
	case MON_STATE::DRAWN:
	{
		if (GetObjDir() == 1)
			GetAnimator()->Play(m_strDrawnRightAnimKey, true);
		else
			GetAnimator()->Play(m_strDrawnLeftAnimKey, true);
	}
	}
}

void GameMonster::SetAI(AI* _pAI)
{
	m_pAI = _pAI;
	m_pAI->m_pOwner = this;
}

void GameMonster::OnCollisionEnter(GameCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Inhale")
	{
		m_pInhale = _pOther->GetObj();
	}
	else if (_pOther->GetObj()->GetName() == L"Power_Inhale")
	{
		m_pPowerInhale = _pOther->GetObj();
	}
}

void GameMonster::OnCollisionExit(GameCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Inhale")
	{
		m_pInhale = nullptr;
	}
	else if (_pOther->GetObj()->GetName() == L"Power_Inhale")
	{
		m_pPowerInhale = nullptr;
	}
}