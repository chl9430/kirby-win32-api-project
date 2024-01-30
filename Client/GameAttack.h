#pragma once
#include "GameObject.h"

class GameAttack :
	public GameObject
{
private:
	GameObject* m_pOwner;
	Vec2 m_vOffset;

	vector<GameObject*> m_vecCollisionMonGroup;

public:
	virtual void Update();

	GameObject* GetOwner()
	{
		return m_pOwner;
	}

	GameAttack(wstring _strName, Vec2 _vPos, Vec2 _vScale);
	virtual ~GameAttack();

	friend class GamePlayer;
};