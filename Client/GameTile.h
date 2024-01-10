#pragma once
#include "GameObject.h"

class GameTexture;

class GameTile :
    public GameObject
{
private:
    GameTexture* m_pTileTex;
    int m_iImgIdx;
    int m_iMaxImgIdx;

public:
    virtual void Update();
    /*virtual void Render(HDC _dc);*/

    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

    void AddImgIdx()
    {
        ++m_iImgIdx;

        if (m_iImgIdx == m_iMaxImgIdx)
        {
            m_iImgIdx = 0;
        }
    }
    void SetTexture(GameTexture* _pTex);

    GameTile();
    ~GameTile();
};