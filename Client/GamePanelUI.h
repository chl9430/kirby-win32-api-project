#pragma once
#include "GameUI.h"

class GamePanelUI :
    public GameUI
{
private:
    Vec2 m_vDragStart;

public:
    virtual void render(HDC _dc);

    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();

    GamePanelUI();
    ~GamePanelUI();
};