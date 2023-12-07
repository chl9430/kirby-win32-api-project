#pragma once

class GameCollider;
class GameRigidBody;
class GameAnimator;
class GameGravity;

class GameObject
{
private:
	wstring m_strName;
	Vec2 m_vPos;
	Vec2 m_vScale;
	bool m_bAlive;

	GameCollider* m_pCollider;
	GameRigidBody* m_pRigidBody;
	GameAnimator* m_pAnimator;
	GameGravity* m_pGravity;

	void SetDead()
	{
		m_bAlive = false;
	}

public:
	virtual void Start() {};
	virtual void Update() = 0;
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	virtual void OnCollision(GameCollider* _pOther) {}
	virtual void OnCollisionEnter(GameCollider* _pOther) {}
	virtual void OnCollisionExit(GameCollider* _pOther) {}

	void ComponentRender(HDC _dc);

	void CreateCollider();
	void CreateRigidBody();
	void CreateAnimator();
	void CreateGravity();

	void SetName(const wstring& _strName)
	{
		m_strName = _strName;
	}
	const wstring& GetName()
	{
		return m_strName;
	}
	void SetScale(Vec2 _vScale)
	{
		m_vScale = _vScale;
	}
	bool IsDead()
	{
		return !m_bAlive;
	}
	Vec2 GetPos()
	{
		return m_vPos;
	}
	void SetPos(Vec2 _vPos)
	{
		m_vPos = _vPos;
	}
	GameRigidBody* GetRigidBody()
	{
		return m_pRigidBody;
	}
	GameAnimator* GetAnimator()
	{
		return m_pAnimator;
	}
	GameCollider* GetCollider()
	{
		return m_pCollider;
	}

	GameObject();
	virtual ~GameObject();

	friend class GameEventMgr;
};