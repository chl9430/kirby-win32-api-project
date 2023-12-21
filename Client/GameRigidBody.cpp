#include "pch.h"
#include "GameRigidBody.h"

#include "GameTimeMgr.h"

#include "GameObject.h"
#include "GamePlayer.h"
#include "GameGravity.h"

GameRigidBody::GameRigidBody()
	: m_pOwner{ nullptr }
	, m_vForce{}
	, m_vVelocity{}
	, m_fMass{ 1.f }
	, m_vAccel{}
	, m_vAccelA{}
	, m_fFricCoeff{ 100.f }
	, m_vMaxVelocity{ Vec2{ 200.f, 600.f } }
{
}

GameRigidBody::~GameRigidBody()
{
}

void GameRigidBody::FinalUpdate()
{
	// 순수한 힘의 크기
	float fForce = m_vForce.Length();

	if (fForce != 0.f)
	{
		// 순수한 힘의 방향
		m_vForce.Normalize();

		// 가속도의 크기
		float m_fAccel = fForce / m_fMass;

		// 가속도
		m_vAccel = m_vForce * m_fAccel;
	}

	// 추가 가속도
	m_vAccel += m_vAccelA;

	// 속도
	m_vVelocity += m_vAccel * fDT;

	// 마찰력에 의한 반대방향 가속도
	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		Vec2 vFriction = vFricDir * m_fFricCoeff * fDT;

		if (m_pOwner->GetName() == L"Player")
		{
			GamePlayer* pPlayer = (GamePlayer*)m_pOwner;

			if (pPlayer->GetPlayerState() == PLAYER_STATE::FLOAT_START
				|| pPlayer->GetPlayerState() == PLAYER_STATE::FLOAT_IDLE
				|| pPlayer->GetPlayerState() == PLAYER_STATE::FLOAT_END)
			{
				if (m_pOwner->GetGravity()->IsOnTheGround())
				{
					vFriction = vFricDir * 60.f * fDT;
				}
			}
		}

		if (m_vVelocity.Length() <= vFriction.Length()) // 본래 속도보다 마찰가속도가 크다면
		{
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	// 속도 제한 검사
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		// 기존 방향 값(-1, 1)을 유지하기 위한 공식
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}

	// 속도에 따른 이동
	Move();

	// 힘 초기화
	m_vForce = Vec2(0.f, 0.f);

	// 가속도 초기화
	m_vAccel = Vec2{ 0.f, 0.f };
	m_vAccelA = Vec2{ 0.f, 0.f };
}

void GameRigidBody::Move()
{
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		Vec2 vPos = m_pOwner->GetPos();

		vPos += m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);
	}
}