#pragma once

class GameObject;

class GameCollider
{
private:
	GameObject* m_pOwner;

public:

	GameCollider();
	~GameCollider();

	friend class GameObject;
};