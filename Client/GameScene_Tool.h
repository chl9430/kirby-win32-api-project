#pragma once
#include "GameScene.h"

class GameUI;

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
    wstring m_strTileName;
    GameUI* m_pPanel;

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
    void SetSelectedTexture(wstring _strTileName)
    {
        m_strTileName = _strTileName;
    }

    GameScene_Tool();
    ~GameScene_Tool();
};