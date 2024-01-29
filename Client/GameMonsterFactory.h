#pragma once

class GameMonster;

enum class MON_TYPE
{
	WADDLE_DEE,
	SCARFY,
	PENGY
};

class GameMonsterFactory
{
public:
	static GameMonster* CreateMonster(MON_TYPE _eType, Vec2 _vPos);

private:
	GameMonsterFactory();
	~GameMonsterFactory();
};