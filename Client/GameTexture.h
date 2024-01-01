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
    void Load(const wstring& _strFilePath);
    void Create(UINT _iWidth, UINT _iHeight);

    HDC GetDC()
    {
        return m_dc;
    }
    UINT Width()
    {
        return m_bitInfo.bmWidth;
    }
    UINT Height()
    {
        return m_bitInfo.bmHeight;
    }

    GameTexture();
    virtual ~GameTexture();
};

