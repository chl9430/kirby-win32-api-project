#include "pch.h"
#include "GamePlayer.h"

#include "GameCore.h"

#include "GameKeyMgr.h"
#include "GameResMgr.h"
#include "GameTimeMgr.h"
#include "GameCamera.h"

#include "GameTexture.h"
#include "GameRigidBody.h"
#include "GameAnimator.h"
#include "GameAnimation.h"
#include "GameCollider.h"

GamePlayer::GamePlayer()
	: m_eCurState{ PLAYER_STATE::IDLE }
	, m_ePrevState{ PLAYER_STATE::WALK }
	, m_iDir{ 1 }
	, m_iPrevDir{ 1 }
	, m_fJumpStartPos{ 0 }
	, m_bRightMove{ false }
	, m_bLeftMove{ false }
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2{ 0.f, 0.f });
	GetCollider()->SetScale(Vec2{ 40.f, 36.f });

	CreateRigidBody();

	// Texture ·Îµù
	GameTexture* pIdleRightTex = GameResMgr::GetInst()->LoadTexture(L"IdleRight", L"texture\\Kirby_Idle_Right.bmp");
	GameTexture* pIdleLeftTex = GameResMgr::GetInst()->LoadTexture(L"IdleLeft", L"texture\\Kirby_Idle_Left.bmp");
	GameTexture* pWalkRightTex = GameResMgr::GetInst()->LoadTexture(L"WalkRight", L"texture\\Kirby_Walk_Right.bmp");
	GameTexture* pWalkLeftTex = GameResMgr::GetInst()->LoadTexture(L"WalkLeft", L"texture\\Kirby_Walk_Left.bmp");
	GameTexture* pRunRightTex = GameResMgr::GetInst()->LoadTexture(L"RunRight", L"texture\\Kirby_Run_Right.bmp");
	GameTexture* pRunLeftTex = GameResMgr::GetInst()->LoadTexture(L"RunLeft", L"texture\\Kirby_Run_Left.bmp");
	GameTexture* pStopRightTex = GameResMgr::GetInst()->LoadTexture(L"StopRight", L"texture\\Kirby_Stop_Right.bmp");
	GameTexture* pStopLeftTex = GameResMgr::GetInst()->LoadTexture(L"StopLeft", L"texture\\Kirby_Stop_Left.bmp");
	GameTexture* pJumpRightTex = GameResMgr::GetInst()->LoadTexture(L"JumpRight", L"texture\\Kirby_Jump_Right.bmp");
	GameTexture* pJumpLeftTex = GameResMgr::GetInst()->LoadTexture(L"JumpLeft", L"texture\\Kirby_Jump_Left.bmp");
	GameTexture* pDropRightTex = GameResMgr::GetInst()->LoadTexture(L"DropRight", L"texture\\Kirby_Drop_Right.bmp");
	GameTexture* pDropLeftTex = GameResMgr::GetInst()->LoadTexture(L"DropLeft", L"texture\\Kirby_Drop_Left.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pIdleRightTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pIdleLeftTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pWalkRightTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pWalkLeftTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);
	GetAnimator()->CreateAnimation(L"RUN_RIGHT", pRunRightTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);
	GetAnimator()->CreateAnimation(L"RUN_LEFT", pRunLeftTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);
	GetAnimator()->CreateAnimation(L"STOP_RIGHT", pStopRightTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);
	GetAnimator()->CreateAnimation(L"STOP_LEFT", pStopLeftTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);
	GetAnimator()->CreateAnimation(L"JUMP_RIGHT", pJumpRightTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);
	GetAnimator()->CreateAnimation(L"JUMP_LEFT", pJumpLeftTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.07f, 4);
	GetAnimator()->CreateAnimation(L"DROP_RIGHT", pDropRightTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.03f, 4);
	GetAnimator()->CreateAnimation(L"DROP_LEFT", pDropLeftTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.03f, 4);

	// GetAnimator()->LoadAnimation(L"animation\\walk_down.anim");
	// GetAnimator()->FindAnimation(L"WALK_DOWN")->Save(L"animation\\walk_down.anim");

	CreateGravity();
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::Update()
{
	UpdateDirection();
	UpdateState();
	UpdateMove();
	UpdateAnimation();

	if (GetPos().x >= (float)GameCore::GetInst()->GetResolution().x / 2)
	{
		GameCamera::GetInst()->SetTargetObj(this);
	}

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void GamePlayer::Render(HDC _dc)
{
	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"Left : %d, Right : %d, Dir : %d, SecondDir : %d", m_bLeftMove, m_bRightMove, m_iDir, m_iSecondDir);
	SetWindowText(GameCore::GetInst()->GetMainHwnd(), szBuffer);

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

void GamePlayer::UpdateDirection()
{
	/*if (KEY_TAP(KEY::A))
	{
		m_iDir = -1;
	}

	if (KEY_TAP(KEY::D))
	{
		m_iDir = 1;
	}

	if (KEY_TAP(KEY::A) && KEY_HOLD(KEY::D))
	{
		m_iDir = -1;
	}

	if (KEY_TAP(KEY::D) && KEY_HOLD(KEY::A))
	{
		m_iDir = 1;
	}

	if (KEY_AWAY(KEY::A) && KEY_HOLD(KEY::D))
	{
		m_iDir = 1;
	}

	if (KEY_AWAY(KEY::D) && KEY_HOLD(KEY::A))
	{
		m_iDir = -1;
	}*/
}

void GamePlayer::UpdateState()
{
	if (m_eCurState == PLAYER_STATE::WALK_READY && GetRigidBody()->GetVelocity().Length() == 0.f)
	{
		if (KEY_HOLD(KEY::A) || KEY_HOLD(KEY::D))
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
		else
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}

	if (m_eCurState == PLAYER_STATE::JUMP)
	{
		if (GetRigidBody()->GetVelocity().y >= 0.f)
		{
			m_eCurState = PLAYER_STATE::DROP;
		}
	}

	if (m_eCurState == PLAYER_STATE::IDLE)
	{
		if (m_ePrevState == PLAYER_STATE::DROP)
		{
			if (KEY_HOLD(KEY::A) || KEY_HOLD(KEY::D))
			{
				m_eCurState = PLAYER_STATE::WALK;
			}
			else
			{
				if (GetRigidBody()->GetVelocity().x != 0.f)
				{
					m_eCurState = PLAYER_STATE::WALK_READY;
				}
				else
				{
					m_eCurState = PLAYER_STATE::IDLE;
				}
			}
		}
	}

	if (KEY_TAP(KEY::A))
	{
		m_iDir = -1;


		if (m_eCurState == PLAYER_STATE::IDLE)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (KEY_TAP(KEY::D))
	{
		m_iDir = 1;

		if (m_eCurState == PLAYER_STATE::IDLE)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (KEY_AWAY(KEY::A))
	{
		if (m_eCurState == PLAYER_STATE::WALK)
		{
			if (!(KEY_HOLD(KEY::D)))
			{
				m_eCurState = PLAYER_STATE::WALK_READY;
			}
		}
	}

	if (KEY_AWAY(KEY::D))
	{
		if (m_eCurState == PLAYER_STATE::WALK)
		{
			if (!(KEY_HOLD(KEY::A)))
			{
				m_eCurState = PLAYER_STATE::WALK_READY;
			}
		}
	}

	if (KEY_TAP(KEY::A) && KEY_HOLD(KEY::D))
	{
		m_iDir = -1;
	}

	if (KEY_TAP(KEY::D) && KEY_HOLD(KEY::A))
	{
		m_iDir = 1;
	}

	if (KEY_AWAY(KEY::A) && KEY_HOLD(KEY::D))
	{
		m_iDir = 1;
	}

	if (KEY_AWAY(KEY::D) && KEY_HOLD(KEY::A))
	{
		m_iDir = -1;
	}
}

void GamePlayer::UpdateMove()
{
	GameRigidBody* pRigid = GetRigidBody();

	if (m_eCurState == PLAYER_STATE::WALK)
	{
		isRunning = false;
		pRigid->AddForce(Vec2{ 150.f, 0.f } * (float)m_iDir);
	}
	
	if (m_eCurState == PLAYER_STATE::RUN)
	{
		isRunning = true;
		pRigid->AddForce(Vec2{ 200.f, 0.f } * (float)m_iDir);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		m_eCurState = PLAYER_STATE::JUMP;

		if (GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, -300.f });
		}
	}

	if (m_eCurState == PLAYER_STATE::JUMP || m_eCurState == PLAYER_STATE::DROP)
	{
		if (KEY_HOLD(KEY::A) || KEY_HOLD(KEY::D))
		{
			pRigid->AddForce(Vec2{ 150.f * (float)m_iDir, GetRigidBody()->GetVelocity().y });
		}
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
	case PLAYER_STATE::WALK_READY:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"WALK_LEFT", true);
		else
			GetAnimator()->Play(L"WALK_RIGHT", true);
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
	case PLAYER_STATE::WALK_STOP:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"STOP_RIGHT", true);
		else
			GetAnimator()->Play(L"STOP_LEFT", true);
	}
	break;
	case PLAYER_STATE::RUN_READY:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"WALK_LEFT", true);
		else
			GetAnimator()->Play(L"WALK_RIGHT", true);
	}
	break;
	case PLAYER_STATE::RUN:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"RUN_LEFT", true);
		else
			GetAnimator()->Play(L"RUN_RIGHT", true);
	}
	break;
	case PLAYER_STATE::RUN_STOP:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"STOP_LEFT", true);
		else
			GetAnimator()->Play(L"STOP_RIGHT", true);
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
	case PLAYER_STATE::DROP:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"DROP_LEFT", false);
		else
			GetAnimator()->Play(L"DROP_RIGHT", false);
	}
	break;
	}
}

void GamePlayer::UpdateGravity()
{
	GetRigidBody()->AddForce(Vec2{ 0.f, 500.f });
}