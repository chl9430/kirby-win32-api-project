#include "pch.h"
#include "GameMissile.h"

#include "GameTimeMgr.h"

#include "GameCollider.h"
#include "GameRigidBody.h"
#include "GameAnimator.h"
#include "GameAnimation.h"

GameMissile::GameMissile(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject{ _strName, _vPos, _vScale }
	, m_pOwner{ nullptr }
	, m_fMissileSpeed{ 500.f }
{
}

GameMissile::~GameMissile()
{
}

void GameMissile::Update()
{
	if (GetAnimator()->GetCurrentAnim()->GetName() == L"STAR_DESTROY")
	{
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			DestroyObj();
		}
	}
	else
	{
		Vec2 vPos = GetPos();

		SetPos(Vec2{ vPos.x + (m_fMissileSpeed * fDT), vPos.y });
	}
}

void GameMissile::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void GameMissile::FollowOwner()
{
	Vec2 vOwnerPos = m_pOwner->GetPos();
	int iOwnerDir = m_pOwner->GetObjDir();

	SetPos(Vec2{ vOwnerPos.x + iOwnerDir, vOwnerPos.y });
	SetObjDir(iOwnerDir);
}

void GameMissile::OnCollisionEnter(GameCollider* _pOther)
{
}

void GameMissile::OnCollision(GameCollider* _pOther)
{
	GameObject* pOther = _pOther->GetObj();

	if (pOther->GetGroupType() == GROUP_TYPE::TILE)
	{
		if (GetTouchRight() || GetTouchLeft())
		{
			GetAnimator()->Play(L"STAR_DESTROY", false);
		}
	}

	if (pOther->GetGroupType() == GROUP_TYPE::MONSTER)
	{
		GetAnimator()->Play(L"STAR_DESTROY", false);
	}
}

void GameMissile::OnCollisionExit(GameCollider* _pOther)
{
}