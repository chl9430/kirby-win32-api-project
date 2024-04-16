#include "pch.h"
#include "GamePlayer.h"

#include "GameCore.h"

#include "GameKeyMgr.h"
#include "GameResMgr.h"
#include "GameTimeMgr.h"
#include "GameCamera.h"
#include "GameCollisionMgr.h"
#include "GameEventMgr.h"

#include "GameTexture.h"

#include "GameScene.h"

#include "GameAttack.h"
#include "GameMissile.h"
#include "GameMonster.h"

#include "GameAnimator.h"
#include "GameAnimation.h"
#include "GameRigidBody.h"
#include "GameCollider.h"
#include "GameGravity.h"

#include "AI.h"
#include "GameState.h"
#include "GameDrawnState.h"

#define IS_KIRBY_WALKING GetTouchBottom() && (KEY_HOLD(KEY::LEFT) || KEY_HOLD(KEY::RIGHT))
#define IS_KIRBY_WALK_READYING GetTouchBottom() && (GetRigidBody()->GetVelocity().x != 0.f)
#define IS_KIRBY_FALLING !GetTouchBottom() && (GetRigidBody()->GetVelocity().y > 0.f)
#define IS_KIRBY_IDLING GetTouchBottom() && (GetRigidBody()->GetVelocity().x == 0.f)

GamePlayer::GamePlayer(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject{ _strName, _vPos, _vScale }
	, m_eCurState{ PLAYER_STATE::IDLE }
	, m_ePrevState{ PLAYER_STATE::WALK }
	, m_fInhaleTime{ 0.f }
	, m_fPowerInhaleTime{ 0.f }
	, m_fJumpPower{ -300.f }
	, m_fFloatJumpPower{ -150.f }
	, m_fWalkSpeed{ 120.f }
	, m_fFloatMoveSpeed{ 60.f }
	, m_vecInhaleRangeMon{}
	, m_vecPowerInhaleRangeMon{}
	, m_eEatenMon{ MON_TYPE::END }
	, m_pStarMissile{ nullptr }
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

	GameTexture* pInhaleLeftTex = GameResMgr::GetInst()->LoadTexture(L"InhaleLeft", L"texture\\Kirby_Inhale_Left.bmp");
	GameTexture* pInhaleRightTex = GameResMgr::GetInst()->LoadTexture(L"InhaleRight", L"texture\\Kirby_Inhale_Right.bmp");
	GameTexture* pPowerInhaleLeftTex = GameResMgr::GetInst()->LoadTexture(L"PowerInhaleLeft", L"texture\\Kirby_Power_Inhale_Left.bmp");
	GameTexture* pPowerInhaleRightTex = GameResMgr::GetInst()->LoadTexture(L"PowerInhaleRight", L"texture\\Kirby_Power_Inhale_Right.bmp");

	GameTexture* pKeepStartRightTex = GameResMgr::GetInst()->LoadTexture(L"KeepStartRight", L"texture\\Kirby_Keep_Start_Right.bmp");
	GameTexture* pKeepStartLeftTex = GameResMgr::GetInst()->LoadTexture(L"KeepStartLeft", L"texture\\Kirby_Keep_Start_Left.bmp");

	GameTexture* pKeepIdleRightTex = GameResMgr::GetInst()->LoadTexture(L"KeepIdleRight", L"texture\\Kirby_Keep_Idle_Right.bmp");
	GameTexture* pKeepIdleLeftTex = GameResMgr::GetInst()->LoadTexture(L"KeepIdleLeft", L"texture\\Kirby_Keep_Idle_Left.bmp");
	GameTexture* pKeepWalkRightTex = GameResMgr::GetInst()->LoadTexture(L"KeepWalkRight", L"texture\\Kirby_Keep_Walk_Right.bmp");
	GameTexture* pKeepWalkLeftTex = GameResMgr::GetInst()->LoadTexture(L"KeepWalkLeft", L"texture\\Kirby_Keep_Walk_Left.bmp");

	GameTexture* pKeepJumpRightTex = GameResMgr::GetInst()->LoadTexture(L"KeepJumpRight", L"texture\\Kirby_Keep_Jump_Right.bmp");
	GameTexture* pKeepJumpLeftTex = GameResMgr::GetInst()->LoadTexture(L"KeepJumpLeft", L"texture\\Kirby_Keep_Jump_Left.bmp");

	GameTexture* pKeepDropStartRightTex = GameResMgr::GetInst()->LoadTexture(L"KeepDropStartRight", L"texture\\Kirby_Keep_Drop_Start_Right.bmp");
	GameTexture* pKeepDropStartLeftTex = GameResMgr::GetInst()->LoadTexture(L"KeepDropStartLeft", L"texture\\Kirby_Keep_Drop_Start_Left.bmp");

	GameTexture* pKeepDropRightTex = GameResMgr::GetInst()->LoadTexture(L"KeepDropRight", L"texture\\Kirby_Keep_Drop_Right.bmp");
	GameTexture* pKeepDropLeftTex = GameResMgr::GetInst()->LoadTexture(L"KeepDropLeft", L"texture\\Kirby_Keep_Drop_Left.bmp");

	GameTexture* pKeepHitRightTex = GameResMgr::GetInst()->LoadTexture(L"KeepHitRight", L"texture\\Kirby_Keep_Hit_Right.bmp");
	GameTexture* pKeepHitLeftTex = GameResMgr::GetInst()->LoadTexture(L"KeepHitLeft", L"texture\\Kirby_Keep_Hit_Left.bmp");

	GameTexture* pExhaleRightTex = GameResMgr::GetInst()->LoadTexture(L"ExhaleRight", L"texture\\Kirby_Exhale_Right.bmp");
	GameTexture* pExhaleLeftTex = GameResMgr::GetInst()->LoadTexture(L"ExhaleLeft", L"texture\\Kirby_Exhale_Left.bmp");

	GameTexture* pSwallowRightTex = GameResMgr::GetInst()->LoadTexture(L"SwallowRight", L"texture\\Kirby_Swallow_Right.bmp");
	GameTexture* pSwallowLeftTex = GameResMgr::GetInst()->LoadTexture(L"SwallowLeft", L"texture\\Kirby_Swallow_Left.bmp");

	GameTexture* pHitRightTex = GameResMgr::GetInst()->LoadTexture(L"HitRight", L"texture\\Kirby_Hit_Right.bmp");
	GameTexture* pHitLeftTex = GameResMgr::GetInst()->LoadTexture(L"HitLeft", L"texture\\Kirby_Hit_Left.bmp");

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

	GetAnimator()->CreateAnimation(L"KEEP_START_RIGHT", pKeepStartRightTex, 0.03f);
	GetAnimator()->CreateAnimation(L"KEEP_START_LEFT", pKeepStartLeftTex, 0.03f);
	GetAnimator()->CreateAnimation(L"KEEP_IDLE_RIGHT", pKeepIdleRightTex, 0.03f);
	GetAnimator()->CreateAnimation(L"KEEP_IDLE_LEFT", pKeepIdleLeftTex, 0.03f);

	GetAnimator()->CreateAnimation(L"KEEP_WALK_RIGHT", pKeepWalkRightTex, 0.05f);
	GetAnimator()->CreateAnimation(L"KEEP_WALK_LEFT", pKeepWalkLeftTex, 0.05f);

	GetAnimator()->CreateAnimation(L"KEEP_JUMP_RIGHT", pKeepJumpRightTex, 0.05f);
	GetAnimator()->CreateAnimation(L"KEEP_JUMP_LEFT", pKeepJumpLeftTex, 0.05f);

	GetAnimator()->CreateAnimation(L"KEEP_DROP_START_RIGHT", pKeepDropStartRightTex, 0.05f);
	GetAnimator()->CreateAnimation(L"KEEP_DROP_START_LEFT", pKeepDropStartLeftTex, 0.05f);

	GetAnimator()->CreateAnimation(L"KEEP_DROP_RIGHT", pKeepDropRightTex, 0.05f);
	GetAnimator()->CreateAnimation(L"KEEP_DROP_LEFT", pKeepDropLeftTex, 0.05f);

	GetAnimator()->CreateAnimation(L"KEEP_HIT_RIGHT", pKeepHitRightTex, 0.07f);
	GetAnimator()->CreateAnimation(L"KEEP_HIT_LEFT", pKeepHitLeftTex, 0.07f);

	GetAnimator()->CreateAnimation(L"EXHALE_RIGHT", pExhaleRightTex, 0.03f);
	GetAnimator()->CreateAnimation(L"EXHALE_LEFT", pExhaleLeftTex, 0.03f);

	GetAnimator()->CreateAnimation(L"SWALLOW_RIGHT", pSwallowRightTex, 0.03f);
	GetAnimator()->CreateAnimation(L"SWALLOW_LEFT", pSwallowLeftTex, 0.03f);

	GetAnimator()->CreateAnimation(L"HIT_RIGHT", pHitRightTex, 0.07f);
	GetAnimator()->CreateAnimation(L"HIT_LEFT", pHitLeftTex, 0.07f);

	// GetAnimator()->LoadAnimation(L"animation\\walk_down.anim");
	// GetAnimator()->FindAnimation(L"WALK_DOWN")->Save(L"animation\\walk_down.anim");

	CreateGravity();
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::Update()
{
	CountInvincibleState();

	UpdateDir();
	UpdateState();
	UpdateMove();
	UpdateAnimation();

	if (m_pStarMissile != nullptr)
	{
		m_pStarMissile->FollowOwner();
	}

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

void GamePlayer::CreateInhale()
{
	GameAttack* pInhale = new GameAttack{ L"Inhale", Vec2{ GetPos().x + TILE_SIZE * GetObjDir(), GetPos().y }, Vec2{ TILE_SIZE, TILE_SIZE } };
	pInhale->CreateCollider();
	pInhale->GetCollider()->SetOffsetPos(Vec2{ 0.f, 0.f });
	pInhale->GetCollider()->SetScale(Vec2{ TILE_SIZE, TILE_SIZE });
	pInhale->m_pOwner = this;
	pInhale->m_vOffset = Vec2{ GetScale().x / 2.f + (pInhale->GetScale().x / 2.f), 0.f };
	GetObjScene()->AddObject(pInhale, GROUP_TYPE::ATTACK);

	GameAttack* pPowerInhale = new GameAttack{ L"Power_Inhale", Vec2{ GetPos().x + TILE_SIZE * 2 * GetObjDir(), GetPos().y }, Vec2{ TILE_SIZE * 2, TILE_SIZE * 2 } };
	pPowerInhale->CreateCollider();
	pPowerInhale->GetCollider()->SetOffsetPos(Vec2{ 0.f, 0.f });
	pPowerInhale->GetCollider()->SetScale(Vec2{ TILE_SIZE * 2, TILE_SIZE * 2 });
	pPowerInhale->m_pOwner = this;
	pPowerInhale->m_vOffset = Vec2{ GetScale().x / 2.f + (pPowerInhale->GetScale().x / 2.f), 0.f };
	GetObjScene()->AddObject(pPowerInhale, GROUP_TYPE::ATTACK);

	GameCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ATTACK, GROUP_TYPE::MONSTER);
}

void GamePlayer::UpdateDir()
{
	if (m_eCurState != PLAYER_STATE::HIT && m_eCurState != PLAYER_STATE::KEEP_HIT 
		&& m_eCurState != PLAYER_STATE::INHALE && m_eCurState != PLAYER_STATE::POWER_INHALE)
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
}

void GamePlayer::UpdateState()
{
	if (m_eCurState == PLAYER_STATE::IDLE)
	{
		if (KEY_TAP(KEY::D))
		{
			JumpKirby();
		}

		if (KEY_TAP(KEY::S))
		{
			m_eCurState = PLAYER_STATE::INHALE;
		}

		if (IS_KIRBY_WALKING)
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

		if (IS_KIRBY_WALKING)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}

		if (KEY_TAP(KEY::S))
		{
			m_eCurState = PLAYER_STATE::INHALE;
		}

		if (KEY_TAP(KEY::D))
		{
			JumpKirby();
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
			JumpKirby();
		}

		if (IS_KIRBY_FALLING)
		{
			m_eCurState = PLAYER_STATE::DROP;
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::INHALE)
	{
		InhaleMon();

		m_fInhaleTime += fDT;

		if (m_fInhaleTime > 0.5f && m_vecInhaleRangeMon.empty())
		{
			if (GetAnimator()->GetCurrentAnim()->GetName() == L"INHALE_LEFT") // 방향을 바꿀 수 없었기에 방향을 애니메이션이 끝나면 맞춰줌
			{
				if (KEY_HOLD(KEY::RIGHT))
				{
					SetObjDir(1);
				}
				else if (KEY_HOLD(KEY::LEFT))
				{
					SetObjDir(-1);
				}
			}
			else if (GetAnimator()->GetCurrentAnim()->GetName() == L"INHALE_RIGHT")
			{
				if (KEY_HOLD(KEY::LEFT))
				{
					SetObjDir(-1);
				}
				else if (KEY_HOLD(KEY::RIGHT))
				{
					SetObjDir(1);
				}
			}

			m_eCurState = PLAYER_STATE::IDLE;

			if (IS_KIRBY_WALKING)
			{
				m_eCurState = PLAYER_STATE::WALK;
			}

			if (KEY_HOLD(KEY::S))
			{
				m_eCurState = PLAYER_STATE::POWER_INHALE;
			}

			if (KEY_TAP(KEY::D))
			{
				JumpKirby();
			}

			m_fInhaleTime = 0.f;
		}

		if (m_vecInhaleRangeMon.empty() && m_eEatenMon != MON_TYPE::END)
		{
			m_eCurState = PLAYER_STATE::KEEP_START;
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::POWER_INHALE)
	{
		InhaleMon();

		m_fPowerInhaleTime += fDT;

		if (m_fPowerInhaleTime > 1.5f && m_vecPowerInhaleRangeMon.empty())
		{
			if (GetAnimator()->GetCurrentAnim()->GetName() == L"POWER_INHALE_LEFT") // 방향을 바꿀 수 없었기에 방향을 애니메이션이 끝나면 맞춰줌
			{
				if (KEY_HOLD(KEY::RIGHT))
				{
					SetObjDir(1);
				}
				else if (KEY_HOLD(KEY::LEFT))
				{
					SetObjDir(-1);
				}
			}
			else if (GetAnimator()->GetCurrentAnim()->GetName() == L"POWER_INHALE_RIGHT")
			{
				if (KEY_HOLD(KEY::LEFT))
				{
					SetObjDir(-1);
				}
				else if (KEY_HOLD(KEY::RIGHT))
				{
					SetObjDir(1);
				}
			}

			m_eCurState = PLAYER_STATE::IDLE;

			if (IS_KIRBY_WALKING)
			{
				m_eCurState = PLAYER_STATE::WALK;
			}

			if (KEY_TAP(KEY::D))
			{
				JumpKirby();
			}

			m_fPowerInhaleTime = 0.f;
		}

		if (m_vecInhaleRangeMon.empty() && m_eEatenMon != MON_TYPE::END)
		{
			m_eCurState = PLAYER_STATE::KEEP_START;
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

			if (IS_KIRBY_WALK_READYING)
			{
				m_eCurState = PLAYER_STATE::WALK_READY;
			}

			if (IS_KIRBY_WALKING)
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

		if (IS_KIRBY_WALK_READYING)
		{
			m_eCurState = PLAYER_STATE::WALK_READY;
		}

		if (IS_KIRBY_WALKING)
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

	if (m_eCurState == PLAYER_STATE::KEEP_START)
	{
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			m_eCurState = PLAYER_STATE::KEEP_IDLE;
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::KEEP_IDLE)
	{
		if (KEY_TAP(KEY::D))
		{
			JumpKirby();
		}

		if (KEY_TAP(KEY::S))
		{
			LaunchMon();
		}

		if (IS_KIRBY_WALKING)
		{
			m_eCurState = PLAYER_STATE::KEEP_WALK;
		}

		if (IS_KIRBY_WALK_READYING)
		{
			m_eCurState = PLAYER_STATE::KEEP_WALK_READY;
		}

		if (IS_KIRBY_FALLING)
		{
			m_eCurState = PLAYER_STATE::KEEP_DROP;
		}

		if (KEY_TAP(KEY::DOWN))
		{
			SwallowMon();
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::KEEP_WALK_READY)
	{
		if (IS_KIRBY_IDLING)
		{
			m_eCurState = PLAYER_STATE::KEEP_IDLE;
		}

		if (IS_KIRBY_WALKING)
		{
			m_eCurState = PLAYER_STATE::KEEP_WALK;
		}

		if (KEY_TAP(KEY::S))
		{
			LaunchMon();
		}

		if (KEY_TAP(KEY::D))
		{
			JumpKirby();
		}

		if (IS_KIRBY_FALLING)
		{
			m_eCurState = PLAYER_STATE::KEEP_DROP;
		}

		if (KEY_TAP(KEY::DOWN))
		{
			SwallowMon();
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::KEEP_WALK)
	{
		if (KEY_AWAY(KEY::LEFT) || KEY_AWAY(KEY::RIGHT))
		{
			m_eCurState = PLAYER_STATE::KEEP_WALK_READY;
		}

		if (KEY_TAP(KEY::S))
		{
			LaunchMon();
		}

		if (KEY_TAP(KEY::D))
		{
			JumpKirby();
		}

		if (IS_KIRBY_FALLING)
		{
			m_eCurState = PLAYER_STATE::KEEP_DROP;
		}

		if (KEY_TAP(KEY::DOWN))
		{
			SwallowMon();
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::KEEP_JUMP)
	{
		if (KEY_TAP(KEY::S))
		{
			LaunchMon();
		}

		if (IS_KIRBY_FALLING)
		{
			m_eCurState = PLAYER_STATE::KEEP_DROP_START;
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::KEEP_DROP_START)
	{
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			m_eCurState = PLAYER_STATE::KEEP_DROP;
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::KEEP_DROP)
	{
		if (IS_KIRBY_IDLING)
		{
			m_eCurState = PLAYER_STATE::KEEP_IDLE;
		}

		if (IS_KIRBY_WALK_READYING)
		{
			m_eCurState = PLAYER_STATE::KEEP_WALK_READY;
		}

		if (IS_KIRBY_WALKING)
		{
			m_eCurState = PLAYER_STATE::KEEP_WALK;
		}

		if (KEY_TAP(KEY::S))
		{
			LaunchMon();
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::KEEP_HIT)
	{
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			if (GetAnimator()->GetCurrentAnim()->GetName() == L"KEEP_HIT_LEFT") // 방향을 바꿀 수 없었기에 방향을 애니메이션이 끝나면 맞춰줌
			{
				if (KEY_HOLD(KEY::RIGHT))
				{
					SetObjDir(1);
				}
				else if (KEY_HOLD(KEY::LEFT))
				{
					SetObjDir(-1);
				}
			}
			else if (GetAnimator()->GetCurrentAnim()->GetName() == L"KEEP_HIT_RIGHT")
			{
				if (KEY_HOLD(KEY::LEFT))
				{
					SetObjDir(-1);
				}
				else if (KEY_HOLD(KEY::RIGHT))
				{
					SetObjDir(1);
				}
			}

			if (IS_KIRBY_IDLING)
			{
				m_eCurState = PLAYER_STATE::KEEP_IDLE;
			}

			if (IS_KIRBY_WALKING)
			{
				m_eCurState = PLAYER_STATE::KEEP_WALK;
			}

			if (IS_KIRBY_WALK_READYING)
			{
				m_eCurState = PLAYER_STATE::KEEP_WALK_READY;
			}

			if (IS_KIRBY_FALLING)
			{
				m_eCurState = PLAYER_STATE::KEEP_DROP;
			}
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::EXHALE)
	{
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			if (!GetTouchBottom() && (GetRigidBody()->GetVelocity().y < 0.f))
			{
				m_eCurState = PLAYER_STATE::JUMP;
			}

			if (IS_KIRBY_FALLING)
			{
				m_eCurState = PLAYER_STATE::DROP;
			}

			if (IS_KIRBY_IDLING)
			{
				m_eCurState = PLAYER_STATE::IDLE;
			}

			if (IS_KIRBY_WALKING)
			{
				m_eCurState = PLAYER_STATE::WALK;
			}

			if (IS_KIRBY_WALK_READYING)
			{
				m_eCurState = PLAYER_STATE::WALK_READY;
			}
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::SWALLOW)
	{
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			if (IS_KIRBY_IDLING)
			{
				m_eCurState = PLAYER_STATE::IDLE;
			}

			if (IS_KIRBY_WALKING)
			{
				m_eCurState = PLAYER_STATE::WALK;
			}

			if (IS_KIRBY_WALK_READYING)
			{
				m_eCurState = PLAYER_STATE::WALK_READY;
			}
		}

		return;
	}

	if (m_eCurState == PLAYER_STATE::HIT)
	{
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			if (GetAnimator()->GetCurrentAnim()->GetName() == L"HIT_LEFT") // 방향을 바꿀 수 없었기에 방향을 애니메이션이 끝나면 맞춰줌
			{
				if (KEY_HOLD(KEY::RIGHT))
				{
					SetObjDir(1);
				}
				else if (KEY_HOLD(KEY::LEFT))
				{
					SetObjDir(-1);
				}
			}
			else if (GetAnimator()->GetCurrentAnim()->GetName() == L"HIT_RIGHT")
			{
				if (KEY_HOLD(KEY::LEFT))
				{
					SetObjDir(-1);
				}
				else if (KEY_HOLD(KEY::RIGHT))
				{
					SetObjDir(1);
				}
			}

			if (IS_KIRBY_IDLING)
			{
				m_eCurState = PLAYER_STATE::IDLE;
			}

			if (IS_KIRBY_WALKING)
			{
				m_eCurState = PLAYER_STATE::WALK;
			}

			if (IS_KIRBY_WALK_READYING)
			{
				m_eCurState = PLAYER_STATE::WALK_READY;
			}

			if (IS_KIRBY_FALLING)
			{
				m_eCurState = PLAYER_STATE::DROP;
			}
		}

		return;
	}
}

void GamePlayer::UpdateMove()
{
	GameRigidBody* pRigid = GetRigidBody();

	if (m_eCurState == PLAYER_STATE::WALK || m_eCurState == PLAYER_STATE::KEEP_WALK)
	{
		pRigid->AddForce(Vec2{ m_fWalkSpeed * (float)GetObjDir(), 0.f });
	}

	if (m_eCurState == PLAYER_STATE::JUMP || m_eCurState == PLAYER_STATE::DROP
		|| m_eCurState == PLAYER_STATE::KEEP_JUMP || m_eCurState == PLAYER_STATE::KEEP_DROP_START || m_eCurState == PLAYER_STATE::KEEP_DROP)
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
	case PLAYER_STATE::KEEP_START:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"KEEP_START_LEFT", false);
		else
			GetAnimator()->Play(L"KEEP_START_RIGHT", false);
	}
	break;
	case PLAYER_STATE::KEEP_IDLE:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"KEEP_IDLE_LEFT", true);
		else
			GetAnimator()->Play(L"KEEP_IDLE_RIGHT", true);
	}
	break;
	case PLAYER_STATE::KEEP_WALK_READY:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"KEEP_WALK_LEFT", true);
		else
			GetAnimator()->Play(L"KEEP_WALK_RIGHT", true);
	}
	break;
	case PLAYER_STATE::KEEP_WALK:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"KEEP_WALK_LEFT", true);
		else
			GetAnimator()->Play(L"KEEP_WALK_RIGHT", true);
	}
	break;
	case PLAYER_STATE::KEEP_JUMP:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"KEEP_JUMP_LEFT", true);
		else
			GetAnimator()->Play(L"KEEP_JUMP_RIGHT", true);
	}
	break;
	case PLAYER_STATE::KEEP_DROP_START:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"KEEP_DROP_START_LEFT", false);
		else
			GetAnimator()->Play(L"KEEP_DROP_START_RIGHT", false);
	}
	break;
	case PLAYER_STATE::KEEP_DROP:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"KEEP_DROP_LEFT", false);
		else
			GetAnimator()->Play(L"KEEP_DROP_RIGHT", false);
	}
	break;
	case PLAYER_STATE::EXHALE:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"EXHALE_LEFT", false);
		else
			GetAnimator()->Play(L"EXHALE_RIGHT", false);
	}
	break;
	case PLAYER_STATE::SWALLOW:
	{
		if (GetObjDir() == -1)
			GetAnimator()->Play(L"SWALLOW_LEFT", false);
		else
			GetAnimator()->Play(L"SWALLOW_RIGHT", false);
	}
	break;
	}
}

void GamePlayer::JumpKirby()
{
	if (m_eCurState >= PLAYER_STATE::KEEP_IDLE)
	{
		m_eCurState = PLAYER_STATE::KEEP_JUMP;
	}
	else
	{
		m_eCurState = PLAYER_STATE::JUMP;
	}

	GetRigidBody()->SetVelocity(Vec2{ GetRigidBody()->GetVelocity().x, m_fJumpPower });
}

void GamePlayer::InhaleMon()
{
	if (m_eCurState == PLAYER_STATE::INHALE)
	{
		for (int i = 0; i < m_vecInhaleRangeMon.size(); i++)
		{
			((GameMonster*)m_vecInhaleRangeMon[i])->GetAI()->SetCurState(MON_STATE::DRAWN);
			((GameDrawnState*)((GameMonster*)m_vecInhaleRangeMon[i])->GetAI()->GetCurState())->SetDestPos(GetPos());
		}
	}

	if (m_eCurState == PLAYER_STATE::POWER_INHALE)
	{
		for (int i = 0; i < m_vecPowerInhaleRangeMon.size(); i++)
		{
			((GameMonster*)m_vecPowerInhaleRangeMon[i])->GetAI()->SetCurState(MON_STATE::DRAWN);
			((GameDrawnState*)((GameMonster*)m_vecPowerInhaleRangeMon[i])->GetAI()->GetCurState())->SetDestPos(GetPos());
		}
	}
}

void GamePlayer::SwallowMon()
{
	m_eCurState = PLAYER_STATE::SWALLOW;

	//if () // 커비의 능력 변화
	//{

	//}
	m_eEatenMon = MON_TYPE::END;
}

void GamePlayer::LaunchMon()
{
	m_eCurState = PLAYER_STATE::EXHALE;

	if (m_pStarMissile != nullptr)
	{
		GetObjScene()->AddObject(m_pStarMissile, GROUP_TYPE::STAR);
		m_pStarMissile->SetObjDir(GetObjDir());
	}

	m_pStarMissile = nullptr;
	m_eEatenMon = MON_TYPE::END;
}

void GamePlayer::OnCollisionEnter(GameCollider* _pOther)
{
	
}

void GamePlayer::OnCollision(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetGroupType() == GROUP_TYPE::MONSTER)
	{
		// 몬스터를 먹는 로직
		if ((m_eCurState == PLAYER_STATE::INHALE
			|| m_eCurState == PLAYER_STATE::POWER_INHALE)
			&& ((GameMonster*)pOtherObj)->GetAI()->GetCurState()->GetType() == MON_STATE::DRAWN)
		{
			RemoveInhaleRangeMon(pOtherObj);
			RemovePowerInhaleRangeMon(pOtherObj);

			if (m_eEatenMon != MON_TYPE::END) // 먹은 몬스터가 이미 있을 경우에는 타입 우선순위 확인
			{
				if (((GameMonster*)pOtherObj)->GetMonType() < m_eEatenMon)
				{
					m_eEatenMon = ((GameMonster*)pOtherObj)->GetMonType();
				}
			}
			else
			{
				m_eEatenMon = ((GameMonster*)pOtherObj)->GetMonType();
			}

			pOtherObj->DestroyObj();

			// 별 미사일 생성
			GameTexture* m_pStarTex = GameResMgr::GetInst()->LoadTexture(L"Star", L"texture\\Star.bmp");
			GameTexture* m_pStarDestroyTex = GameResMgr::GetInst()->LoadTexture(L"Star_Destroy", L"texture\\Star_Destroy.bmp");

			m_pStarMissile = new GameMissile{ L"Star", GetPos(), Vec2{ TILE_SIZE, TILE_SIZE } };
			m_pStarMissile->CreateAnimator();
			m_pStarMissile->GetAnimator()->CreateAnimation(L"STAR", m_pStarTex, 0.15f);
			m_pStarMissile->GetAnimator()->CreateAnimation(L"STAR_DESTROY", m_pStarDestroyTex, 0.03f);
			m_pStarMissile->GetAnimator()->Play(L"STAR", true);
			m_pStarMissile->SetOwner(this);

			m_pStarMissile->CreateCollider();
			m_pStarMissile->GetCollider()->SetScale(m_pStarMissile->GetScale());
		}

		// 커비가 맞는 로직
		if (!GetIsInvincible() && (m_eCurState != PLAYER_STATE::INHALE && m_eCurState != PLAYER_STATE::POWER_INHALE))
		{
			// 커비를 무적상태로 변경
			SetIsInvincible(true);

			// 커비가 몬스터와 맞은 위치에 따라 커비를 밀침
			if (pOtherObj->GetPos().x < GetPos().x)
			{
				SetObjDir(-1);
				GetRigidBody()->SetVelocity(Vec2{ 100.f * -GetObjDir(), GetRigidBody()->GetVelocity().y });
			}
			else
			{
				SetObjDir(1);
				GetRigidBody()->SetVelocity(Vec2{ 100.f * -GetObjDir(), GetRigidBody()->GetVelocity().y });
			}

			// 커비가 뭔가 물고 있는 상태에서 맞았다면 (KEEP_START ~ KEEP_HIT : 값 변경 주의)
			if ((int)m_eCurState >= 15 && (int)m_eCurState <= 22)
			{
				m_eCurState = PLAYER_STATE::KEEP_HIT;

				if (GetObjDir() == -1)
					GetAnimator()->Play(L"KEEP_HIT_LEFT", false);
				else
					GetAnimator()->Play(L"KEEP_HIT_RIGHT", false);
			}
			else
			{
				m_eCurState = PLAYER_STATE::HIT;

				if (GetObjDir() == -1)
					GetAnimator()->Play(L"HIT_LEFT", false);
				else
					GetAnimator()->Play(L"HIT_RIGHT", false);
			}
		}
	}
}

void GamePlayer::OnCollisionExit(GameCollider* _pOther)
{
}