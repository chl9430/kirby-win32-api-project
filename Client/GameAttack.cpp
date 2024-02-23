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
	GameObject* pOtherObj = _pOther->GetObj();

	if (_pOther->GetObj()->GetGroupType() == GROUP_TYPE::MONSTER)
	{
		if (GetName() == L"Inhale")
		{
			m_pOwner->AddInhaleRangeMon(pOtherObj);
		}
		else if (GetName() == L"Power_Inhale")
		{
			m_pOwner->AddPowerInhaleRangeMon(pOtherObj);
		}
	}
}

void GameAttack::OnCollision(GameCollider* _pOther)
{
}

void GameAttack::OnCollisionExit(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	if (_pOther->GetObj()->GetGroupType() == GROUP_TYPE::MONSTER)
	{
		if (GetName() == L"Inhale")
		{
			m_pOwner->RemoveInhaleRangeMon(pOtherObj);
		}
		else if (GetName() == L"Power_Inhale")
		{
			m_pOwner->RemovePowerInhaleRangeMon(pOtherObj);
		}
	}
}