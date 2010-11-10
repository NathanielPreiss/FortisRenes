#include "CHelicopter.h"

CHelicopter::CHelicopter(void) : CEnemy(WEP_PISTOL)
{
	SetEnemyID(ENEMY_HELICOPTER);
	SetMoneyReward(10);
	SetRepReward(10);
	SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/SaT_Helicopter_Shadow.png"));
	// Load in shooting animation
	SetAnimation(CAnimationManager::GetInstance()->LoadAnimation("Resource/Graphics/JaF_HelicopterShoot.bin"));
}

CHelicopter::~CHelicopter(void)
{
}

void CHelicopter::Update(float fElapsedTime)
{
	tVector2D vel;
	vel.fX = GetVelX();
	vel.fY = GetVelY();
	tVector2D facing;
	facing.fX = 0.0f;
	facing.fY = 1.0f;

	m_fRotation = AngleBetweenVectors(facing,vel);

	SetPosX(GetPosX()+GetVelX()*fElapsedTime);
	SetPosY(GetPosY()+GetVelY()*fElapsedTime);
	m_fShadowPosX = GetPosX() + GetVelX()*3.0f;
	m_fShadowPosY = GetPosY() + GetVelX()*3.0f;

	if( GetAnimation() != NULL )
		GetAnimation()->Update(fElapsedTime);
}

void CHelicopter::Render(float fCamPosX, float fCamPosY)
{
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(),(int)m_fShadowPosX-(int)fCamPosX,(int)m_fShadowPosY-(int)fCamPosY,1.0f,1.0f,0,m_fShadowPosX,m_fShadowPosY,m_fRotation);

	if( GetAnimation() != NULL )
	{
		GetAnimation()->Render(GetPosX()-fCamPosX,GetPosY()-fCamPosY,0.0f,0.0f);
	}
}

void CHelicopter::HandleEvent(CEvent *pEvent)
{
}