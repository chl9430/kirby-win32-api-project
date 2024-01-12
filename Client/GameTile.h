#pragma once
#include "GameObject.h"

class GameTexture;

class GameTile :
	public GameObject
{
private:

public:
	virtual void Update();

	virtual void Save(FILE* _pFile);

	virtual void OnCollisionEnter(GameCollider* _pOther);
	virtual void OnCollision(GameCollider* _pOther);
	virtual void OnCollisionExit(GameCollider* _pOther);

	GameTile();
	~GameTile();
};