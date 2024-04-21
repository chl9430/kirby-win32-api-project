#include "pch.h"
#include "GameSoundMgr.h"

#include "GameCore.h"

#include "GameSound.h"

GameSoundMgr::GameSoundMgr()
	: m_pSound(nullptr)
	, m_pBGM(nullptr)
{
}

GameSoundMgr::~GameSoundMgr()
{
}

int GameSoundMgr::init(void)
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"사운드디바이스생성실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// 사운드 디바이스 협조레벨 설정.
	HWND hWnd = GameCore::GetInst()->GetMainHwnd();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag값 정리
	{
		MessageBox(NULL, L"사운드디바이스 협조레벨 설정", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void GameSoundMgr::RegisterToBGM(GameSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}