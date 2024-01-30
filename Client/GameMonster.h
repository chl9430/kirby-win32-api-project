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
	AI* m_pAI;

	wstring m_strWalkRightAnimKey;
	wstring m_strWalkLeftAnimKey;
	wstring m_strDrawnRightAnimKey;
	wstring m_strDrawnLeftAnimKey;

	GameObject* m_pInhale;
	GameObject* m_pPowerInhale;

	void SetMonInfo(const tMonInfo& _info)
	{
		m_tInfo = _info;
	}

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	void UpdateAnimation();

	void SetAI(AI* _pAI);
	tMonInfo& GetMonInfo()
	{
		return m_tInfo;
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

	virtual void OnCollisionEnter(GameCollider* _pOther);
	virtual void OnCollisionExit(GameCollider* _pOther);

	GameMonster(wstring _strName, Vec2 _vPos, Vec2 _vScale);
	~GameMonster();

	friend class GameMonsterFactory;
};