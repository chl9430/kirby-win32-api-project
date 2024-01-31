#include "pch.h"
#include "GameMonster.h"

#include "GameResMgr.h"

#include "GamePlayer.h"
#include "GameAttack.h"

#include "GameAnimator.h"
#include "GameCollider.h"

#include "AI.h"
#include "GameState.h"
#include "GameDrawnState.h"

GameMonster::GameMonster(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject(_strName, _vPos, _vScale)
	, m_tInfo{}
	, m_pAI{ nullptr }
	, m_strWalkRightAnimKey{}
	, m_strWalkLeftAnimKey{}
	, m_strDrawnRightAnimKey{}
	, m_strDrawnLeftAnimKey{}
	, m_strStarAnimKey{}
	, m_bIsStar{ false }
{
	CreateAnimator();

	GameTexture* m_pStarTex = GameResMgr::GetInst()->LoadTexture(L"Star", L"texture\\Star.bmp");

	GetAnimator()->CreateAnimation(L"STAR", m_pStarTex, 0.15f);

	m_strStarAnimKey = L"STAR";
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
		if (GetObjDir() == 1)
			GetAnimator()->Play(m_strDrawnRightAnimKey, true);
		else
			GetAnimator()->Play(m_strDrawnLeftAnimKey, true);
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

	if (pOtherObj->GetName() == L"Player")
	{
		if (((GamePlayer*)pOtherObj)->GetPlayerState() == PLAYER_STATE::INHALE
			|| ((GamePlayer*)pOtherObj)->GetPlayerState() == PLAYER_STATE::POWER_INHALE)
		{
			m_bIsStar = true;
		}
	}
}

void GameMonster::OnCollision(GameCollider* _pOther)
{
	GameObject* pOther = _pOther->GetObj();

	if (_pOther->GetObj()->GetName() == L"Inhale")
	{
		GamePlayer* pPlayer = (GamePlayer*)((GameAttack*)pOther)->GetOwner();

		if (pPlayer->GetPlayerState() == PLAYER_STATE::INHALE)
		{
			m_pAI->SetCurState(MON_STATE::DRAWN);

			((GameDrawnState*)m_pAI->GetCurState())->SetDestPos(pPlayer->GetPos());
		}
	}
	else if (_pOther->GetObj()->GetName() == L"Power_Inhale")
	{
		GamePlayer* pPlayer = (GamePlayer*)((GameAttack*)pOther)->GetOwner();

		if (pPlayer->GetPlayerState() == PLAYER_STATE::POWER_INHALE)
		{
			m_pAI->SetCurState(MON_STATE::DRAWN);

			((GameDrawnState*)m_pAI->GetCurState())->SetDestPos(pPlayer->GetPos());
		}
	}
}

void GameMonster::OnCollisionExit(GameCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Inhale"
		|| _pOther->GetObj()->GetName() == L"Power_Inhale")
	{
		m_pAI->SetCurState(MON_STATE::WALK);
	}
}