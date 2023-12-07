#pragma once

class GameObject;

class GameRigidBody
{
private:
	GameObject* m_pOwner;

	Vec2 m_vForce;
	Vec2 m_vVelocity;
	Vec2 m_vAccel;
	Vec2 m_vAccelA;
	float m_fMass;
	float m_fFricCoeff;
	Vec2 m_vMaxVelocity;

public:
	void FinalUpdate();
	void Move();

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