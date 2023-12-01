#include "pch.h"
#include "GamePlayer.h"

GamePlayer::GamePlayer()
	: m_eCurState{ PLAYER_STATE::IDLE }
	, m_ePrevState{ PLAYER_STATE::WALK  }
	, m_iDir{ 1 }
	, m_iPrevDir{ 1 }
{
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
}

void GamePlayer::UpdateMove()
{
}

void GamePlayer::UpdateAnimation()
{
}
