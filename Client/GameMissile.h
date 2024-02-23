#pragma once
#include "GameObject.h"

class GameMissile :
    public GameObject
{
private:
    GameObject* m_pOwner;

    float m_fMissileSpeed;

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    void FollowOwner();

    void SetOwner(GameObject* _pOwner)
    {
        m_pOwner = _pOwner;
    }

    virtual void OnCollisionEnter(GameCollider* _pOther);
    virtual void OnCollision(GameCollider* _pOther);
    virtual void OnCollisionExit(GameCollider* _pOther);

    GameMissile(wstring _strName, Vec2 _vPos, Vec2 _vScale);
    ~GameMissile();
};