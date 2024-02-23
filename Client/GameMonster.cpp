#include "pch.h"
#include "GameMonster.h"

#include "GameResMgr.h"
#include "GameEventMgr.h"
#include "GameTimeMgr.h"

#include "GamePlayer.h"
#include "GameAttack.h"

#include "GameAnimator.h"
#include "GameAnimation.h"
#include "GameCollider.h"
#include "GameRigidBody.h"

#include "AI.h"
#include "GameState.h"
#include "GameDrawnState.h"
#include "GameHitState.h"

GameMonster::GameMonster(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject(_strName, _vPos, _vScale)
	, m_tInfo{}
	, m_eMonType{ MON_TYPE::NORMAL }
	, m_pAI{ nullptr }
	, m_strWalkRightAnimKey{}
	, m_strWalkLeftAnimKey{}
	, m_strDrawnRightAnimKey{}
	, m_strDrawnLeftAnimKey{}
	, m_strHitRightAnimKey{}
	, m_strHitLeftAnimKey{}
	, m_fHitTime{ 0.f }
	, m_fHitFinishTime{ 0.1f }
{
	CreateAnimator();
}

GameMonster::~GameMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}

void GameMonster::Update()
{
	UpdateAnimation();

	if (GetAI()->GetCurState()->GetType() == MON_STATE::HIT)
	{
		m_fHitTime += fDT;

		if (m_fHitTime >= m_fHitFinishTime)
		{
			m_pAI->SetCurState(MON_STATE::WALK);

			m_fHitTime = 0.f;
		}
	}

	if (nullptr != m_pAI)
		m_pAI->Update();
}

void GameMonster::Render(HDC _dc)
{
	if (m_pAI->GetCurState()->GetType() != MON_STATE::EATEN)
	{
		ComponentRender(_dc);
	}
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
	break;
	case MON_STATE::HIT:
	{
		if (GetObjDir() == 1)
			GetAnimator()->Play(m_strHitRightAnimKey, true);
		else
			GetAnimator()->Play(m_strHitLeftAnimKey, true);
	}
	break;
	}
}

void GameMonster::SetAI(AI* _pAI)
{
	m_pAI = _pAI;
	m_pAI->m_pOwner = this;
}

void GameMonster::OnCollisionEnter(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetGroupType() == GROUP_TYPE::STAR)
	{
		GetAI()->SetCurState(MON_STATE::HIT);
	}
}

void GameMonster::OnCollision(GameCollider* _pOther)
{
}

void GameMonster::OnCollisionExit(GameCollider* _pOther)
{
}