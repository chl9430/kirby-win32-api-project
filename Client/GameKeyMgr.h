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
	KEY_STATE eState; // 키의 상태값
	bool bPrevPush; // 이전 프레임에서 눌렸는지 여부
};

class GameKeyMgr
{
	SINGLE(GameKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;

public:
	void Init();
};