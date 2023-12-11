#pragma once
#include "GameObject.h"

class GameGround
	: public GameObject
{
private:
	virtual void Start();
	virtual void Update();

public:
	virtual void OnCollisionEnter(GameCollider* _pOther);
	virtual void OnCollision(GameCollider* _pOther);
	virtual void OnCollisionExit(GameCollider* _pOther);

	GameGround();
	~GameGround();
};