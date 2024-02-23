#pragma once

class GameMonster;

class GameMonsterFactory
{
public:
	static GameMonster* CreateMonster(MON_NAME _eType, Vec2 _vPos);

private:
	GameMonsterFactory();
	~GameMonsterFactory();
};