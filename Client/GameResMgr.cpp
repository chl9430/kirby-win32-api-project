#include "pch.h"
#include "GameResMgr.h"

#include "GamePathMgr.h"

#include "GameTexture.h"

GameResMgr::GameResMgr()
{

}

GameResMgr::~GameResMgr()
{
	Safe_Delete_Map(m_mapTex);
}

void GameResMgr::Init()
{
	GameTexture* pTex = LoadTexture(L"Stage1TileSet", L"texture\\tile\\Stage1_Tile_Set.bmp");

	UINT iWidth = pTex->Width();
	UINT iHeight = pTex->Height();

	UINT iTileCount = (iWidth * iHeight) / (TILE_SIZE * TILE_SIZE);

	for (UINT i = 0; i < iTileCount; ++i)
	{
		LoadTexture(L"Stage1TileButton" + to_wstring(i), L"texture\\tile\\Stage1_Tile_Button_" + to_wstring(i) + L".bmp");
	}
}

GameTexture* GameResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	GameTexture* pTex = FindTexture(_strKey);

	if (pTex != nullptr)
	{
		return pTex;
	}

	wstring strFilePath = GamePathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new GameTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

GameTexture* GameResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	GameTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr)
		return pTex;

	pTex = new GameTexture;
	pTex->Create(_iWidth, _iHeight);
	pTex->SetKey(_strKey);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

GameTexture* GameResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, GameRes*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end()) // �ؽ�ó�� ������
	{
		return nullptr;
	}

	return (GameTexture*)iter->second;
}
