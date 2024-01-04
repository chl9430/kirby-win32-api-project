#pragma once
#include "GameUI.h"

#include "GameScene.h"
#include "GameObject.h"
#include "GameScene_Tool.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

typedef void(GameScene::*SCENE_MEMFUNC)(EDIT_MODE);

class GameBtnUI :
    public GameUI
{
private:
    SCENE_MEMFUNC m_pSceneFunc;
    GameScene* m_pSceneInst;

    GameTexture* m_pIdleTexture;
    GameTexture* m_pMouseOnTex;
    GameTexture* m_pMouseDownTex;
    GameTexture* m_pMouseUpTex;

    BTN_FUNC m_pFunc;
    DWORD_PTR m_param1;
    DWORD_PTR m_param2;

public:
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    void SetClickedCallBack(GameScene* _pScene, SCENE_MEMFUNC _pSceneFunc);
    void SetIdleTexture(GameTexture* _pTex)
    {
        m_pIdleTexture = _pTex;
    }
    void SetMouseOnTexture(GameTexture* _pTex)
    {
        m_pMouseOnTex = _pTex;
    }
    void SetMouseDownTexture(GameTexture* _pTex)
    {
        m_pMouseDownTex = _pTex;
    }
    void SetMouseUpTexture(GameTexture* _pTex)
    {
        m_pMouseUpTex = _pTex;
    }

    GameBtnUI(bool _bCamAff);
    ~GameBtnUI();
};