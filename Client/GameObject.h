#pragma once

class GameSight;
class GameTexture;
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
	int m_iDir; // 방향정보

	GameSight* m_pLeftSight;
	GameSight* m_pRightSight;
	GameTexture* m_pCurTexture;
	GameCollider* m_pCollider;
	GameRigidBody* m_pRigidBody;
	GameAnimator* m_pAnimator;
	GameGravity* m_pGravity;

	bool m_isTouchBottom;
	bool m_isTouchLeft;
	bool m_isTouchRight;
	bool m_isTouchTop;

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

	void CreateSight();
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
	Vec2 GetScale()
	{
		return m_vScale;
	}
	bool IsDead()
	{
		return !m_bAlive;
	}
	void SetObjDir(int _iDir)
	{
		m_iDir = _iDir;
	}
	int GetObjDir()
	{
		return m_iDir;
	}
	Vec2 GetPos()
	{
		return m_vPos;
	}
	void SetPos(Vec2 _vPos)
	{
		m_vPos = _vPos;
	}
	GameSight* GetObjLeftSight()
	{
		return m_pLeftSight;
	}
	GameSight* GetObjRightSight()
	{
		return m_pRightSight;
	}
	GameTexture* GetCurrentTexture()
	{
		return m_pCurTexture;
	}
	void SetCurrentTexture(GameTexture* _pTexture)
	{
		m_pCurTexture = _pTexture;
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
	GameGravity* GetGravity()
	{
		return m_pGravity;
	}
	void SetTouchBottom(bool _b);
	bool GetTouchBottom()
	{
		return m_isTouchBottom;
	}
	void SetTouchTop(bool _b)
	{
		m_isTouchTop = _b;
	}
	bool GetTouchTop()
	{
		return m_isTouchTop;
	}
	void SetTouchRight(bool _b)
	{
		m_isTouchRight = _b;
	}
	bool GetTouchRight()
	{
		return m_isTouchRight;
	}
	void SetTouchLeft(bool _b)
	{
		m_isTouchLeft = _b;
	}
	bool GetTouchLeft()
	{
		return m_isTouchLeft;
	}

	GameObject(wstring _strName, Vec2 _vPos, Vec2 _vScale);
	virtual ~GameObject();

	friend class GameEventMgr;
};