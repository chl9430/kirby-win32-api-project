#pragma once
#include "GameScene.h"

enum class EDIT_MODE
{
    NONE,
    BACKGROUND,
    LAST,
};

class GameScene_Tool :
    public GameScene
{
private:
    EDIT_MODE m_eCurMode;

public:
    virtual void Enter();
    virtual void Exit();
    virtual void Update();
    
    void SaveTileData();
    void SaveTile(const wstring& _strFilePath);
    void LoadTileData();
    void SetTileIdx();
    void SetCurMode(EDIT_MODE _eMode)
    {
        m_eCurMode = _eMode;
    }

    GameScene_Tool();
    ~GameScene_Tool();
};