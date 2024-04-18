#pragma once
#include "GameScene.h"

class GameScene_Title :
	public GameScene
{
private:

public:
	virtual void Enter();
	virtual void Exit();

	GameScene_Title();
	virtual ~GameScene_Title();
};