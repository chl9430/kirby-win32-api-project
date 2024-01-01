#include "pch.h"
#include "GameKeyMgr.h"

#include "GameCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q',
	'W',
	'E',
	'A',
	'S',
	'D',
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_LBUTTON,
	// LAST
};

GameKeyMgr::GameKeyMgr()
	: m_vecKey{}
	, m_vCurMousePos{}
{
}

GameKeyMgr::~GameKeyMgr()
{
}

void GameKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void GameKeyMgr::Update()
{
	HWND hWnd = GetFocus();

	if (hWnd != nullptr) // 내 게임 창이 포커싱 중이라면
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) // 키를 눌렀을 때
			{
				if (m_vecKey[i].bPrevPush) // 예전 프레임에서도 눌렀다면
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else // 예전 프레임에서 안눌렸다면
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}
			else // 키를 안눌렀을 때
			{
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}

		// Mouse 위치 계산
		POINT ptPos = {};
		GetCursorPos(&ptPos); // 스크린 기준 마우스 좌표
		ScreenToClient(GameCore::GetInst()->GetMainHwnd(), &ptPos); // 게임 창 기준 마우스 좌표로 변환

		m_vCurMousePos = ptPos;
	}
	else // 내 게임 창이 포커싱 중이 아니라면
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;

			if (m_vecKey[i].eState == KEY_STATE::TAP || m_vecKey[i].eState == KEY_STATE::HOLD)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY; // 키 상태에 따른 이벤트 발생을 자연스럽게 마무리되도록 하기 위해
			}
			else if (m_vecKey[i].eState == KEY_STATE::AWAY)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}