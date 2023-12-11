#pragma once

class GameMonster;

enum class MON_TYPE
{
	NORMAL,
	RANGE,
};

class GameMonsterFactory
{
public:
	static GameMonster* CreateMonster(MON_TYPE _eType, Vec2 _vPos);

private:
	GameMonsterFactory();
	~GameMonsterFactory();
};