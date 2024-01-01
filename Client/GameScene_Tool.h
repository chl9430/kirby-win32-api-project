#pragma once
#include "GameScene.h"

class GameScene_Tool :
    public GameScene
{
private:

public:
    virtual void Enter();
    virtual void Exit();
    virtual void Update();
    
    void SaveTileData();
    void SaveTile(const wstring& _strFilePath);
    void LoadTileData();
    void SetTileIdx();

    GameScene_Tool();
    ~GameScene_Tool();
};