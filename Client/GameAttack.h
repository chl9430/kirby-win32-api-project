#pragma once
#include "GameObject.h"

class GameAttack :
	public GameObject
{
private:
	GameObject* m_pOwner;
	Vec2 m_vOffset;

public:
	virtual void Update();

	GameObject* GetOwner()
	{
		return m_pOwner;
	}

	virtual void OnCollisionEnter(GameCollider* _pOther);
	virtual void OnCollision(GameCollider* _pOther);
	virtual void OnCollisionExit(GameCollider* _pOther);

	GameAttack(wstring _strName, Vec2 _vPos, Vec2 _vScale);
	virtual ~GameAttack();

	friend class GamePlayer;
};