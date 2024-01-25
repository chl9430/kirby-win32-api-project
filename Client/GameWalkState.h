#pragma once
#include "GameState.h"

class GameWalkState :
    public GameState
{
private:

public:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

    GameWalkState();
    ~GameWalkState();
};