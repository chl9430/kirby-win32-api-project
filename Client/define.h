#pragma once

// �̱��� ��ũ��
#define SINGLE(type)	public:\
							static type* GetInst()\
							{\
								static type mgr;\
								return &mgr;\
							}\
						private:\
							type();\
							~type();

#define fDT GameTimeMgr::GetInst()->GetfDT()
#define DT GameTimeMgr::GetInst()->GetfDT()

#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)

#define KEY_CHECK(key, state) GameKeyMgr::GetInst()->GetKeyState(key) == state
#define MOUSE_POS GameKeyMgr::GetInst()->GetMousePos()

#define TILE_SIZE 40

enum class GROUP_TYPE // ��ȣ�� ���� ���� ���߿� ����
{
	DEFAULT,
	ATTACK,
	GROUND,
	MONSTER,
	PLAYER,
	TILE,
	PROJ_PLAYER,
	PROJ_MONSTER,
	UI = 31,
	END = 32
};

enum class SCENE_TYPE
{
	TITLE,
	// SELECT_STAGE,
	STAGE_01,
	TOOL,
	END
};

enum class BRUSH_TYPE
{
	HOLLOW, // ä��� ������ ���� �귯�� Ÿ��
	BLACK,
	END
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,
	END
};

enum class MON_STATE
{
	IDLE,
	WALK,
	FLOAT_IDLE,
	DRAWN,
	EATEN,
	LAUNCHED,
	PATROL,
	TRACE,
	ATT,
	RUN,
	DEAD,
	END
};