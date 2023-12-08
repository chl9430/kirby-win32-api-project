#include "pch.h"
#include "GamePlayer.h"

#include "GameKeyMgr.h"
#include "GameResMgr.h"

#include "GameTexture.h"
#include "GameRigidBody.h"
#include "GameAnimator.h"
#include "GameAnimation.h"
#include "GameCollider.h"

GamePlayer::GamePlayer()
	: m_eCurState{ PLAYER_STATE::IDLE }
	, m_ePrevState{ PLAYER_STATE::WALK  }
	, m_iDir{ 1 }
	, m_iPrevDir{ 1 }
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2{ 0.f, 0.f });
	GetCollider()->SetScale(Vec2{ 40.f, 36.f });

	CreateRigidBody();

	// Texture 로딩
	GameTexture* pIdleRightTex = GameResMgr::GetInst()->LoadTexture(L"IdleRight", L"texture\\Kirby_Idle_Right.bmp");
	GameTexture* pIdleLeftTex = GameResMgr::GetInst()->LoadTexture(L"IdleLeft", L"texture\\Kirby_Idle_Left.bmp");
	GameTexture* pWalkRightTex = GameResMgr::GetInst()->LoadTexture(L"WalkRight", L"texture\\Kirby_Walk_Right.bmp");
	GameTexture* pWalkLeftTex = GameResMgr::GetInst()->LoadTexture(L"WalkLeft", L"texture\\Kirby_Walk_Left.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pIdleRightTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pIdleLeftTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pWalkRightTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pWalkLeftTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);

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

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void GamePlayer::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void GamePlayer::OnCollisionEnter(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Ground")
	{
		Vec2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
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

	/*if (KEY_TAP(KEY::A))
	{
		pRigid->SetVelocity(Vec2{ -100.f, pRigid->GetVelocity().y });
	}

	if (KEY_TAP(KEY::D))
	{
		pRigid->SetVelocity(Vec2{ 100.f, pRigid->GetVelocity().y });
	}*/
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

void GamePlayer::UpdateGravity()
{
	GetRigidBody()->AddForce(Vec2{ 0.f, 500.f });
}