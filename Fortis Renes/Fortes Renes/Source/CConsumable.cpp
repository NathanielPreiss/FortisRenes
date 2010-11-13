//////////////////////////////////////////////////////////////////////////////
// File: "CConsumable.cpp"
//
// Date Edited: 10/19/2010
//
// Purpose: 
//
//////////////////////////////////////////////////////////////////////////////

// Nessisary header includes
#include "CConsumable.h"
#include "CCamera.h"
#include "CEventSystem.h"
#include "CMessageSystem.h"

////////////////////////////////////////////////////////
// Function: Constructor
// Paramaters: int nItemID - Which item is it
// Returns: void
////////////////////////////////////////////////////////
CConsumable::CConsumable(int nItemID)
{
	SetType(OBJECT_CONSUMABLE);
	SetItemID(nItemID);
	switch(nItemID)
	{
	case CON_ADRENALINE:
		SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/pill.png"));
		SetWidth(32);
		SetHeight(32);
		break;
	case CON_HEALTH:
		SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Medkit.png"));
		SetWidth(32);
		SetHeight(32);
		break;
	case CON_AMMO:
		SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/ammo.png"));
		SetWidth(32);
		SetHeight(32);
		break;
	}
	CEventSystem::GetInstance()->RegisterClient("picked_up", this);
	m_nItemID = nItemID;
}
////////////////////////////////////////////////////////
// Function: ~CConsumable
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
CConsumable::~CConsumable(void)
{
	CEventSystem::GetInstance()->UnregisterClient("picked_up", this);
	if( GetImageID() != -1 )
		CSGD_TextureManager::GetInstance()->UnloadTexture(GetImageID());
}
void CConsumable::Render(float fCamPosX, float fCamPosY)
{
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX() - (GetWidth() * 0.5f) - CCamera::GetInstance()->GetPosX()),
											(int)(GetPosY() - (GetHeight() * 0.5f) - CCamera::GetInstance()->GetPosY()));
}

RECT CConsumable::GetRect(void)
{
	RECT collisionRect;
	collisionRect.left = LONG(GetPosX() - GetWidth() * 0.5f);
	collisionRect.top = LONG(GetPosY() - GetHeight() * 0.5f);
	collisionRect.right = LONG(collisionRect.left + GetWidth());
	collisionRect.bottom  = LONG(collisionRect.top + GetHeight());

	return collisionRect;
}
void CConsumable::HandleEvent(CEvent* pEvent)
{
	if( pEvent->GetEventID() == "picked_up" && pEvent->GetParam() == this )
	{
		CMessageSystem::GetInstance()->SendMsg( new CDestroyConsumable( this ) );
	}
}