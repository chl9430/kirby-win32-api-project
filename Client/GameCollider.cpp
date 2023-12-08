#include "pch.h"
#include "GameCollider.h"

#include "GameCamera.h"

#include "GameObject.h"
#include "SelectGDI.h"

GameCollider::GameCollider()
	: m_pOwner{ nullptr }
	, m_vOffsetPos{}
	, m_vScale{}
	, m_iCol{ 0 }
	, m_vFinalPos{}
	, m_iId{ 0 }
{
}

GameCollider::~GameCollider()
{
}

void GameCollider::FinalUpdate()
{
	// Player의 위치를 따라간다.
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	assert(0 <= m_iCol);
}

void GameCollider::Render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_iCol)
		ePen = PEN_TYPE::RED;

	SelectGDI p{ _dc, ePen };
	SelectGDI b{ _dc, BRUSH_TYPE::HOLLOW };

	Vec2 vRenderPos = GameCamera::GetInst()->GetRenderPos(m_vFinalPos);

	Rectangle(_dc
		, (int)(vRenderPos.x - m_vScale.x / 2.f)
		, (int)(vRenderPos.y - m_vScale.y / 2.f)
		, (int)(vRenderPos.x + m_vScale.x / 2.f)
		, (int)(vRenderPos.y + m_vScale.y / 2.f));
}

void GameCollider::OnCollision(GameCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void GameCollider::OnCollisionEnter(GameCollider* _pOther)
{
	m_pOwner->OnCollisionEnter(_pOther);
	++m_iCol;
}

void GameCollider::OnCollisionExit(GameCollider* _pOther)
{
	m_pOwner->OnCollisionExit(_pOther);
	--m_iCol;
}