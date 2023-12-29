#include "pch.h"
#include "GameGround.h"

#include "GameResMgr.h"
#include "GameCamera.h"

#include "GameCollider.h"
#include "GameGravity.h"
#include "GameTexture.h"
#include "GameAnimator.h"

GameGround::GameGround()
	: m_pTex{ nullptr }
{
	CreateCollider();
}

GameGround::~GameGround()
{
}

void GameGround::Start()
{
	GetCollider()->SetScale(Vec2{ GetScale() });
	m_pTex = GameResMgr::GetInst()->LoadTexture(L"Stage1_1", L"texture\\tile\\Stage1_1.bmp");
}

void GameGround::Update()
{
}

void GameGround::Render(HDC _dc)
{
	Vec2 vPos = GameCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(
		_dc,
		(int)(vPos.x - GetScale().x / 2.f),
		(int)(vPos.y - GetScale().y / 2.f),
		(int)GetScale().x,
		(int)GetScale().y,
		m_pTex->GetDC(),
		0,
		0,
		(int)GetScale().x,
		(int)GetScale().y,
		RGB(255, 0, 255)
	);
}

void GameGround::OnCollisionEnter(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Monster")
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		// 충돌을 접한 상태로 유지하기 위해 일부로 1픽셀 올려준다.
		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= (fValue);

		pOtherObj->SetPos(vObjPos);
	}
}

void GameGround::OnCollision(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Monster")
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		// 충돌을 접한 상태로 유지하기 위해 일부로 1픽셀 올려준다.
		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= (fValue);

		pOtherObj->SetPos(vObjPos);
	}
}

void GameGround::OnCollisionExit(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Monster")
	{
		pOtherObj->GetGravity()->SetGround(false);
	}
}