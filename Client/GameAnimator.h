#pragma once

class GameAnimation;
class GameObject;
class GameTexture;

class GameAnimator
{
private:
	map<wstring, GameAnimation*> m_mapAnim;
	GameObject* m_pOwner;
	GameAnimation* m_pCurAnim;
	GameAnimation* m_pPrevAnim;
	bool m_bRepeat;

public:
	void Play(const wstring& _strName, bool _bRepeat);

	void CreateAnimation(const wstring& _strName, GameTexture* _pTex, float _fDuration);
	GameAnimation* FindAnimation(const wstring& _strName);
	void LoadAnimation(const wstring& _strRelativePath);

	void FinalUpdate();
	void Render(HDC _dc);

	GameObject* GetObj()
	{
		return m_pOwner;
	}
	bool IsRepeatAnim()
	{
		return m_bRepeat;
	}
	GameAnimation* GetCurrentAnim()
	{
		return m_pCurAnim;
	}

	GameAnimator();
	~GameAnimator();

	friend class GameObject;
};