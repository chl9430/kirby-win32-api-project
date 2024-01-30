#include "pch.h"
#include "GamePlayer.h"

#include "GameCore.h"

#include "GameKeyMgr.h"
#include "GameResMgr.h"
#include "GameTimeMgr.h"
#include "GameCamera.h"
#include "GameCollisionMgr.h"

#include "GameTexture.h"

#include "GameScene.h"

#include "GameAttack.h"

#include "GameAnimator.h"
#include "GameAnimation.h"
#include "GameRigidBody.h"
#include "GameCollider.h"
#include "GameGravity.h"

#define IS_KIRBY_MOVING GetTouchBottom() && (KEY_HOLD(KEY::LEFT) || KEY_HOLD(KEY::RIGHT))
#define IS_KIRBY_FALLING !GetTouchBottom() && (GetRigidBody()->GetVelocity().y > 0.f)
#define IS_KIRBY_IDLING GetTouchBottom() && (GetRigidBody()->GetVelocity().x == 0.f)

GamePlayer::GamePlayer(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject{ _strName, _vPos, _vScale }
	, m_pInhale{ nullptr }
	, m_pPowerInhale{ nullptr }
	, m_eCurState{ PLAYER_STATE::IDLE }
	, m_ePrevState{ PLAYER_STATE::WALK }
	, m_fInhaleTime{ 0.f }
	, m_fPowerInhaleTime{ 0.f }
	, m_fJumpPower{ -300.f }
	, m_fFloatJumpPower{ -150.f }
	, m_fWalkSpeed{ 120.f }
	, m_fFloatMoveSpeed{ 60.f }

{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2{ 0.f, 0.f });
	GetCollider()->SetScale(Vec2{ TILE_SIZE, TILE_SIZE });

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
	GameTexture* pFloatStartRightTex = GameResMgr::GetInst()->LoadTexture(L"FloatStartRight", L"texture\\Kirby_Float_Start_Right.bmp");
	GameTexture* pFloatStartLeftTex = GameResMgr::GetInst()->LoadTexture(L"FloatStartLeft", L"texture\\Kirby_Float_Start_Left.bmp");
	GameTexture* pFloatIdleRightTex = GameResMgr::GetInst()->LoadTexture(L"FloatIdleRight", L"texture\\Kirby_Float_Idle_Right.bmp");
	GameTexture* pFloatIdleLeftTex = GameResMgr::GetInst()->LoadTexture(L"FloatIdleLeft", L"texture\\Kirby_Float_Idle_Left.bmp");

	GameTexture* pInhaleLeftTex = GameResMgr::GetInst()->LoadTexture(L"InhaleLeft", L"texture\\Kirby_Inhale_Left.bmp");
	GameTexture* pInhaleRightTex = GameResMgr::GetInst()->LoadTexture(L"InhaleRight", L"texture\\Kirby_Inhale_Right.bmp");
	GameTexture* pPowerInhaleLeftTex = GameResMgr::GetInst()->LoadTexture(L"PowerInhaleLeft", L"texture\\Kirby_Power_Inhale_Left.bmp");
	GameTexture* pPowerInhaleRightTex = GameResMgr::GetInst()->LoadTexture(L"PowerInhaleRight", L"texture\\Kirby_Power_Inhale_Right.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pIdleRightTex, 0.07f);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pIdleLeftTex, 0.07f);

	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pWalkRightTex, 0.07f);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pWalkLeftTex, 0.07f);

	GetAnimator()->CreateAnimation(L"RUN_RIGHT", pRunRightTex, 0.07f);
	GetAnimator()->CreateAnimation(L"RUN_LEFT", pRunLeftTex, 0.07f);
	GetAnimator()->CreateAnimation(L"STOP_RIGHT", pStopRightTex, 0.07f);
	GetAnimator()->CreateAnimation(L"STOP_LEFT", pStopLeftTex, 0.07f);

	GetAnimator()->CreateAnimation(L"JUMP_RIGHT", pJumpRightTex, 0.07f);
	GetAnimator()->CreateAnimation(L"JUMP_LEFT", pJumpLeftTex, 0.07f);
	GetAnimator()->CreateAnimation(L"DROP_RIGHT", pDropRightTex, 0.03f);
	GetAnimator()->CreateAnimation(L"DROP_LEFT", pDropLeftTex, 0.03f);

	GetAnimator()->CreateAnimation(L"FLOAT_START_RIGHT", pFloatStartRightTex, 0.03f);
	GetAnimator()->CreateAnimation(L"FLOAT_START_LEFT", pFloatStartLeftTex, 0.03f);
	GetAnimator()->CreateAnimation(L"FLOAT_IDLE_RIGHT", pFloatIdleRightTex, 0.1f);
	GetAnimator()->CreateAnimation(L"FLOAT_IDLE_LEFT", pFloatIdleLeftTex, 0.1f);
	GetAnimator()->CreateAnimation(L"FLOAT_END_RIGHT", pFloatStartRightTex, 0.03f);
	GetAnimator()->CreateAnimation(L"FLOAT_END_LEFT", pFloatStartLeftTex, 0.03f);

	GetAnimator()->CreateAnimation(L"INHALE_RIGHT", pInhaleRightTex, 0.03f);
	GetAnimator()->CreateAnimation(L"INHALE_LEFT", pInhaleLeftTex, 0.03f);
	GetAnimator()->CreateAnimation(L"POWER_INHALE_RIGHT", pPowerInhaleRightTex, 0.03f);
	GetAnimator()->CreateAnimation(L"POWER_INHALE_LEFT", pPowerInhaleLeftTex, 0.03f);

	// GetAnimator()->LoadAnimation(L"animation\\walk_down.anim");
	// GetAnimator()->FindAnimation(L"WALK_DOWN")->Save(L"animation\\walk_down.anim");

	CreateGravity();
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::Update()
{
	UpdateDir();
	UpdateState();
	UpdateMove();
	UpdateAnimation();

	if (GetPos().y >= (float)GameCore::GetInst()->GetResolution().y / 2 || GetPos().x >= (float)GameCore::GetInst()->GetResolution().x / 2)
	{
		GameCamera::GetInst()->SetTargetObj(this);
	}

	m_ePrevState = m_eCurState;
	SetPrevDir(GetObjDir());
}

void GamePlayer::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void GamePlayer::CreateAttack()
{
	m_pInhale = new GameAttack{ L"Inhale", Vec2{ GetPos().x + TILE_SIZE * GetObjDir(), GetPos().y }, Vec2{ TILE_SIZE, TILE_SIZE } };
	m_pInhale->CreateCollider();
	m_pInhale->GetCollider()->SetOffsetPos(Vec2{ 0.f, 0.f });
	m_pInhale->GetCollider()->SetScale(Vec2{ TILE_SIZE, TILE_SIZE });
	m_pInhale->m_pOwner = this;
	m_pInhale->m_vOffset = Vec2{ GetScale().x / 2.f + (m_pInhale->GetScale().x / 2.f), 0.f };
	GetObjScene()->AddObject(m_pInhale, GROUP_TYPE::ATTACK);

	m_pPowerInhale = new GameAttack{ L"Power_Inhale", Vec2{ GetPos().x + TILE_SIZE * 2 * GetObjDir(), GetPos().y }, Vec2{ TILE_SIZE * 2, TILE_SIZE * 2 } };
	m_pPowerInhale->CreateCollider();
	m_pPowerInhale->GetCollider()->SetOffsetPos(Vec2{ 0.f, 0.f });
	m_pPowerInhale->GetCollider()->SetScale(Vec2{ TILE_SIZE * 2, TILE_SIZE * 2 });
	m_pPowerInhale->m_pOwner = this;
	m_pPowerInhale->m_vOffset = Vec2{ GetScale().x / 2.f + (m_pPowerInhale->GetScale().x / 2.f), 0.f };
	GetObjScene()->AddObject(m_pPowerInhale, GROUP_TYPE::ATTACK);

	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ATTACK, GROUP_TYPE::MONSTER);
}

void GamePlayer::UpdateDir()
{
	if (KEY_TAP(KEY::LEFT))
	{
		SetObjDir(-1);
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		SetObjDir(1);
	}

	if (KEY_TAP(KEY::LEFT) && KEY_HOLD(KEY::RIGHT))
	{
		SetObjDir(-1);
	}

	if (KEY_TAP(KEY::RIGHT) && KEY_HOLD(KEY::LEFT))
	{
		SetObjDir(1);
	}

	if (KEY_AWAY(KEY::LEFT) && KEY_HOLD(KEY::RIGHT))
	{
		SetObjDir(1);
	}

	if (KEY_AWAY(KEY::RIGHT) && KEY_HOLD(KEY::LEFT))
	{
		SetObjDir(-1);
	}
}

void GamePlayer::UpdateState()
{
	if (m_eCurState == PLAYER_STATE::IDLE)
	{
		if (KEY_TAP(KEY::D))
		{
			m_eCurState = PLAYER_STATE::JUMP;
			GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, m_fJumpPower });
		}

		if (KEY_TAP(KEY::S))
		{
			m_eCurState = PLAYER_STATE::INHALE;
		}

		if (IS_KIRBY_MOVING)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}

		if (IS_KIRBY_FALLING)
		{
			m_eCurState = PLAYER_STATE::DROP;
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::WALK_READY)
	{
		if (IS_KIRBY_IDLING)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}

		if (IS_KIRBY_MOVING)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}

		if (KEY_TAP(KEY::S))
		{
			m_eCurState = PLAYER_STATE::INHALE;
		}

		if (KEY_TAP(KEY::D))
		{
			m_eCurState = PLAYER_STATE::JUMP;
			GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, m_fJumpPower });
		}

		if (IS_KIRBY_FALLING)
		{
			m_eCurState = PLAYER_STATE::DROP;
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::WALK)
	{
		if (KEY_AWAY(KEY::LEFT) || KEY_AWAY(KEY::RIGHT))
		{
			m_eCurState = PLAYER_STATE::WALK_READY;
		}

		if (KEY_TAP(KEY::S))
		{
			m_eCurState = PLAYER_STATE::INHALE;
		}

		if (KEY_TAP(KEY::D))
		{
			m_eCurState = PLAYER_STATE::JUMP;
			GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, m_fJumpPower });
		}

		if (IS_KIRBY_FALLING)
		{
			m_eCurState = PLAYER_STATE::DROP;
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::INHALE)
	{
		m_fInhaleTime += fDT;

		if (m_fInhaleTime > 0.5f)
		{
			m_eCurState = PLAYER_STATE::IDLE;

			if (IS_KIRBY_MOVING)
			{
				m_eCurState = PLAYER_STATE::WALK;
			}

			if (KEY_HOLD(KEY::S))
			{
				m_eCurState = PLAYER_STATE::POWER_INHALE;
			}

			if (KEY_TAP(KEY::D))
			{
				m_eCurState = PLAYER_STATE::JUMP;
				GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, m_fJumpPower });
			}

			m_fInhaleTime = 0.f;
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::POWER_INHALE)
	{
		m_fPowerInhaleTime += fDT;

		if (m_fPowerInhaleTime > 1.5f)
		{
			m_eCurState = PLAYER_STATE::IDLE;

			if (IS_KIRBY_MOVING)
			{
				m_eCurState = PLAYER_STATE::WALK;
			}

			if (KEY_TAP(KEY::D))
			{
				m_eCurState = PLAYER_STATE::JUMP;
				GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, m_fJumpPower });
			}

			m_fPowerInhaleTime = 0.f;
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::JUMP)
	{
		if (KEY_TAP(KEY::S))
		{
			m_eCurState = PLAYER_STATE::INHALE;
		}

		if (KEY_TAP(KEY::D))
		{
			m_eCurState = PLAYER_STATE::FLOAT_START;
			GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, m_fFloatJumpPower });
		}

		if (IS_KIRBY_FALLING)
		{
			m_eCurState = PLAYER_STATE::DROP;
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::FLOAT_START)
	{
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			m_eCurState = PLAYER_STATE::FLOAT_IDLE;
		}

		if (KEY_TAP(KEY::S))
		{
			m_eCurState = PLAYER_STATE::INHALE;
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::FLOAT_IDLE)
	{
		if (KEY_TAP(KEY::S))
		{
			m_eCurState = PLAYER_STATE::FLOAT_END;
		}

		if (KEY_TAP(KEY::D))
		{
			GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, m_fFloatJumpPower });
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::FLOAT_END)
	{
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			m_eCurState = PLAYER_STATE::DROP;

			if (IS_KIRBY_IDLING)
			{
				m_eCurState = PLAYER_STATE::IDLE;
			}

			if (GetTouchBottom() && (GetRigidBody()->GetVelocity().x != 0.f))
			{
				m_eCurState = PLAYER_STATE::WALK_READY;
			}

			if (IS_KIRBY_MOVING)
			{
				m_eCurState = PLAYER_STATE::WALK;
			}
		}

		if (KEY_TAP(KEY::S))
		{
			m_eCurState = PLAYER_STATE::INHALE;
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::DROP)
	{
		if (IS_KIRBY_IDLING)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}

		if (GetTouchBottom() && (GetRigidBody()->GetVelocity().x != 0.f))
		{
			m_eCurState = PLAYER_STATE::WALK_READY;
		}

		if (IS_KIRBY_MOVING)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}

		if (KEY_TAP(KEY::S))
		{
			m_eCurState = PLAYER_STATE::INHALE;
		}

		if (KEY_TAP(KEY::D))
		{
			m_eCurState = PLAYER_STATE::FLOAT_START;
			GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, m_fFloatJumpPower });
		}

		return;
	}
}

void GamePlayer::UpdateMove()
{
	GameRigidBody* pRigid = GetRigidBody();

	if (m_eCurState == PLAYER_STATE::WALK)
	{
		pRigid->AddForce(Vec2{ m_fWalkSpeed * (float)GetObjDir(), 0.f});
	}

	if (m_eCurState == PLAYER_STATE::JUMP || m_eCurState == PLAYER_STATE::DROP)
	{
		if (KEY_HOLD(KEY::LEFT) || KEY_HOLD(KEY::RIGHT))
		{
			pRigid->AddForce(Vec2{ m_fWalkSpeed * (float)GetObjDir(), 0.f });
		}
	}

	if (m_eCurState == PLAYER_STATE::FLOAT_START || m_eCurState == PLAYER_STATE::FLOAT_IDLE || m_eCurState == PLAYER_STATE::FLOAT_END)
	{
		if (KEY_HOLD(KEY::LEFT) || KEY_HOLD(KEY::RIGHT))
		{
			pRigid->AddForce(Vec2{ m_fFloatMoveSpeed * (float)GetObjDir(), 0.f });
		}
	}
}

void GamePlayer::UpdateAnimation()
{
	if (m_ePrevState == m_eCurState && GetPrevDir() == GetObjDir())
		return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"IDLE_LEFT", true);
		else
			GetAnimator()->Play(L"IDLE_RIGHT", true);
	}
	break;
	case PLAYER_STATE::WALK_READY:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"WALK_LEFT", true);
		else
			GetAnimator()->Play(L"WALK_RIGHT", true);
	}
	break;
	case PLAYER_STATE::WALK:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"WALK_LEFT", true);
		else
			GetAnimator()->Play(L"WALK_RIGHT", true);
	}
	break;
	case PLAYER_STATE::RUN_READY:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"WALK_LEFT", true);
		else
			GetAnimator()->Play(L"WALK_RIGHT", true);
	}
	break;
	case PLAYER_STATE::RUN:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"RUN_LEFT", true);
		else
			GetAnimator()->Play(L"RUN_RIGHT", true);
	}
	break;
	case PLAYER_STATE::JUMP:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"JUMP_LEFT", true);
		else
			GetAnimator()->Play(L"JUMP_RIGHT", true);
	}
	break;
	case PLAYER_STATE::FLOAT_START:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"FLOAT_START_LEFT", false);
		else
			GetAnimator()->Play(L"FLOAT_START_RIGHT", false);
	}
	break;
	case PLAYER_STATE::FLOAT_IDLE:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"FLOAT_IDLE_LEFT", true);
		else
			GetAnimator()->Play(L"FLOAT_IDLE_RIGHT", true);
	}
	break;
	case PLAYER_STATE::FLOAT_END:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"FLOAT_END_LEFT", false);
		else
			GetAnimator()->Play(L"FLOAT_END_RIGHT", false);
	}
	break;
	case PLAYER_STATE::DROP:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"DROP_LEFT", false);
		else
			GetAnimator()->Play(L"DROP_RIGHT", false);
	}
	break;
	case PLAYER_STATE::INHALE:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"INHALE_LEFT", true);
		else
			GetAnimator()->Play(L"INHALE_RIGHT", true);
	}
	break;
	case PLAYER_STATE::POWER_INHALE:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"POWER_INHALE_LEFT", true);
		else
			GetAnimator()->Play(L"POWER_INHALE_RIGHT", true);
	}
	break;
	}
}