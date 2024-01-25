#pragma once
#include "GameState.h"

class GameFloatIdleState :
    public GameState
{
private:
    Vec2 m_vInitialPos;
    float m_vfFloatRange;
    int m_iCurDir;

public:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

    void SetFloatingRange(float _fRange)
    {
        m_vfFloatRange = _fRange;
    }

    GameFloatIdleState(Vec2 _vPos);
    ~GameFloatIdleState();
};