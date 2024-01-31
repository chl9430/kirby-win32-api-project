#pragma once
#include "GameState.h"

class GameDrawnState :
    public GameState
{
private:
    Vec2 m_vDestPos;

public:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

    void SetDestPos(Vec2 _vPos)
    {
        m_vDestPos = _vPos;
    }

    GameDrawnState();
    ~GameDrawnState();
};