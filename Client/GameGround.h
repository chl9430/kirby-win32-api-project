#pragma once
#include "GameObject.h"

class GameTexture;

class GameGround
	: public GameObject
{
private:
	GameTexture* m_pTex;

public:
	virtual void Start();
	virtual void Update();
	virtual void Render(HDC _dc);

	virtual void OnCollisionEnter(GameCollider* _pOther);
	virtual void OnCollision(GameCollider* _pOther);
	virtual void OnCollisionExit(GameCollider* _pOther);

	GameGround();
	~GameGround();
};