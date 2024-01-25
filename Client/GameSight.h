#pragma once
#include "GameObject.h"

class GameSight :
    public GameObject
{
private:
    Vec2 m_vOffsetPos;
    GameObject* m_pOwner;

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    void SetOffsetPos(Vec2 _v)
    {
        m_vOffsetPos = _v;
    }

    GameSight(wstring _strName, Vec2 _vPos, Vec2 _vScale);
    virtual ~GameSight();

    friend class GameObject;
};