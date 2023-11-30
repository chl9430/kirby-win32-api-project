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