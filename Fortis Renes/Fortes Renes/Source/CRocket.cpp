#include "CRocket.h"
#include "CEnemyTank.h"
#include "CMessageSystem.h"

CRocket::CRocket(float fDelay)
{
	SetType(OBJECT_ROCKET);
	m_fDelayTime = fDelay;
	m_fTimeBucket = 0.0f;
	SetWidth(32);
	SetHeight(32);
	//m_Explosion->LoadEmitter("randomnameofexplosion");
}

CRocket::~CRocket(void)
{
}

void CRocket::Update(float fElapsedTime)
{
	m_fTimeBucket += fElapsedTime;

	if( m_fTimeBucket > m_fDelayTime )
	{
		CEnemyTank* pTank = (CEnemyTank*)GetOwner();

		if( pTank->GetTarget() != NULL )
		{
			tVector2D toTarget;
			toTarget.fX = pTank->GetTarget()->GetPosX()-GetPosX();
			toTarget.fY = pTank->GetTarget()->GetPosY()-GetPosY();

			if( Vector2DLength(toTarget) < 100 )
			{
				pTank->GetTarget()->SetHealth(pTank->GetTarget()->GetHealth()-34);
			}
		}
		CMessageSystem::GetInstance()->SendMsg( new CDestroyBullet(this));
	}

	m_fScale = m_fTimeBucket / m_fDelayTime;
}

void CRocket::Render(float fCamPosX, float fCamPosY)
{
	CSGD_TextureManager::GetInstance()->Draw( GetImageID(), (int)((GetPosX() - (GetWidth()*0.5f)*m_fScale)-fCamPosX),
											  (int)((GetPosY()-(GetHeight()*0.5f)*m_fScale)-fCamPosY), m_fScale, m_fScale, 0, 
											  (float)(GetWidth()*0.5f), (float)(GetHeight()*0.5f), GetRotation() );
}