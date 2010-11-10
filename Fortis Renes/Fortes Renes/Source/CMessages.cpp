//////////////////////////////////////////////////////////////////////////////
// File: "CMessages.cpp"
//
// Date Edited: 10/19/2010
//
// Purpose: To fill the functions created in the CMessages.h header file
//
//////////////////////////////////////////////////////////////////////////////

// Includes for files needed by the functions
#include "CMessages.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CObjectManager.h"
#include "CEnemy.h"

////////////////////////////////////////////////////////
// Function: CCreatePlayerBullet (Constructor)
// Paramaters: CPlayer* pPlayer - player that fired the bullet
// Returns: void
////////////////////////////////////////////////////////
CCreatePlayerBullet::CCreatePlayerBullet( CPlayer* pPlayer ) : CBaseMessage( MSG_CREATE_PLAYER_BULLET )
{
	m_pPlayer = pPlayer;	// Hold onto the pointer to the player
	m_pPlayer->AddRef();	// Add one to the players reference count
}

////////////////////////////////////////////////////////
// Function: ~CCreatePlayerBullet (Destructor)
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
CCreatePlayerBullet::~CCreatePlayerBullet( void )
{
	m_pPlayer->Release();	// Reduce reference count
}

// Constructor 
CCreateEnemyBullet::CCreateEnemyBullet( CBase* pEnemy ) : CBaseMessage( MSG_CREATE_ENEMY_BULLET )
{
	m_pEnemy = pEnemy;
	pEnemy->AddRef();
}

// Destructor
CCreateEnemyBullet::~CCreateEnemyBullet(void)
{
}

////////////////////////////////////////////////////////
// Function: CDestroyBullet (Constructor)
// Paramaters: CBullet* pBullet - pointer to the bullet getting destroyed
// Returns: void
////////////////////////////////////////////////////////
CDestroyBullet::CDestroyBullet( CBullet* pBullet ) : CBaseMessage( MSG_DESTROY_BULLET )
{
	m_pBullet = pBullet;	// Hold onto the bullet
	m_pBullet->AddRef();	// Add to the reference count
}

////////////////////////////////////////////////////////
// Function: ~CDestroyBullet (Destructor)
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
CDestroyBullet::~CDestroyBullet( void )
{
	m_pBullet->Release();	// Reduce reference count
}
////////////////////////////////////////////////////////
// Function: CTesterMedPack (Constructor)
// Paramaters: CPlayer* pPlayer - player 
// Returns: void
////////////////////////////////////////////////////////
CTesterMedPack::CTesterMedPack( CPlayer* pPlayer ) : CBaseMessage( MSG_TESTER_MEDPACK )
{
	m_pPlayer = pPlayer;	// Hold onto the pointer to the player
	m_pPlayer->AddRef();	// Add one to the players reference count
}

////////////////////////////////////////////////////////
// Function: ~CTesterMedPack (Destructor)
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
CTesterMedPack::~CTesterMedPack( void )
{
	m_pPlayer->Release();	// Reduce reference count
}

////////////////////////////////////////////////////////
// Function: CDestroyConsumable (Constructor)
// Paramaters: CConsumable* pConsumable - pointer to the consumable getting destroyed
// Returns: void
////////////////////////////////////////////////////////
CDestroyConsumable::CDestroyConsumable( CConsumable* pConsumable ) : CBaseMessage( MSG_DESTROY_CONSUMABLE )
{
	m_pConsumable = pConsumable;	// Hold onto the bullet
	m_pConsumable->AddRef();	// Add to the reference count
}

////////////////////////////////////////////////////////
// Function: ~CDestroyConsumable (Destructor)
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
CDestroyConsumable::~CDestroyConsumable( void )
{
	m_pConsumable->Release();	// Reduce reference count
}