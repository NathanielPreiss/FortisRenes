#include "CEnemy.h"
#include "CCamera.h"
#include "CMessageSystem.h"
#include "CEventSystem.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_DirectInput.h"
#include "DirectX Wrappers/CSGD_WaveManager.h"
#include "CIdleState.h"
#include "CBullet.h"
#include "CObjectManager.h"


CEnemy::CEnemy(int nWeapon)
{
	SetDead(false);
	m_Weapon = new CWeapon(nWeapon);
	m_nWeaponSoundID = CSGD_WaveManager::GetInstance()->LoadWave("Resource/Sounds/Gunshot.wav");
	m_pTarget = NULL;
	m_bAttack = true;
	m_bCalculate = true;
	m_vFacingNormal.fX = 0;
	m_vFacingNormal.fY = 1;
	Vector2DNormalize(m_vFacingNormal);
	ChangeState(CIdleState::GetInstance());
	SetType(OBJECT_ENEMY);
	CEventSystem::GetInstance()->SendEvent("enemy.here",this);
	CEventSystem::GetInstance()->RegisterClient("Increment.Phase", this);
}
CEnemy::~CEnemy(void)
{
	delete m_Weapon;
	CSGD_WaveManager::GetInstance()->UnloadWave(m_nWeaponSoundID);
	CEventSystem::GetInstance()->UnregisterClient("Increment.Phase", this);
}
void CEnemy::LoadTexture(void)
{
	m_nType = OBJECT_ENEMY;
	SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/NaP_Gundam.png"));
	SetPosX(1000.0f);
	SetPosY(1000.0f);
	SetWidth(32);
	SetHeight(32);
}
void CEnemy::UnloadTexture(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(GetImageID());
}

void CEnemy::Render(float fCamPosX, float fCamPosY)
{
	if(GetAnimation() != NULL && GetAnimation()->currSheet != NULL)
		GetAnimation()->Render((GetPosX()-GetWidth()*0.5f) - fCamPosX, (GetPosY()-GetHeight()*0.5f) - fCamPosY, 1.0f, 1.0f);
	else
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX() - (GetWidth() * 0.5f) - CCamera::GetInstance()->GetPosX()),
											(int)(GetPosY() - (GetHeight() * 0.5f) - CCamera::GetInstance()->GetPosY()));
}
void CEnemy::Update(float fElapsedTime)
{
	// Check if dead
	if( GetHealth() <= 0 && GetDead() == false )
	{
		SetDead(true);
		CEventSystem::GetInstance()->SendEvent("enemy.died",this);
		// Set animation to death animation
		SetCurrAnimation("Die");
	}

	if( GetDead() == true && GetCull() == true )
	{
		CMessageSystem::GetInstance()->SendMsg( new CDestroyEnemy(this));
	}

	if( GetDead() == false )
	{
		// check out of bounds
		int mapWidth = CObjectManager::GetInstance()->GetMap()->MapTileSize * CObjectManager::GetInstance()->GetMap()->MapRow;
		int mapHeight = CObjectManager::GetInstance()->GetMap()->MapTileSize * CObjectManager::GetInstance()->GetMap()->MapColumn;
		if( GetPosX()+GetWidth()*0.5f > mapWidth )
		{
			SetPosX(mapWidth-GetWidth()*0.5f);
		}
		if( GetPosY()+GetHeight()*0.5f > mapHeight )
		{
			SetPosY(mapHeight-GetHeight()*0.5f);
		}
		if( GetPosX()-GetWidth()*0.5f < 0 )
		{
			SetPosX(0+GetWidth()*0.5f);
		}
		if( GetPosY()-GetHeight()*0.5f < 0 )
		{
			SetPosY(0+GetHeight()*0.5f);
		}

		Vector2DNormalize(m_vFacingNormal);
	}
	if(GetAnimation() != NULL && GetAnimation()->currSheet != NULL)
		GetAnimation()->Update(fElapsedTime);
}
RECT CEnemy::GetRect(void)
{
	RECT collisionRect;
	collisionRect.left = LONG(GetPosX() - GetWidth() * 0.5f);
	collisionRect.top = LONG(GetPosY() - GetHeight() * 0.5f);
	collisionRect.right = LONG(collisionRect.left + GetWidth());
	collisionRect.bottom  = LONG(collisionRect.top + GetHeight());

	return collisionRect;
}

void CEnemy::ChangeState(IArtIntState* newState)
{
	if( m_pAiState != newState )
	{
		m_pAiState = newState;
	}
}

bool CEnemy::CheckCollision( CBase *pBase )
{
	if( pBase->GetType() == OBJECT_ALLY )
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
	RECT collision;
	if( CBase::CheckCollision( pBase, &collision ) )
	{
		if( pBase->GetType() == OBJECT_BULLET )
		{
			CBullet* bullet = (CBullet*)pBase;
			if( bullet->GetOwner()->GetType() != OBJECT_ENEMY )
			{
				CEventSystem::GetInstance()->SendEvent("Increment.Phase", this);
				SetHealth(GetHealth()-(bullet->GetDamage()-GetArmor()));
				CMessageSystem::GetInstance()->SendMsg( new CDestroyBullet(bullet));

				if( bullet->GetOwner()->GetType() == OBJECT_PLAYER )
					SetPlayerKill(true);

				if( bullet->GetWeaponID() != WEP_SHOTGUN )
					return false;
			}
			else
				return false;
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

void CEnemy::Shoot(void)
{
	if( GetFacing().fX == 1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("FireRight");
		}
	}
	else if( GetFacing().fX == -1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("FireLeft");
		}
	}
	else if( GetFacing().fY == 1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("FireDown");
		}
	}
	else if( GetFacing().fY == -1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("FireUp");
		}
	}
}

void CEnemy::Walk(void)
{
	if( GetFacing().fX == 1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("WalkRight");
		}
	}
	else if( GetFacing().fX == -1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("WalkLeft");
		}
	}
	else if( GetFacing().fY == 1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("WalkDown");
		}
	}
	else if( GetFacing().fY == -1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("WalkUp");
		}
	}
}