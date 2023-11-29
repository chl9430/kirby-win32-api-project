#include "pch.h"
#include "GameResMgr.h"

#include "GameTexture.h"

GameResMgr::GameResMgr()
{

}

GameResMgr::~GameResMgr()
{
	Safe_Delete_Map(m_mapTex);
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

	if (iter == m_mapTex.end()) // 텍스처가 없으면
	{
		return nullptr;
	}

	return (GameTexture*)iter->second;
}
