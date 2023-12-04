#include "pch.h"
#include "GameAnimator.h"

GameAnimator::GameAnimator()
	: m_pCurAnim{ nullptr }
	, m_bRepeat{ false }
{
}

GameAnimator::~GameAnimator()
{
}

void GameAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}

GameAnimation* GameAnimator::FindAnimation(const wstring& _strName)
{
	return nullptr;
}
