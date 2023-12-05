#pragma once

class GameObject;

class GameGravity
{
private:
	GameObject* m_pOwner;

public:

	GameGravity();
	~GameGravity();

	friend class GameObject;
};