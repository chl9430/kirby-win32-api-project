#pragma once
#include "GameScene.h"

class GameUI;

enum class EDIT_MODE
{
    NONE,
    TILE,
    LAST,
};

class GameScene_Tool :
    public GameScene
{
private:
    EDIT_MODE m_eCurMode;
    wstring m_strSelectedTileName;
    GameUI* m_pPanel;

public:
    virtual void Enter();
    virtual void Exit();
    virtual void Update();
    
    void SaveTileData();
    void SaveTile(const wstring& _strFilePath);
    void LoadTileData();
    void SetCurMode(EDIT_MODE _eMode)
    {
        m_eCurMode = _eMode;
    }
    void SetSelectedTileName(wstring _strTileName)
    {
        m_strSelectedTileName = _strTileName;
    }
    wstring& GetSelectedTileName()
    {
        return m_strSelectedTileName;
    }

    GameScene_Tool();
    virtual ~GameScene_Tool();
};