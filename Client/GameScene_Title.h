#pragma once
#include "GameScene.h"

class GameScene_Title :
	public GameScene
{
private:

public:
	virtual void Enter();
	virtual void Exit();

	void StartBtnChangeScene()
	{
		tEvent tEve = {};
		tEve.eEven = EVENT_TYPE::SCENE_CHANGE;
		tEve.lParam = (DWORD_PTR)SCENE_TYPE::STAGE_01;

		GameEventMgr::GetInst()->AddEvent(tEve);
	};

	void ToolBtnChangeScene()
	{
		tEvent tEve = {};
		tEve.eEven = EVENT_TYPE::SCENE_CHANGE;
		tEve.lParam = (DWORD_PTR)SCENE_TYPE::TOOL;

		GameEventMgr::GetInst()->AddEvent(tEve);
	};

	GameScene_Title();
	virtual ~GameScene_Title();
};