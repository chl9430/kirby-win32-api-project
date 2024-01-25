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
	// ������ ���� ũ��
	float fForce = m_vForce.Length();

	if (fForce != 0.f)
	{
		// ������ ���� ����
		m_vForce.Normalize();

		// ���ӵ��� ũ��
		float m_fAccel = fForce / m_fMass;

		// ���ӵ�
		m_vAccel = m_vForce * m_fAccel;
	}

	// �߰� ���ӵ�
	m_vAccel += m_vAccelA;

	// �ӵ�
	m_vVelocity += m_vAccel * fDT;

	// �����¿� ���� �ݴ���� ���ӵ�
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
				if (m_pOwner->GetTouchBottom())
				{
					vFriction = vFricDir * 60.f * fDT;
				}
			}
		}

		if (m_vVelocity.Length() <= vFriction.Length()) // ���� �ӵ����� �������ӵ��� ũ�ٸ�
		{
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	// �ӵ� ���� �˻�
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		// ���� ���� ��(-1, 1)�� �����ϱ� ���� ����
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}

	// �ӵ��� ���� �̵�
	Move();

	// �� �ʱ�ȭ
	m_vForce = Vec2(0.f, 0.f);

	// ���ӵ� �ʱ�ȭ
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