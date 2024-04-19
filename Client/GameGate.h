#pragma once
#include "GameObject.h"

class GameGate :

    public GameObject
{
private:
    virtual void Update();
    // virtual void Render(HDC _dc);

public:

    GameGate(wstring _strName, Vec2 _vPos, Vec2 _vScale);
    ~GameGate();
};