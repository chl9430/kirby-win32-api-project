#include "pch.h"
#include "GameObject.h"

#include "GameCamera.h"

#include "GameSight.h"
#include "GameCollider.h"
#include "GameRigidBody.h"
#include "GameAnimator.h"
#include "GameGravity.h"
#include "GameTexture.h"

GameObject::GameObject(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: m_strName{ _strName }
	, m_vPos{ _vPos }
	, m_vScale{ _vScale }
	, m_bAlive{ true }
	, m_iDir{ 1 }
	, m_iPrevDir{ 1 }
	, m_pCurTexture{ nullptr }
	, m_pObjScene{ nullptr }
	, m_pCollider{ nullptr }
	, m_pRigidBody{ nullptr }
	, m_pAnimator{ nullptr }
	, m_pGravity{ nullptr }
	, m_isTouchBottom{ false }
	, m_isTouchLeft{ false }
	, m_isTouchRight{ false }
	, m_isTouchTop{ false }
{
}

GameObject::~GameObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;

	if (nullptr != m_pAnimator)
		delete m_pAnimator;

	if (nullptr != m_pRigidBody)
		delete m_pRigidBody;

	if (nullptr != m_pGravity)
		delete m_pGravity;
}

void GameObject::FinalUpdate()
{
	if (m_pAnimator)
		m_pAnimator->FinalUpdate();

	if (m_pGravity)
		m_pGravity->FinalUpdate();

	if (m_pRigidBody)
		m_pRigidBody->FinalUpdate();

	if (m_pCollider)
		m_pCollider->FinalUpdate();
}

void GameObject::Render(HDC _dc)
{
	Vec2 vRenderPos = GameCamera::GetInst()->GetRenderPos(m_vPos);

	if (m_pCurTexture)
	{
		TransparentBlt(_dc
			, (int)(vRenderPos.x - m_vScale.x / 2)
			, (int)(vRenderPos.y - m_vScale.y / 2)
			, (int)(m_vScale.x)
			, (int)(m_vScale.y)
			, m_pCurTexture->GetDC()
			, 0
			, 0
			, (int)(m_vScale.x)
			, (int)(m_vScale.y)
			, RGB(255, 0, 255)
		);
	}
	else
	{
		Rectangle(_dc
			, (int)(vRenderPos.x - m_vScale.x / 2.f)
			, (int)(vRenderPos.y - m_vScale.y / 2.f)
			, (int)(vRenderPos.x + m_vScale.x / 2.f)
			, (int)(vRenderPos.y + m_vScale.y / 2.f));
	}

	ComponentRender(_dc);
}

void GameObject::ComponentRender(HDC _dc)
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->Render(_dc);
	}

	if (nullptr != m_pCollider)
	{
		m_pCollider->Render(_dc);
	}
}

void GameObject::CreateCollider()
{
	m_pCollider = new GameCollider;
	m_pCollider->m_pOwner = this;
}

void GameObject::CreateRigidBody()
{
	m_pRigidBody = new GameRigidBody;
	m_pRigidBody->m_pOwner = this;
}

void GameObject::CreateAnimator()
{
	m_pAnimator = new GameAnimator;
	m_pAnimator->m_pOwner = this;
}

void GameObject::CreateGravity()
{
	m_pGravity = new GameGravity;
	m_pGravity->m_pOwner = this;
}

void GameObject::SetTouchBottom(bool _b)
{
	m_isTouchBottom = _b;

	if (m_isTouchBottom && m_pRigidBody)
	{
		Vec2 vV = GetRigidBody()->GetVelocity();
		GetRigidBody()->SetVelocity(Vec2{ vV.x, 0.f });
	}
}