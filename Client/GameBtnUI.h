#pragma once
#include "GameUI.h"

class GameScene;

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

typedef void(GameScene::* SCENE_MEMFUNC)(void);

class GameBtnUI :
    public GameUI
{
private:
    SCENE_MEMFUNC m_pSceneFunc;
    GameScene* m_pSceneInst;

    BTN_FUNC m_pFunc;
    DWORD_PTR m_param1;
    DWORD_PTR m_param2;

public:
    void SetClickedCallBack(GameScene* _pScene, SCENE_MEMFUNC _pSceneFunc);
    virtual void MouseLbtnClicked();

    GameBtnUI();
    ~GameBtnUI();
};