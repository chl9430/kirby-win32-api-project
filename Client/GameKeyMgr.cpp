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
	'E',
	'W',
	'A',
	'S',
	'D',
	VK_LSHIFT,
	VK_SPACE,
	'J',
	'L',
	'I',
	'K',
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

	if (hWnd != nullptr) // �� ���� â�� ��Ŀ�� ���̶��
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) // Ű�� ������ ��
			{
				if (m_vecKey[i].bPrevPush) // ���� �����ӿ����� �����ٸ�
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else // ���� �����ӿ��� �ȴ��ȴٸ�
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}
			else // Ű�� �ȴ����� ��
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

		// Mouse ��ġ ���
		POINT ptPos = {};
		GetCursorPos(&ptPos); // ��ũ�� ���� ���콺 ��ǥ
		ScreenToClient(GameCore::GetInst()->GetMainHwnd(), &ptPos); // ���� â ���� ���콺 ��ǥ�� ��ȯ

		m_vCurMousePos = ptPos;
	}
	else // �� ���� â�� ��Ŀ�� ���� �ƴ϶��
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;

			if (m_vecKey[i].eState == KEY_STATE::TAP || m_vecKey[i].eState == KEY_STATE::HOLD)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY; // Ű ���¿� ���� �̺�Ʈ �߻��� �ڿ������� �������ǵ��� �ϱ� ����
			}
			else if (m_vecKey[i].eState == KEY_STATE::AWAY)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}