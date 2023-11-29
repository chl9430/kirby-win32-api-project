#pragma once

class GameRes;
class GameTexture;

class GameResMgr
{
	SINGLE(GameResMgr);

private:
	map<wstring, GameRes*> m_mapTex;

public:
	GameTexture* CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight);
	GameTexture* FindTexture(const wstring& _strKey);
};