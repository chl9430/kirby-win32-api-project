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

//void GameTile::Render(HDC _dc)
//{
//	if (nullptr == m_pTileTex || -1 == m_iImgIdx)
//		return;
//
//	UINT iWidth = m_pTileTex->Width();
//	UINT iHeight = m_pTileTex->Height();
//
//	UINT iMaxCol = iWidth / TILE_SIZE;
//	UINT iMaxRow = iHeight / TILE_SIZE;
//
//	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;
//	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;
//
//	if (iMaxRow <= iCurRow)
//		assert(nullptr);
//
//	Vec2 vRenderPos = GameCamera::GetInst()->GetRenderPos(GetPos());
//	Vec2 vScale = GetScale();
//
//	TransparentBlt(_dc
//		, (int)(vRenderPos.x)
//		, (int)(vRenderPos.y)
//		, (int)(vScale.x)
//		, (int)(vScale.y)
//		, m_pTileTex->GetDC()
//		, iCurCol * TILE_SIZE
//		, iCurRow * TILE_SIZE
//		, (int)(vScale.x)
//		, (int)(vScale.y)
//		, RGB(255, 0, 255)
//	);
//}

void GameTile::Save(FILE* _pFile)
{
	// 타일의 위치
	fwprintf(_pFile, L"[Tile Pos]\n");
	fwprintf(_pFile, L"%d %d\n", (int)GetPos().x, (int)GetPos().y);
	fwprintf(_pFile, L"\n");

	// 타일의 텍스처
	fwprintf(_pFile, L"[Tile Texture]\n");
	fwprintf(_pFile, GetCurrentTexture()->GetKey().c_str());
	fwprintf(_pFile, L"\n\n");
}

//void GameTile::Load(FILE* _pFile)
//{
//	// 타일의 위치
//	wstring str;
//	wchar_t szBuff[256] = {};
//
//	WScanf(szBuff, _pFile);
//	WScanf(szBuff, _pFile);
//	str = szBuff;
//
//	m_strName = wstring(str.begin(), str.end());
//
//	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
//}

void GameTile::SetTexture(GameTexture* _pTex)
{
	m_pTileTex = _pTex;

	m_iMaxImgIdx = (_pTex->Width() / TILE_SIZE) * (_pTex->Height() / TILE_SIZE);
}