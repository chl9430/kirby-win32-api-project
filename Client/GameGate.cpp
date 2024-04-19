#include "pch.h"
#include "GameGate.h"

GameGate::GameGate(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject{ _strName, _vPos, _vScale }
{
}

GameGate::~GameGate()
{
}

void GameGate::Update()
{
}

//void GameGate::Render(HDC _dc)
//{
//}
