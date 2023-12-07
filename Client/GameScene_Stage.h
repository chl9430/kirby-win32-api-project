#pragma once
#include "GameScene.h"

class GameScene_Stage :
	public GameScene
{
private:

public:
	virtual void Render(HDC _dc);

	virtual void Enter();
	virtual void Exit();

	GameScene_Stage();
	~GameScene_Stage();
};