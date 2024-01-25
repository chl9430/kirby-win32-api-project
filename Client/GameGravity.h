#pragma once

class GameObject;

class GameGravity
{
private:
	GameObject* m_pOwner;

public:
	void FinalUpdate();

	GameGravity();
	~GameGravity();

	friend class GameObject;
};