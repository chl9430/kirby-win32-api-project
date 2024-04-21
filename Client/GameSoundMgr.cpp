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
		MessageBox(NULL, L"�������̽���������", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// ���� ����̽� �������� ����.
	HWND hWnd = GameCore::GetInst()->GetMainHwnd();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag�� ����
	{
		MessageBox(NULL, L"�������̽� �������� ����", L"SYSTEM ERROR", MB_OK);
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