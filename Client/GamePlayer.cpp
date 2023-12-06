#include "pch.h"
#include "GamePlayer.h"

#include "GameKeyMgr.h"
#include "GameResMgr.h"

#include "GameTexture.h"

#include "GameRigidBody.h"
#include "GameAnimator.h"
#include "GameAnimation.h"

GamePlayer::GamePlayer()
	: m_eCurState{ PLAYER_STATE::IDLE }
	, m_ePrevState{ PLAYER_STATE::WALK  }
	, m_iDir{ 1 }
	, m_iPrevDir{ 1 }
{
	CreateCollider();
	CreateRigidBody();

	// Texture 로딩
	GameTexture* pRightTex = GameResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Kirby_Walk_Right.bmp");

	CreateAnimator();

	// GetAnimator()->LoadAnimation(L"animation\\walk_down.anim");
	// GetAnimator()->FindAnimation(L"WALK_DOWN")->Save(L"animation\\walk_down.anim");

	CreateGravity();
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
	if (m_ePrevState == m_eCurState && m_iPrevDir == m_iDir)
		return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"IDLE_LEFT", true);
		else
			GetAnimator()->Play(L"IDLE_RIGHT", true);
	}
	break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"WALK_LEFT", true);
		else
			GetAnimator()->Play(L"WALK_RIGHT", true);
	}
	break;
	case PLAYER_STATE::JUMP:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"JUMP_LEFT", true);
		else
			GetAnimator()->Play(L"JUMP_RIGHT", true);
	}
	break;
	}
}