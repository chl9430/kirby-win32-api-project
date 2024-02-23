#pragma once
#include "GameObject.h"

class AI;

struct tMonInfo
{
	float fHP;
	float fSpeed;
	float fRecogRange;
	float fAttRange;
	float fAtt;
};

class GameMonster :
	public GameObject
{
private:
	tMonInfo m_tInfo;
	MON_TYPE m_eMonType;
	AI* m_pAI;

	wstring m_strWalkRightAnimKey;
	wstring m_strWalkLeftAnimKey;
	wstring m_strDrawnRightAnimKey;
	wstring m_strDrawnLeftAnimKey;
	wstring m_strHitRightAnimKey;
	wstring m_strHitLeftAnimKey;

	bool m_bIsDestroying;
	float m_fHitTime;
	float m_fHitFinishTime;

	void SetMonInfo(const tMonInfo& _info)
	{
		m_tInfo = _info;
	}

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	void UpdateAnimation();

	void SetAI(AI* _pAI);
	AI* GetAI()
	{
		return m_pAI;
	}
	tMonInfo& GetMonInfo()
	{
		return m_tInfo;
	}
	void SetMonType(MON_TYPE _eType)
	{
		m_eMonType = _eType;
	}
	MON_TYPE GetMonType()
	{
		return m_eMonType;
	}
	void SetWalkAnimationKey(wstring _pRightAnimKey, wstring _pLeftAnimKey)
	{
		m_strWalkRightAnimKey = _pRightAnimKey;
		m_strWalkLeftAnimKey = _pLeftAnimKey;
	}
	void SetDrawnAnimationKey(wstring _pRightAnimKey, wstring _pLeftAnimKey)
	{
		m_strDrawnRightAnimKey = _pRightAnimKey;
		m_strDrawnLeftAnimKey = _pLeftAnimKey;
	}
	void SetHitAnimationKey(wstring _pRightAnimKey, wstring _pLeftAnimKey)
	{
		m_strHitRightAnimKey = _pRightAnimKey;
		m_strHitLeftAnimKey = _pLeftAnimKey;
	}

	virtual void OnCollisionEnter(GameCollider* _pOther);
	virtual void OnCollision(GameCollider* _pOther);
	virtual void OnCollisionExit(GameCollider* _pOther);

	GameMonster(wstring _strName, Vec2 _vPos, Vec2 _vScale);
	~GameMonster();

	friend class GameMonsterFactory;
};