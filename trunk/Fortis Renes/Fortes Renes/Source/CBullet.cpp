#include <windows.h>
#include <cmath>

#include "CBullet.h"
#include "CEventSystem.h"
#include "CMessageSystem.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "CMessages.h"
#include "CEvent.h"
#include "CGamePlayState.h"


CBullet::CBullet( void )
{
	SetCoverObject(false);
	m_nType = OBJECT_BULLET;

	SetHeight(8);
	SetWidth(8);

	m_fRotation = 0.0f;
	m_pOwner = NULL;

	SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture( "Resource/Graphics/NaP_Bullet.png" ));
}

CBullet::~CBullet(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture( GetImageID() );
}

void CBullet::Update(float fElapsedTime )
{
	CBase::Update(fElapsedTime);

	if( GetPosX() - GetWidth()*0.5f < 0 || GetPosY() - GetHeight()*0.5f < 0 )
		CMessageSystem::GetInstance()->SendMsg( new CDestroyBullet(this) );
}

void CBullet::Render(float fCamPosX, float fCamPosY)
{
	CSGD_TextureManager::GetInstance()->Draw( GetImageID(), (int)((GetPosX() - GetWidth()*0.5f)-fCamPosX),
											  (int)((GetPosY()-GetHeight()*0.5f)-fCamPosY), 1, 1, 0, 
											  (float)(GetWidth()*0.5f), (float)(GetHeight()*0.5f), GetRotation() );
}

RECT CBullet::GetRect(void)
{
	RECT collisionRect;
	collisionRect.left = LONG(GetPosX() - GetWidth()*0.5f);
	collisionRect.top =LONG(GetPosY() - GetHeight()*0.5f);
	collisionRect.right = LONG(GetPosX() + GetWidth()*0.5f);
	collisionRect.bottom = LONG(GetPosY() + GetHeight()*0.5f);

	return collisionRect;
}

bool CBullet::CheckCollision(CBase* pBase )
{

	RECT collision;
	if( CBase::CheckCollision( pBase, &collision ) )
	{
		if(pBase->IsDestructable())
		{
			CMessageSystem::GetInstance()->SendMsg(new CDestroyBase(pBase));
			CMessageSystem::GetInstance()->SendMsg(new CDestroyBullet(this));
			CEventSystem::GetInstance()->SendEvent("generator.destroyed",pBase);
			return true;
		}

		if( pBase->GetType() == OBJECT_BASE )
		{
			CMessageSystem::GetInstance()->SendMsg(new CDestroyBullet(this));
			return true;
		}

		if( pBase->GetType() == OBJECT_BOMB )
		{	
			pBase->SetHealth(-1);
			CMessageSystem::GetInstance()->SendMsg(new CDestroyBullet(this));
			return true;
		}
	}
	return false;
}

void CBullet::HandleEvent(CEvent* pEvent)
{
}