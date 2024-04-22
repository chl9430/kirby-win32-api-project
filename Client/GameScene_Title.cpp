#include "pch.h"
#include "GameScene_Title.h"

#include "GameCore.h"

#include "GameResMgr.h"
#include "GameEventMgr.h"
#include "GameCollisionMgr.h"
#include "GameCamera.h"

#include "GameTexture.h"
#include "GameSound.h"

#include "GameObject.h"
#include "GameBackground.h"
#include "GamePanelUI.h"
#include "GameBtnUI.h"

GameScene_Title::GameScene_Title()
	: m_pBGM{ nullptr }
{
}

GameScene_Title::~GameScene_Title()
{
	delete m_pBGM;
}

void GameScene_Title::Enter()
{
	Vec2 vResolution = GameCore::GetInst()->GetResolution();

	m_pBGM = new GameSound{};

	m_pBGM->Load(L"sound\\Title.wav");
	m_pBGM->PlayToBGM(true);
	m_pBGM->SetVolume(100.f);

	GameTexture* pBackgroundTex = GameResMgr::GetInst()->LoadTexture(L"TitleBackground", L"texture\\Title_Background.bmp");
	GameTexture* pStartBtnTex = GameResMgr::GetInst()->LoadTexture(L"TitleStartButton", L"texture\\Title_Start_Button.bmp");
	GameTexture* pStartBtnClickedTex = GameResMgr::GetInst()->LoadTexture(L"TitleStartButtonClicked", L"texture\\Title_Start_Button_Selected.bmp");
	GameTexture* pToolBtnTex = GameResMgr::GetInst()->LoadTexture(L"TitleToolButton", L"texture\\Title_Tool_Button.bmp");
	GameTexture* pToolBtnClickedTex = GameResMgr::GetInst()->LoadTexture(L"TitleToolButtonClicked", L"texture\\Title_Tool_Button_Selected.bmp");

	GameBackground* pTitleBackground = new GameBackground{ L"Title_Background", Vec2{ 0.f - pBackgroundTex->Width() / 2, 0.f + pBackgroundTex->Height() / 2 }, Vec2{ (int)pBackgroundTex->Width(), (int)pBackgroundTex->Height() } };
	pTitleBackground->SetOriginSize((UINT)pBackgroundTex->Width(), (UINT)pBackgroundTex->Height());

	pTitleBackground->SetCurrentTexture(pBackgroundTex);
	AddObject(pTitleBackground, GROUP_TYPE::BACKGROUND);

	// Panel 생성
	GameUI* pPanelUI = new GamePanelUI{ false, L"ParentUI", Vec2{ 0, 0 }, Vec2{ 0, 0 } };
	AddObject(pPanelUI, GROUP_TYPE::UI);

	// 시작 버튼 생성
	GameBtnUI* pStartBtn = new GameBtnUI{ false, L"TitleStartButton", Vec2{ 0, 0 }, Vec2{ 0, 0 } };
	pStartBtn->SetScale(Vec2{ (int)pStartBtnTex->Width(), (int)pStartBtnTex->Height() });
	pStartBtn->SetTexture(pStartBtnTex);
	pStartBtn->SetMouseDownTexture(pStartBtnClickedTex);
	pStartBtn->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Title::StartBtnChangeScene);
	pPanelUI->AddChild(pStartBtn);

	// 툴 버튼 생성
	GameBtnUI* pToolBtn = new GameBtnUI{ false, L"TitleToolButton", Vec2{ 0, 0 }, Vec2{ 0, 0 } };
	pToolBtn->SetScale(Vec2{ (int)pToolBtnTex->Width(), (int)pToolBtnTex->Height() });
	pToolBtn->SetTexture(pToolBtnTex);
	pToolBtn->SetMouseDownTexture(pToolBtnClickedTex);
	pToolBtn->SetClickedCallBack(this, (SCENE_MEMFUNC_1)&GameScene_Title::ToolBtnChangeScene);
	pPanelUI->AddChild(pToolBtn);

	pPanelUI->SetScale(Vec2{ pStartBtn->GetScale().x, pStartBtn->GetScale().y * 2 });
	pPanelUI->SetPos(Vec2{ vResolution.x / 2 - pPanelUI->GetScale().x / 2, vResolution.y / 2 });
	pToolBtn->SetPos(Vec2{ 0.f, pPanelUI->GetScale().y / 2 });
}

void GameScene_Title::Exit()
{
	DeleteAll();

	GameCamera::GetInst()->ResetCameraPos();

	// 다른 씬에서는 다른 그룹간의 충돌 체크를 하게될 수 있으니 리셋한다.
	GameCollisionMgr::GetInst()->Reset();
}