#pragma once
#include "GameScene.h"

class GameSound;

class GameScene_Stage :
	public GameScene
{
private:
	GameSound* m_pBGM;

public:
	virtual void Enter();
	virtual void Exit();

	virtual void LoadTile(const wstring& _strRelativePath);

	GameScene_Stage();
	virtual ~GameScene_Stage();
};