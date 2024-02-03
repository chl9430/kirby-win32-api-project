#pragma once

struct tEvent
{
	EVENT_TYPE eEven;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
};

class GameObject;

class GameEventMgr
{
	SINGLE(GameEventMgr);

private:
	vector<GameObject*> m_vecDead;
	vector<tEvent> m_vecEvent;

	void Execute(const tEvent& _tEve);
public:
	void Update();

	void AddEvent(tEvent _tEve);
};