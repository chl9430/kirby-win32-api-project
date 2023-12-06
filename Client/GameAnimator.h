#pragma once

class GameAnimation;
class GameObject;

class GameAnimator
{
private:
	map<wstring, GameAnimation*> m_mapAnim;
	GameObject* m_pOwner;
	GameAnimation* m_pCurAnim;
	bool m_bRepeat;

public:
	void Play(const wstring& _strName, bool _bRepeat);

	GameAnimation* FindAnimation(const wstring& _strName);
	void LoadAnimation(const wstring& _strRelativePath);

	GameAnimator();
	~GameAnimator();

	friend class GameObject;
};