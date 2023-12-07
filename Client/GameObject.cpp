#include "pch.h"
#include "GameObject.h"

#include "GameCollider.h"
#include "GameRigidBody.h"
#include "GameAnimator.h"
#include "GameGravity.h"

GameObject::GameObject()
	: m_strName{}
	, m_vPos{}
	, m_vScale{}
	, m_bAlive{ true }
	, m_pCollider{ nullptr }
	, m_pRigidBody{ nullptr }
	, m_pAnimator{ nullptr }
	, m_pGravity{ nullptr }
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
	/*if (m_pCollider)
		m_pCollider->FinalUpdate();*/

	if (m_pAnimator)
		m_pAnimator->FinalUpdate();

	/*if (m_pRigidBody)
		m_pRigidBody->FinalUpdate();

	if (m_pGravity)
		m_pGravity->FinalUpdate();*/
}

void GameObject::Render(HDC _dc)
{
	/*Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	Rectangle(_dc
		, (int)(vRenderPos.x - m_vScale.x / 2.f)
		, (int)(vRenderPos.y - m_vScale.y / 2.f)
		, (int)(vRenderPos.x + m_vScale.x / 2.f)
		, (int)(vRenderPos.y + m_vScale.y / 2.f));*/

	Rectangle(_dc
		, (int)(m_vPos.x - m_vScale.x / 2.f)
		, (int)(m_vPos.y - m_vScale.y / 2.f)
		, (int)(m_vPos.x + m_vScale.x / 2.f)
		, (int)(m_vPos.y + m_vScale.y / 2.f));

	ComponentRender(_dc);
}

void GameObject::ComponentRender(HDC _dc)
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->Render(_dc);
	}

	/*if (nullptr != m_pCollider)
	{
		m_pCollider->Render(_dc);
	}*/
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