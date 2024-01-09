#pragma once
#include "GameUI.h"

#include "GameScene.h"
#include "GameObject.h"
#include "GameScene_Tool.h"

// typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

typedef void(GameScene::*SCENE_MEMFUNC_1) (wstring);

class GameBtnUI :
    public GameUI
{
private:
    SCENE_MEMFUNC_1 m_pSceneFunc;
    GameScene* m_pSceneInst;

    GameTexture* m_pIdleTexture;
    GameTexture* m_pMouseOnTex;
    GameTexture* m_pMouseDownTex;
    GameTexture* m_pMouseUpTex;
    GameTexture* m_pMouseClickedTex;

    /*BTN_FUNC m_pFunc;
    DWORD_PTR m_param1;
    DWORD_PTR m_param2;*/
    wstring m_strParam;

public:
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    void SetTexture(GameTexture* _pTexture);
    void SetClickedCallBack(GameScene* _pScene, SCENE_MEMFUNC_1 _pSceneFunc, wstring _str = L"", DWORD_PTR _param1 = 0, DWORD_PTR _param2 = 0);
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
    void SetMouseClickedTexture(GameTexture* _pTex)
    {
        m_pMouseClickedTex = _pTex;
    }

    GameBtnUI(bool _bCamAff);
    ~GameBtnUI();
};