#pragma once

enum class KEY_STATE
{
	NONE,
	TAP,
	HOLD,
	AWAY
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	E,
	W,
	A,
	S,
	D,
	LSHIFT,
	SPACE,
	LAST
};

struct tKeyInfo
{
	KEY_STATE eState; // Ű�� ���°�
	bool bPrevPush; // ���� �����ӿ��� ���ȴ��� ����
};

class GameKeyMgr
{
	SINGLE(GameKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;
	Vec2 m_vCurMousePos;

public:
	void Init();
	void Update();

	KEY_STATE GetKeyState(KEY _eKey)
	{
		return m_vecKey[(int)_eKey].eState;
	}
};