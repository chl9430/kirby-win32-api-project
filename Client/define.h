#pragma once

// 싱글톤 매크로
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
#define MAX_TILE_COUNT_WIDTH 30
#define MAX_TILE_COUNT_HEIGHT 20

enum class GROUP_TYPE // 번호가 높을 수록 나중에 렌더
{
	DEFAULT,
	BACKGROUND,
	ATTACK,
	GROUND,
	GATE,
	MONSTER,
	PLAYER,
	TILE,
	STAR,
	PROJ_PLAYER,
	PROJ_MONSTER,
	UI,
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
	HOLLOW, // 채우기 색상이 없는 브러쉬 타입
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

enum class MON_TYPE
{
	ICE,
	NORMAL,
	END
};

enum class MON_NAME
{
	WADDLE_DEE,
	SCARFY,
	PENGY
};

enum class MON_STATE
{
	IDLE,
	WALK,
	FLOAT_IDLE,
	DRAWN,
	EATEN,
	LAUNCHED,
	HIT,
	PATROL,
	TRACE,
	ATT,
	RUN,
	DEAD,
	END
};