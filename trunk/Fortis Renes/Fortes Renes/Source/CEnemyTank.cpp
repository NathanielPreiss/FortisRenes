#include "CEnemyTank.h"
#include "CMessageSystem.h"
#include "CBullet.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CCamera.h"

CEnemyTank::CEnemyTank() : CEnemy(WEP_PISTOL)
{
	m_fTimeBucket = 0.0f;
	m_fShotTimer = 5.0f;
	SetEnemyID(ENEMY_TANK);
	SetMoneyReward(50);
	SetRepReward(10);
	SetHeight(64);
	SetWidth(64);
	SetMaxHealth(200);
	SetVelX(0.0f);
	SetVelY(0.0f);
	SetSpeed(50.0f);
	SetHealth(GetMaxHealth());
	SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Idle Tank.png", D3DCOLOR_XRGB(255,0,255)));
}

CEnemyTank::~CEnemyTank()
{
}

void CEnemyTank::Update(float fElapsedTime)
{
	m_fTimeBucket += fElapsedTime;

	tVector2D toTarget;
	tVector2D originalFacing;
	if( GetTarget() != NULL )
	{
		toTarget.fX = GetTarget()->GetPosX() - GetPosX();
		toTarget.fY = GetTarget()->GetPosY() - GetPosY();

		originalFacing.fX = 0.0f;
		originalFacing.fY = -1.0f;
		m_fRotation = AngleBetweenVectors(originalFacing, toTarget);
		
		if( GetTarget()->GetPosX() < GetPosX() )
			m_fRotation = -m_fRotation;
	}

	if( m_fTimeBucket > m_fShotTimer )
	{
		if( GetTarget() != NULL )
		{
			CMessageSystem::GetInstance()->SendMsg(new CCreateEnemyBullet(this));
		}
		m_fTimeBucket = 0.0f;
	}

	if( GetHealth() < GetMaxHealth()*0.5f )
	{
		toTarget = Vector2DNormalize(toTarget);
		toTarget = toTarget * GetSpeed();

		SetVelX(-toTarget.fX);
		SetVelY(-toTarget.fY);
	}

	if( GetHealth() < 0 )
	{
		CMessageSystem::GetInstance()->SendMsg( new CDestroyEnemy(this));
	}

	SetPosX(GetPosX() + GetVelX() * fElapsedTime );
	SetPosY(GetPosY() + GetVelY() * fElapsedTime );
}

bool CEnemyTank::CheckCollision(CBase* pBase)
{
	if( pBase->GetType() == OBJECT_PLAYER || pBase->GetType() == OBJECT_ALLY )
	{
		tVector2D toTarget;
		toTarget.fX = pBase->GetPosX()-GetPosX();
		toTarget.fY = pBase->GetPosY()-GetPosY();

		if( Vector2DLength(toTarget) < 500 )
			SetTarget(pBase);
		else
			SetTarget(NULL);
	}
	if( pBase->GetType() == OBJECT_BULLET )
	{
		CBullet* pBullet = (CBullet*)pBase;
		if( pBullet->GetWeaponID() == WEP_BAZOOKA && CBase::CheckCollision(pBase) )
		{
			SetHealth(GetHealth()-34);
		}
		CMessageSystem::GetInstance()->SendMsg( new CDestroyBullet(pBullet));
	}

	return false;
}

void CEnemyTank::Render(float fCamPosX, float fCamPosY)
{
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX() - (GetWidth() * 0.5f) - CCamera::GetInstance()->GetPosX()),
											(int)(GetPosY() - (GetHeight() * 0.5f) - CCamera::GetInstance()->GetPosY()), 1.0f, 1.0f, 0, (GetWidth()*0.5f),(GetHeight()*0.5f),m_fRotation);
}