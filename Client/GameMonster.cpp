#include "pch.h"
#include "GameMonster.h"

#include "GameResMgr.h"
#include "GameEventMgr.h"

#include "GamePlayer.h"
#include "GameAttack.h"

#include "GameAnimator.h"
#include "GameAnimation.h"
#include "GameCollider.h"
#include "GameRigidBody.h"

#include "AI.h"
#include "GameState.h"
#include "GameDrawnState.h"
#include "GameEatenState.h"

GameMonster::GameMonster(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject(_strName, _vPos, _vScale)
	, m_tInfo{}
	, m_pAI{ nullptr }
	, m_strWalkRightAnimKey{}
	, m_strWalkLeftAnimKey{}
	, m_strDrawnRightAnimKey{}
	, m_strDrawnLeftAnimKey{}
	, m_strStarAnimKey{}
	, m_strStarDestroyAnimKey{}
	, m_bIsStar{ false }
{
	CreateAnimator();

	GameTexture* m_pStarTex = GameResMgr::GetInst()->LoadTexture(L"Star", L"texture\\Star.bmp");
	GameTexture* m_pStarDestroyTex = GameResMgr::GetInst()->LoadTexture(L"Star_Destroy", L"texture\\Star_Destroy.bmp");

	GetAnimator()->CreateAnimation(L"STAR", m_pStarTex, 0.15f);
	GetAnimator()->CreateAnimation(L"STAR_DESTROY", m_pStarDestroyTex, 0.03f);

	m_strStarAnimKey = L"STAR";
	m_strStarDestroyAnimKey = L"STAR_DESTROY";
}

GameMonster::~GameMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}

void GameMonster::Update()
{
	if (m_bIsDestroying)
	{
		GetAnimator()->Play(m_strStarDestroyAnimKey, false);

		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			DestroyMon();
		}
	}
	else
	{
		UpdateAnimation();

		if (nullptr != m_pAI)
			m_pAI->Update();
	}
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
	if (m_bIsStar)
	{
		GetAnimator()->Play(m_strStarAnimKey, true);
		return;
	}

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
		if (GetAnimator()->GetCurrentAnim()->GetName() != m_strStarAnimKey)
		{
			if (GetObjDir() == 1)
				GetAnimator()->Play(m_strDrawnRightAnimKey, true);
			else
				GetAnimator()->Play(m_strDrawnLeftAnimKey, true);
		}
	}
	break;
	}
}

void GameMonster::DestroyMon()
{
	tEvent tEve = {};
	tEve.eEven = EVENT_TYPE::DELETE_OBJECT;
	tEve.lParam = (DWORD_PTR)this;

	GameEventMgr::GetInst()->AddEvent(tEve);
}

void GameMonster::SetAI(AI* _pAI)
{
	m_pAI = _pAI;
	m_pAI->m_pOwner = this;
}

void GameMonster::OnCollisionEnter(GameCollider* _pOther)
{
}

void GameMonster::OnCollision(GameCollider* _pOther)
{
	GameObject* pOther = _pOther->GetObj();

	if (pOther->GetName() == L"Tile" && m_bIsStar && m_pAI->GetCurState()->GetType() == MON_STATE::LAUNCHED && GetTouchRight())
	{
		m_bIsDestroying = true;
	}
}

void GameMonster::OnCollisionExit(GameCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Inhale"
		|| _pOther->GetObj()->GetName() == L"Power_Inhale")
	{
		if (!m_bIsStar)
		{
			m_pAI->SetCurState(MON_STATE::WALK);
		}
	}
}