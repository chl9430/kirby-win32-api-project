#include "pch.h"
#include "GameAttack.h"

#include "GamePlayer.h"
#include "GameMonster.h"

#include "GameCollider.h"

#include "AI.h"
#include "GameDrawnState.h"

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

void GameAttack::OnCollisionEnter(GameCollider* _pOther)
{
}

void GameAttack::OnCollision(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	if (_pOther->GetObj()->GetName() == L"Waddle_Dee")
	{
		GameMonster* pMon = (GameMonster*)pOtherObj;

		if (GetName() == L"Inhale" // 커비가 일반 빨아들이기 상태일 경우, 몬스터가 일반 빨아들이기 범위 내라면
			&& ((GamePlayer*)m_pOwner)->GetPlayerState() == PLAYER_STATE::INHALE
			&& pMon->GetAI()->GetCurState()->GetType() != MON_STATE::EATEN)
		{
			pMon->GetAI()->SetCurState(MON_STATE::DRAWN);

			((GameDrawnState*)pMon->GetAI()->GetCurState())->SetDestPos(m_pOwner->GetPos());
		}
		else if (GetName() == L"Power_Inhale" // 커비가 강한 빨아들이기 상태일 경우, 몬스터가 강한 빨아들이기 범위 내라면
			&& ((GamePlayer*)m_pOwner)->GetPlayerState() == PLAYER_STATE::POWER_INHALE
			&& pMon->GetAI()->GetCurState()->GetType() != MON_STATE::EATEN)
		{
			pMon->GetAI()->SetCurState(MON_STATE::DRAWN);

			((GameDrawnState*)pMon->GetAI()->GetCurState())->SetDestPos(m_pOwner->GetPos());
		}

		// 커비가 제한 시간 내로 몬스터를 빨아들이지 못했다면
		if (pMon->GetAI()->GetCurState()->GetType() == MON_STATE::DRAWN
			&& ((GamePlayer*)m_pOwner)->GetPlayerState() == PLAYER_STATE::IDLE)
		{
			pMon->GetAI()->SetCurState(MON_STATE::WALK);
		}
	}
}

void GameAttack::OnCollisionExit(GameCollider* _pOther)
{
}