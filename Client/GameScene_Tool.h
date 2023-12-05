#pragma once
#include "GameScene.h"

class GameScene_Tool :
    public GameScene
{
private:

public:
    virtual void Enter();
    virtual void Exit();

    GameScene_Tool();
    ~GameScene_Tool();
};