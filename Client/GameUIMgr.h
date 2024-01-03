#pragma once

class GameUI;

class GameUIMgr
{
	SINGLE(GameUIMgr);

private:
	GameUI* m_pFocusedUI;

	GameUI* GetFocusedUI();
	GameUI* GetTargetedUI(GameUI* _pParentUI); // 부모 UI 내에서 실제로 타겟팅 된 UI를 찾아서 반환한다.

public:
	void Update();

	void SetFocusedUI(GameUI* _pUI);
};