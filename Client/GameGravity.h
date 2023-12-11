#pragma once

class GameObject;

class GameGravity
{
private:
	GameObject* m_pOwner;

	bool m_bGround;

public:
	void FinalUpdate();

	void SetGround(bool _b);

	GameGravity();
	~GameGravity();

	friend class GameObject;
};