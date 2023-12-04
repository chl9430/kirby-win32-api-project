#include "pch.h"
#include "GamePlayer.h"

#include "GameKeyMgr.h"

#include "GameRigidBody.h"

GamePlayer::GamePlayer()
	: m_eCurState{ PLAYER_STATE::IDLE }
	, m_ePrevState{ PLAYER_STATE::WALK  }
	, m_iDir{ 1 }
	, m_iPrevDir{ 1 }
{
	CreateCollider();
	CreateRigidBody();
	CreateCollider();
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::Update()
{
	UpdateMove();

	UpdateState();

	UpdateAnimation();

	/*if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2{ 640.f, 384.f });
	}*/

	// GetAnimator()->Update();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void GamePlayer::UpdateState()
{
	if (KEY_HOLD(KEY::A))
	{
		m_iDir = -1;

		if (m_eCurState != PLAYER_STATE::JUMP) // 점프 상태일때는 걷는 상태가 될 수 없다.
			m_eCurState = PLAYER_STATE::WALK;
	}

	if (KEY_HOLD(KEY::D))
	{
		m_iDir = 1;

		if (m_eCurState != PLAYER_STATE::JUMP)
			m_eCurState = PLAYER_STATE::WALK;
	}

	if (GetRigidBody()->GetSpeed() == 0.f && m_eCurState != PLAYER_STATE::JUMP)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}

	if (KEY_TAP(KEY::SPACE)) // 플레이어 점프
	{
		m_eCurState = PLAYER_STATE::JUMP;

		if (GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, -300.f });
		}
	}
}

void GamePlayer::UpdateMove()
{
	GameRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2{ -200.f, 0.f });
	}

	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2{ 200.f, 0.f });
	}

	if (KEY_TAP(KEY::A))
	{
		pRigid->SetVelocity(Vec2{ -100.f, pRigid->GetVelocity().y });
	}

	if (KEY_TAP(KEY::D))
	{
		pRigid->SetVelocity(Vec2{ -100.f, pRigid->GetVelocity().y });
	}
}

void GamePlayer::UpdateAnimation()
{
}
