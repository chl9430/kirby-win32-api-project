#include "pch.h"
#include "GameTile.h"

#include "GameCamera.h"

#include "GameTexture.h"

GameTile::GameTile()
	: m_pTileTex{ nullptr }
	, m_iImgIdx{ 0 }
	, m_iMaxImgIdx{ 0 }
{
	SetScale(Vec2{ TILE_SIZE, TILE_SIZE });
}

GameTile::~GameTile()
{

}

void GameTile::Update()
{
}

void GameTile::Render(HDC _dc)
{
	if (nullptr == m_pTileTex || -1 == m_iImgIdx)
		return;

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;
	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;

	if (iMaxRow <= iCurRow)
		assert(nullptr);

	Vec2 vRenderPos = GameCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	TransparentBlt(_dc
		, (int)(vRenderPos.x)
		, (int)(vRenderPos.y)
		, (int)(vScale.x)
		, (int)(vScale.y)
		, m_pTileTex->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, (int)(vScale.x)
		, (int)(vScale.y)
		, RGB(255, 0, 255)
	);
}

void GameTile::Save(FILE* _pFile)
{
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void GameTile::Load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void GameTile::SetTexture(GameTexture* _pTex)
{
	m_pTileTex = _pTex;

	m_iMaxImgIdx = (_pTex->Width() / TILE_SIZE) * (_pTex->Height() / TILE_SIZE);
}