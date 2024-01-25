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
#include "GameGravity.h"

GamePlayer::GamePlayer(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject{ _strName, _vPos, _vScale }
	, m_eCurState{ PLAYER_STATE::IDLE }
	, m_ePrevState{ PLAYER_STATE::WALK }
	, m_iDir{ 1 }
	, m_iPrevDir{ 1 }
	, isRunning{ false }
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2{ 0.f, 0.f });
	GetCollider()->SetScale(Vec2{ TILE_SIZE, TILE_SIZE });

	CreateRigidBody();

	// Texture 로딩
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
	GameTexture* pFloatStartRightTex = GameResMgr::GetInst()->LoadTexture(L"FloatStartRight", L"texture\\Kirby_Float_Start_Right.bmp");
	GameTexture* pFloatStartLeftTex = GameResMgr::GetInst()->LoadTexture(L"FloatStartLeft", L"texture\\Kirby_Float_Start_Left.bmp");
	GameTexture* pFloatIdleRightTex = GameResMgr::GetInst()->LoadTexture(L"FloatIdleRight", L"texture\\Kirby_Float_Idle_Right.bmp");
	GameTexture* pFloatIdleLeftTex = GameResMgr::GetInst()->LoadTexture(L"FloatIdleLeft", L"texture\\Kirby_Float_Idle_Left.bmp");

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
	GetAnimator()->CreateAnimation(L"FLOAT_START_RIGHT", pFloatStartRightTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.03f, 4);
	GetAnimator()->CreateAnimation(L"FLOAT_START_LEFT", pFloatStartLeftTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.03f, 4);
	GetAnimator()->CreateAnimation(L"FLOAT_IDLE_RIGHT", pFloatIdleRightTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.1f, 4);
	GetAnimator()->CreateAnimation(L"FLOAT_IDLE_LEFT", pFloatIdleLeftTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.1f, 4);
	GetAnimator()->CreateAnimation(L"FLOAT_END_RIGHT", pFloatStartRightTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.03f, 4);
	GetAnimator()->CreateAnimation(L"FLOAT_END_LEFT", pFloatStartLeftTex, Vec2{ 0.f, 0.f }, Vec2{ 20.f, 19.f }, Vec2{ 10.f, 0.f }, 0.03f, 4);

	// GetAnimator()->LoadAnimation(L"animation\\walk_down.anim");
	// GetAnimator()->FindAnimation(L"WALK_DOWN")->Save(L"animation\\walk_down.anim");

	CreateGravity();
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::Update()
{
	UpdateState();
	UpdateMove();
	UpdateAnimation();

	if (GetPos().y >= (float)GameCore::GetInst()->GetResolution().y / 2 || GetPos().x >= (float)GameCore::GetInst()->GetResolution().x / 2)
	{
		GameCamera::GetInst()->SetTargetObj(this);
	}

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
			if (m_eCurState != PLAYER_STATE::FLOAT_START
				&& m_eCurState != PLAYER_STATE::FLOAT_IDLE
				&& m_eCurState != PLAYER_STATE::FLOAT_END)
			{
				m_eCurState = PLAYER_STATE::IDLE;
			}
		}
	}
}

void GamePlayer::UpdateState()
{
	//// 걷기 준비 자세에서 보통상태로 자유롭게 전환
	//if (m_eCurState == PLAYER_STATE::WALK_READY && GetRigidBody()->GetVelocity().Length() == 0.f)
	//{
	//	if (KEY_HOLD(KEY::LEFT) || KEY_HOLD(KEY::RIGHT))
	//	{
	//		m_eCurState = PLAYER_STATE::WALK;
	//	}
	//	else
	//	{
	//		m_eCurState = PLAYER_STATE::IDLE;
	//	}
	//}

	//// 떠다니기 진입시 애니메이션을 자연스럽게 전환
	//if (m_eCurState == PLAYER_STATE::FLOAT_START)
	//{
	//	if (GetAnimator()->GetCurrentAnim()->IsFinish())
	//	{
	//		m_eCurState = PLAYER_STATE::FLOAT_IDLE;
	//	}
	//}

	//// 떠다니기 탈출시 애니메이션을 자연스럽게 전환
	//if (m_eCurState == PLAYER_STATE::FLOAT_END)
	//{
	//	if (GetAnimator()->GetCurrentAnim()->IsFinish())
	//	{
	//		if (GetGravity()->IsOnTheGround())
	//		{
	//			m_eCurState = PLAYER_STATE::IDLE;
	//		}
	//		else
	//		{
	//			m_eCurState = PLAYER_STATE::DROP;
	//		}
	//	}
	//}

	//// 떠다니기 상태에서 S를 누르면 떠다니기 상태에서 탈출
	//if (m_eCurState == PLAYER_STATE::FLOAT_IDLE)
	//{
	//	if (KEY_TAP(KEY::S))
	//	{
	//		m_eCurState = PLAYER_STATE::FLOAT_END;
	//	}
	//}

	//// 점프나 드롭상태에서 한번 더 점프하면 떠다니기 모드로 전환
	//if (m_eCurState == PLAYER_STATE::JUMP || m_eCurState == PLAYER_STATE::DROP)
	//{
	//	if (KEY_TAP(KEY::D))
	//	{
	//		m_eCurState = PLAYER_STATE::FLOAT_START;
	//	}
	//}

	//// 점프하다가 떨어질때 드롭으로 상태변경
	//if (m_eCurState == PLAYER_STATE::JUMP)
	//{
	//	if (GetRigidBody()->GetVelocity().y >= 0.f)
	//	{
	//		if (!(m_eCurState == PLAYER_STATE::FLOAT_START || m_eCurState == PLAYER_STATE::FLOAT_IDLE))
	//		{
	//			m_eCurState = PLAYER_STATE::DROP;
	//		}
	//	}
	//}

	//if (m_eCurState == PLAYER_STATE::IDLE)
	//{
	//	// 떨어진 시점에 키를 누르고 있으면 걷고, 그렇지 않다면 천천히 걸은 후 일반 모드로 진입
	//	if (m_ePrevState == PLAYER_STATE::DROP)
	//	{
	//		if (KEY_HOLD(KEY::LEFT) || KEY_HOLD(KEY::RIGHT))
	//		{
	//			m_eCurState = PLAYER_STATE::WALK;
	//		}
	//		else
	//		{
	//			if (GetRigidBody()->GetVelocity().x != 0.f)
	//			{
	//				m_eCurState = PLAYER_STATE::WALK_READY;
	//			}
	//			else
	//			{
	//				m_eCurState = PLAYER_STATE::IDLE;
	//			}
	//		}
	//	}

	//	if (m_ePrevState == PLAYER_STATE::FLOAT_END)
	//	{
	//		if (KEY_HOLD(KEY::LEFT) || KEY_HOLD(KEY::RIGHT))
	//		{
	//			m_eCurState = PLAYER_STATE::WALK;
	//		}
	//		else
	//		{
	//			if (GetRigidBody()->GetVelocity().x != 0.f)
	//			{
	//				m_eCurState = PLAYER_STATE::WALK_READY;
	//			}
	//			else
	//			{
	//				m_eCurState = PLAYER_STATE::IDLE;
	//			}
	//		}
	//	}
	//}

	//if (KEY_TAP(KEY::LEFT))
	//{
	//	m_iDir = -1;


	//	if (m_eCurState == PLAYER_STATE::IDLE)
	//	{
	//		m_eCurState = PLAYER_STATE::WALK;
	//	}
	//}

	//if (KEY_TAP(KEY::RIGHT))
	//{
	//	m_iDir = 1;

	//	if (m_eCurState == PLAYER_STATE::IDLE)
	//	{
	//		m_eCurState = PLAYER_STATE::WALK;
	//	}
	//}

	//if (KEY_AWAY(KEY::LEFT))
	//{
	//	if (m_eCurState == PLAYER_STATE::WALK)
	//	{
	//		if (!(KEY_HOLD(KEY::RIGHT)))
	//		{
	//			m_eCurState = PLAYER_STATE::WALK_READY;
	//		}
	//	}
	//}

	//if (KEY_AWAY(KEY::RIGHT))
	//{
	//	if (m_eCurState == PLAYER_STATE::WALK)
	//	{
	//		if (!(KEY_HOLD(KEY::LEFT)))
	//		{
	//			m_eCurState = PLAYER_STATE::WALK_READY;
	//		}
	//	}
	//}

	//if (KEY_TAP(KEY::LEFT) && KEY_HOLD(KEY::RIGHT))
	//{
	//	m_iDir = -1;
	//}

	//if (KEY_TAP(KEY::RIGHT) && KEY_HOLD(KEY::LEFT))
	//{
	//	m_iDir = 1;
	//}

	//if (KEY_AWAY(KEY::LEFT) && KEY_HOLD(KEY::RIGHT))
	//{
	//	m_iDir = 1;
	//}

	//if (KEY_AWAY(KEY::RIGHT) && KEY_HOLD(KEY::LEFT))
	//{
	//	m_iDir = -1;
	//}
}

void GamePlayer::UpdateMove()
{
	GameRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::RIGHT))
	{
		pRigid->SetVelocity(Vec2{ 70.f, GetRigidBody()->GetVelocity().y });
	}

	if (KEY_HOLD(KEY::LEFT))
	{
		pRigid->SetVelocity(Vec2{ -70.f, GetRigidBody()->GetVelocity().y });
	}

	if (KEY_HOLD(KEY::D))
	{
		GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, -200.f });
	}
	/*if (m_eCurState == PLAYER_STATE::WALK)
	{
		isRunning = false;
		pRigid->AddForce(Vec2{ 125.f * (float)m_iDir, GetRigidBody()->GetVelocity().y });
	}

	if (m_eCurState == PLAYER_STATE::RUN)
	{
		isRunning = true;
		pRigid->AddForce(Vec2{ 200.f * (float)m_iDir, 0.f });
	}

	if (m_eCurState == PLAYER_STATE::FLOAT_IDLE || m_eCurState == PLAYER_STATE::FLOAT_START || m_eCurState == PLAYER_STATE::FLOAT_END)
	{
		if (KEY_HOLD(KEY::LEFT) || KEY_HOLD(KEY::RIGHT))
		{
			pRigid->AddForce(Vec2{ 70.f * (float)m_iDir, GetRigidBody()->GetVelocity().y });
		}
	}

	if (KEY_TAP(KEY::D))
	{
		if (!(m_eCurState == PLAYER_STATE::FLOAT_START || m_eCurState == PLAYER_STATE::FLOAT_IDLE || m_eCurState == PLAYER_STATE::FLOAT_END))
		{
			m_eCurState = PLAYER_STATE::JUMP;
			GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, -300.f });
		}
		else
		{
			GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, -200.f });
		}
	}

	if (m_eCurState == PLAYER_STATE::JUMP || m_eCurState == PLAYER_STATE::DROP)
	{
		if (KEY_HOLD(KEY::LEFT) || KEY_HOLD(KEY::RIGHT))
		{
			pRigid->AddForce(Vec2{ 150.f * (float)m_iDir, GetRigidBody()->GetVelocity().y });
		}
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
	case PLAYER_STATE::JUMP:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"JUMP_LEFT", true);
		else
			GetAnimator()->Play(L"JUMP_RIGHT", true);
	}
	break;
	case PLAYER_STATE::FLOAT_START:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"FLOAT_START_LEFT", false);
		else
			GetAnimator()->Play(L"FLOAT_START_RIGHT", false);
	}
	break;
	case PLAYER_STATE::FLOAT_IDLE:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"FLOAT_IDLE_LEFT", true);
		else
			GetAnimator()->Play(L"FLOAT_IDLE_RIGHT", true);
	}
	break;
	case PLAYER_STATE::FLOAT_END:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"FLOAT_END_LEFT", false);
		else
			GetAnimator()->Play(L"FLOAT_END_RIGHT", false);
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