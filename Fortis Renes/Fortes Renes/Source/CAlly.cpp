#include "CAlly.h"
#include "CWeapon.h"
#include "CHostageState.h"
#include "CRebelState.h"
#include "CEventSystem.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CAnimationManager.h"
#include "CCamera.h"
#include "CMessageSystem.h"
#include "CBullet.h"
#include "DirectX Wrappers/CSGD_WaveManager.h"
#include "CEnemy.h"

CAlly::CAlly(bool bHostage)
{
	SetCoverObject(false);
	SetType(OBJECT_ALLY);
	m_pWeapon = new CWeapon(WEP_MACHINEGUN);
	if( bHostage )
	{
		m_pAIState = CHostageState::GetInstance();
	}
	else
	{
		m_pAIState = CRebelState::GetInstance();
	}

	SetAnimation(CAnimationManager::GetInstance()->LoadAnimation("resource\\data\\JaF_LightInfantryAnimation.bin"));
	GetAnimation()->currAnimation->Play();
	SetWidth(32);
	SetHeight(32);
	SetArmor(10);
	SetTarget(NULL);
	m_nWeaponSoundID = CSGD_WaveManager::GetInstance()->LoadWave("Resource/Sounds/Gunshot.wav");

	m_nSpeed = 10;

	CEventSystem::GetInstance()->RegisterClient("enemy.died",this);
	CEventSystem::GetInstance()->RegisterClient("enemy.here",this);
	CEventSystem::GetInstance()->RegisterClient("call.ally",this);
	CEventSystem::GetInstance()->RegisterClient("return.ally",this);
}

CAlly::~CAlly(void)
{
	delete m_pWeapon;
	CEventSystem::GetInstance()->UnregisterClient("enemy.died",this);
	CEventSystem::GetInstance()->UnregisterClient("enemy.here",this);
	CEventSystem::GetInstance()->UnregisterClient("call.ally",this);
	CEventSystem::GetInstance()->UnregisterClient("return.ally",this);
}

void CAlly::Update(float fElapsedTime)
{
	if( m_pAIState != NULL )
	{
		m_pAIState->CalculateAI(fElapsedTime, this);
	}

	SetPosX(GetPosX()+GetVelX()*fElapsedTime);
	SetPosY(GetPosY()+GetVelY()*fElapsedTime);
}

void CAlly::HandleEvent(CEvent* pEvent)
{
	if( pEvent->GetEventID() == "enemy.died" )
	{
		if( GetTarget() == pEvent->GetParam() )
		{
			SetTarget(NULL);
		}
	}
	if( pEvent->GetEventID() == "enemy.here" )
	{
		if( GetTarget() == NULL )
		{
			SetTarget((CBase*)pEvent->GetParam());
		}
	}
	if( pEvent->GetEventID() == "call.ally" )
	{
		SetPosX(1137.0f);
		SetPosY(890.0f);
	}
	if( pEvent->GetEventID() == "return.ally" )
	{
		SetPosX(800.0f);
		SetPosY(100.0f);
	}
}

void CAlly::Render(float fCamPosX, float fCamPosY)
{
	if(GetAnimation() != NULL && GetAnimation()->currSheet != NULL)
		GetAnimation()->Render((GetPosX()-GetWidth()*0.5f) - fCamPosX, (GetPosY()-GetHeight()*0.5f) - fCamPosY, 1.0f, 1.0f);
	else
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX() - (GetWidth() * 0.5f) - CCamera::GetInstance()->GetPosX()),
											(int)(GetPosY() - (GetHeight() * 0.5f) - CCamera::GetInstance()->GetPosY()));
}

bool CAlly::CheckCollision(CBase* pBase)
{
	if( pBase->GetType() == OBJECT_ENEMY )
	{
		CEnemy* pEnemy = (CEnemy*)pBase;
		if( pEnemy->GetDead() == false )
		{
			tVector2D distance;
			distance.fX = pBase->GetPosX() - GetPosX();
			distance.fY = pBase->GetPosY() - GetPosY();

			float length = Vector2DLength(distance);

			if( length < GetWeapon()->GetRange() )
			{
				SetTarget(pBase);
			}
		}
	}
	RECT collision;
	if( CBase::CheckCollision( pBase, &collision ) )
	{	
		if( pBase->GetType() == OBJECT_BULLET )
		{
			CBullet* bullet = (CBullet*)pBase;
			if( bullet->GetOwner()->GetType() == OBJECT_ENEMY )
			{
				SetHealth(GetHealth()-bullet->GetDamage());
				CMessageSystem::GetInstance()->SendMsg( new CDestroyBullet(bullet));
			}
			return true;
		}

		int rWidth, rHeight;
		rWidth = collision.right - collision.left;
		rHeight = collision.bottom - collision.top;
		if( rWidth >= rHeight )
		{
			if( GetPosY() < pBase->GetPosY() )
			{
				SetPosY(pBase->GetPosY() - ((GetHeight()*0.5f) + (pBase->GetHeight()*0.5f)));
			}
			else
			{
				SetPosY(pBase->GetPosY() + ((GetHeight()*0.5f) + (pBase->GetHeight()*0.5f)));
			}
		}
		if( rHeight >= rWidth )
		{
			if( GetPosX() < pBase->GetPosX() )
			{
				SetPosX(pBase->GetPosX() - ((GetWidth()*0.5f) + (pBase->GetWidth()*0.5f)));
			}
			else
			{
				SetPosX(pBase->GetPosX() + ((GetWidth()*0.5f) + (pBase->GetWidth()*0.5f)));
			}
		}

		return false;
	}
	return false;
}