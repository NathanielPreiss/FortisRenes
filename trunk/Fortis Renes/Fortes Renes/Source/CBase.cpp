//////////////////////////////////////////////////////////////////////////////
// File: "CBase.cpp"
//
// Date Edited: 10/14/2010
//
// Purpose: To define functions declared in header
//////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "CBase.h"
#include "CTile.h"
#include "CEventSystem.h"
#include "CPlayer.h"
#include "CTankState.h"
#include "CJeepState.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"

////////////////////////////////////////////////////////
// Function: "CBase"
//
// Paramaters: void
//
// Returns: void
////////////////////////////////////////////////////////
CBase::CBase(void) : m_nType(OBJECT_BASE)
{
	SetCoverObject(false);
	SetDestructable(false);
	// object knows about self
	m_uiRefCount = 1;

	m_bCoverObject = false;
	m_fPosX = 0;
	m_fPosY = 0;
	m_nVelX = 0;
	m_nVelY = 0;
	m_nImageID = -1;

	m_pAnimation = NULL;
	m_nLayer = 0;
	// Comment in this line to check to make sure that all objects are having
	// their layer set like they should
	// m_nLayer = -1;
	CEventSystem::GetInstance()->RegisterClient("Change_Position", this);
	CEventSystem::GetInstance()->RegisterClient("Spawn_Jeep", this);
	CEventSystem::GetInstance()->RegisterClient("Spawn_Tank", this);
	CEventSystem::GetInstance()->RegisterClient("need.cover", this);
}
////////////////////////////////////////////////////////
// Function: "~CBase"
//
// Paramaters: void
//
// Returns: void
////////////////////////////////////////////////////////
CBase::~CBase(void)
{
	if(GetAnimation() != NULL)
		CAnimationManager::GetInstance()->UnloadAnimation(GetAnimation());
	CEventSystem::GetInstance()->UnregisterClient("Change_Position", this);
	CEventSystem::GetInstance()->UnregisterClient("Spawn_Jeep", this);
	CEventSystem::GetInstance()->UnregisterClient("Spawn_Tank", this);
	CEventSystem::GetInstance()->UnregisterClient("need.cover", this);
}
////////////////////////////////////////////////////////
// Function: "Update"
//
// Paramaters: (float) fElapsedTime - Allows for time
//						based updates rather than frame
//
// Returns: void
void CBase::Update(float fElapsedTime)
{
	// Moves the object by its velocity
	SetPosX( GetPosX() + (GetVelX() * fElapsedTime));
	SetPosY( GetPosY() + (GetVelY() * fElapsedTime));

	//if(m_pAnimation != NULL)
		//m_pAnimation->Update(fElapsedTime);
}
////////////////////////////////////////////////////////
// Function: "Render"
//
// Paramaters: void
//
// Returns: void
////////////////////////////////////////////////////////
void CBase::Render(float fCamPosX, float fCamPosY)
{
	// Draws the object at its position
	//if(m_pAnimation->currSheet != NULL)
	//	m_pAnimation->Render((int)(GetPosX() - fCamPosX), (int)(GetPosY() - fCamPosY), 1.0f, 1.0f);
	//else

	//RECT tempRect = GetRect();
	//tempRect.top -= fCamPosY;
	//tempRect.left -= fCamPosX;
	//tempRect.right = tempRect.left + GetWidth();
	//tempRect.bottom = tempRect.top + GetHeight();

		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)((GetPosX() - GetWidth()*0.5f) - fCamPosX), 
			(int)((GetPosY() - GetHeight() *0.5f) - fCamPosY), 1.0f, 1.0f, 0, GetWidth()*0.5f, GetHeight()*0.5f, 0);

		//CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
		//CSGD_Direct3D::GetInstance()->DrawRect(tempRect, 0,255,0);
}
////////////////////////////////////////////////////////
// Function: "GetRect"
//
// Paramaters: void
//
// Returns: (RECT) thisRect - Collision rectangle of the object
///////////////////////////////////////////////////////
RECT CBase::GetRect(void)
{
//	if( GetAnimation() != NULL )
//	{
//		return GetAnimation()->currFrame->rCollision;
//	}

	RECT collisionRect;
	collisionRect.left = (LONG)(GetPosX() - GetWidth() * 0.5f);
	collisionRect.top = (LONG)(GetPosY() - GetHeight() * 0.5f);
	collisionRect.right = collisionRect.left + GetWidth();
	collisionRect.bottom  = collisionRect.top + GetHeight();

	return collisionRect;
}
//////////////////////////////////////////////////////
// Function: "CheckCollision"
//
// Paramaters: (CBase*) pBase - Pointer to another CBase
//				object and checks if they are colliding
//
// Returns: (bool) true - if they are colliding
//			(bool) false - if they are not colliding
//////////////////////////////////////////////////////
bool CBase::CheckCollision( CBase *pBase, RECT *collision )
{
	if( IntersectRect( collision, &GetRect(), &pBase->GetRect() ) )
	{
		// They are colliding
		return true;
	}
	// They are not colliding
	return false;
}
//////////////////////////////////////////////////////
// Function: "CheckCollision"
//
// Paramaters: (CBase*) pBase - Pointer to another CBase
//				object and checks if they are colliding
//
// Returns: (bool) true - if they are colliding
//			(bool) false - if they are not colliding
//////////////////////////////////////////////////////
bool CBase::CheckCollision( CBase *pBase )
{
	RECT temp;
	if( IntersectRect( &temp, &GetRect(), &pBase->GetRect() ) )
	{
		// They are colliding
		return true;
	}
	// They are not colliding
	return false;
}
//////////////////////////////////////////////////////
// Function: "CheckTerrain"
//
// Paramaters: (CTile*) pTile - Pointer to tile to check
//								if it is traversable
//
// Returns: (bool) true - if they are colliding
//			(bool) false - if they are not colliding
//////////////////////////////////////////////////////
bool CBase::CheckTerrain( CTile *pTile )
{
	RECT temp;
	if( IntersectRect( &temp, &GetRect(), &pTile->GetRect() ) )
	{
		// They are colliding
		return true;
	}
	// They are not colliding
	return false;
}

void CBase::HandleEvent( CEvent* pEvent )
{
	if( pEvent->GetEventID() == "need.cover" && m_bCoverObject == true )
	{
		CEventSystem::GetInstance()->SendEvent("over.here",this);
	}
}

void CBase::SetCurrAnimation(const char* szAnimationName)
{
	if( strcmp(this->m_pAnimation->currAnimation->szName,szAnimationName) == 0 )
	{
		return;
	}

	GetAnimation()->currAnimation->Stop();
	GetAnimation()->currAnimation->Reset();

	for( unsigned int count = 0; count < GetAnimation()->currSheet->m_vAnimations.size(); count++ )
	{
		if( strcmp(GetAnimation()->currSheet->m_vAnimations[count]->szName, szAnimationName) == 0 )
		{
			GetAnimation()->currAnimation = GetAnimation()->currSheet->m_vAnimations[count];
			break;
		}
	}

	GetAnimation()->currAnimation->Reset();
	GetAnimation()->currAnimation->Play();
}