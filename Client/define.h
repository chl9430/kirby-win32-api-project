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

#define KEY_CHECK(key, state) GameKeyMgr::GetInst()->GetKeyState(key) == state

#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)

enum class SCENE_TYPE
{
	TITLE,
	/*SELECT_STAGE,
	STAGE_01,*/
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