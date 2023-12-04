#pragma once

class GameObject;

class GameRigidBody
{
private:
	GameObject* m_pOwner;

	Vec2 m_vForce;
	Vec2 m_vVelocity;

public:
	void AddForce(Vec2 _vF)
	{
		m_vForce += _vF;
	}

	Vec2 GetVelocity()
	{
		return m_vVelocity;
	}

	void SetVelocity(Vec2 _v)
	{
		m_vVelocity = _v;
	}

	float GetSpeed()
	{
		return m_vVelocity.Length();
	}

	GameRigidBody();
	~GameRigidBody();

	friend class GameObject;
};