#pragma once
#include "GameRes.h"

class GameTexture :
    public GameRes
{
private:
    HDC m_dc;
    HBITMAP m_hBit;
    BITMAP m_bitInfo;

public:
    void Create(UINT _iWidth, UINT _iHeight);

    GameTexture();
    virtual ~GameTexture();
};

