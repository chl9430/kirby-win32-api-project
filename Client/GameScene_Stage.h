#pragma once
#include "GameScene.h"

class GameScene_Stage :
	public GameScene
{
private:

public:
	virtual void Enter();
	virtual void Exit();

	virtual void LoadTile(const wstring& _strRelativePath);

	GameScene_Stage();
	~GameScene_Stage();
};