//////////////////////////////////////////////////////////////////////////////
// File: "CMessages.h"
//
// Date Edited: 10/19/2010
//
// Purpose: File Contains all messages that can occur 
//
//////////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef _CMESSAGES_H
#define _CMESSAGES_H

typedef int MSGID;

// Forward declarations
class CBullet;
class CBase;
class CPlayer;
class CConsumable;
class CEnemy;

// Enum for all message types available
enum eMsgTypes { MSG_NULL = 0, MSG_CREATE_PLAYER_BULLET, MSG_DESTROY_BULLET, MSG_TESTER_MEDPACK, MSG_DESTROY_CONSUMABLE, MSG_CREATE_BASE_OBJECT, MSG_CREATE_ENEMY_BULLET, MSG_CREATE_CONSUMABLE, MSG_CREATE_LIGHTINFANTRY, MSG_CREATE_HEAVYINFANTRY, MSG_CREATE_MEDIUMINFANTRY, MSG_CREATE_HELICOPTER, MSG_CREATE_ENEMY_TANK, MSG_CREATE_TANK, MSG_CREATE_JEEP, MSG_CREATE_ALLY, MSG_DESTROY_ENEMY, MSG_CREATE_BOSS, MSG_DESTROY_BASE, MSG_CREATE_GATE, MSG_MAX };

//////////////////////////////////////////////////////////////////////////////
//	Class: CBaseMessage
//
//	Notes: Base type for all messages
//////////////////////////////////////////////////////////////////////////////
class CBaseMessage
{
private:
	// Message ID to tell them appart
	MSGID	m_msgID;

public:
	// Constructor
	CBaseMessage(MSGID msgID)
	{
		m_msgID = msgID;
	}
	// Destructor
	virtual ~CBaseMessage(void){}

	// Accessors
	MSGID GetMsgID(void) { return m_msgID; }

};

//////////////////////////////////////////////////////////////////////////////
//	Class: CCreateBullet
//
//	Notes: Message to create bullets the player shoots
//////////////////////////////////////////////////////////////////////////////
class CCreatePlayerBullet : public CBaseMessage
{
	// Pointer to the player
	CPlayer*	m_pPlayer;

public:
	// Constructor 
	CCreatePlayerBullet( CPlayer* m_pPlayer );
	// Destructor
	~CCreatePlayerBullet(void);

	// Accessors
	CPlayer* GetPlayer(void) { return m_pPlayer; }
};

class CCreateEnemyBullet : public CBaseMessage
{
	// Pointer to the player
	CBase*	m_pEnemy;

public:
	// Constructor 
	CCreateEnemyBullet( CBase* m_pEnemy );
	// Destructor
	~CCreateEnemyBullet(void);

	// Accessors
	CBase* GetEnemy(void) { return m_pEnemy; }
};

//////////////////////////////////////////////////////////////////////////////
//	Class: CDestroyBullet
//
//	Notes: Destroys any bullet that gets the message
//////////////////////////////////////////////////////////////////////////////
class CDestroyBullet : public CBaseMessage
{
	// Pointer to the bullet
	CBullet* m_pBullet;

public:
	// Constructor
	CDestroyBullet( CBullet* pBullet );
	// Destructor
	~CDestroyBullet(void);

	// Accessors
	CBullet* GetBullet(void) { return m_pBullet; }
};

//////////////////////////////////////////////////////////////////////////////
//	Class: CTesterMedPack
//
//	Notes: Creates medpack just above the player
//////////////////////////////////////////////////////////////////////////////
class CTesterMedPack : public CBaseMessage
{
	// Pointer to the bullet
	CPlayer* m_pPlayer;

public:
	// Constructor
	CTesterMedPack( CPlayer* m_pPlayer );
	// Destructor
	~CTesterMedPack(void);

	// Accessors
	CPlayer* GetPlayer(void) { return m_pPlayer; }
};
//////////////////////////////////////////////////////////////////////////////
//	Class: CDestroyBullet
//
//	Notes: Destroys any bullet that gets the message
//////////////////////////////////////////////////////////////////////////////
class CDestroyConsumable : public CBaseMessage
{
	// Pointer to the bullet
	CConsumable* m_pConsumable;

public:
	// Constructor
	CDestroyConsumable( CConsumable* pConsumable );
	// Destructor
	~CDestroyConsumable(void);

	// Accessors
	CConsumable* GetConsumable(void) { return m_pConsumable; }
};

class CCreateBaseObject : public CBaseMessage
{
	float	m_fPosX;
	float	m_fPosY;

	// image
	int		m_nImageID;
	int		m_nWidth;
	int		m_nHeight;

	bool	m_bCoverObject;
	bool	m_bDestructable;
	
	int m_nObjectID;

public:
	CCreateBaseObject( float fPosX, float fPosY, int nImageID, int nWidth, int nHeight, int nObjectID, bool bCoverObject = false, bool bDestructable = false ) : CBaseMessage(MSG_CREATE_BASE_OBJECT)
	{
		m_fPosX = fPosX;
		m_fPosY = fPosY;
		m_nImageID = nImageID;
		m_nWidth = nWidth;
		m_nHeight = nHeight;
		m_nObjectID = nObjectID;
		m_bCoverObject = bCoverObject;
		m_bDestructable = bDestructable;
	}
	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
	int GetImageID() { return m_nImageID; }
	int GetWidth() { return m_nWidth; }
	int GetHeight() { return m_nHeight; }
	int GetObjectID() { return m_nObjectID; }
	bool GetCoverBool() { return m_bCoverObject; }
	bool GetDestructableBool() { return m_bDestructable; }
};

class CCreateConsumable : public CBaseMessage
{
	float m_fPosX;
	float m_fPosY;

	int m_nItemID;
public:
	CCreateConsumable( float fPosX, float fPosY, int nItemID ) : CBaseMessage(MSG_CREATE_CONSUMABLE)
	{
		m_fPosX = fPosX;
		m_fPosY = fPosY;

		m_nItemID = nItemID;
	}
	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
	int GetItemId() { return m_nItemID; }
};

class CCreateLightInfantry : public CBaseMessage
{
	float m_fPosX;
	float m_fPosY;
public:
	CCreateLightInfantry( float fPosX, float fPosY ) : CBaseMessage(MSG_CREATE_LIGHTINFANTRY)
	{
		m_fPosX = fPosX;
		m_fPosY = fPosY;
	}

	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
};

class CCreateMediumInfantry : public CBaseMessage
{
	float m_fPosX;
	float m_fPosY;
public:
	CCreateMediumInfantry( float fPosX, float fPosY ) : CBaseMessage(MSG_CREATE_MEDIUMINFANTRY)
	{
		m_fPosX = fPosX;
		m_fPosY = fPosY;
	}

	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
};

class CCreateHeavyInfantry : public CBaseMessage
{
	float m_fPosX;
	float m_fPosY;
public:
	CCreateHeavyInfantry( float fPosX, float fPosY ) : CBaseMessage(MSG_CREATE_HEAVYINFANTRY)
	{
		m_fPosX = fPosX;
		m_fPosY = fPosY;
	}

	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
};

class CCreateBoss : public CBaseMessage
{
	int m_nNumber;
	float m_fPosX;
	float m_fPosY;
public:
	CCreateBoss( float fPosX, float fPosY, int nNumber ) : CBaseMessage(MSG_CREATE_BOSS)
	{
		m_nNumber = nNumber;
		m_fPosX = fPosX;
		m_fPosY = fPosY;
	}

	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
	int GetNumber() { return m_nNumber; }
};

class CCreateHelicopter : public CBaseMessage
{
	float m_fPosX;
	float m_fPosY;
	float m_fVelX;
	float m_fVelY;
public:
	CCreateHelicopter( float fPosX, float fPosY, float fVelX, float fVelY ) : CBaseMessage(MSG_CREATE_HELICOPTER)
	{
		m_fPosX = fPosX;
		m_fPosY = fPosY;
		m_fVelX = fVelX;
		m_fVelY = fVelY;
	}

	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
	float GetVelX() { return m_fVelX; }
	float GetVelY() { return m_fVelY; }
};

class CCreateJeep : public CBaseMessage
{
	float m_fPosX;
	float m_fPosY;
public:
	CCreateJeep( float fPosX, float fPosY ) : CBaseMessage(MSG_CREATE_JEEP)
	{
		m_fPosX = fPosX;
		m_fPosY = fPosY;
	}

	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
};

class CCreateEnemyTank : public CBaseMessage
{
	float m_fPosX;
	float m_fPosY;
public:
	CCreateEnemyTank( float fPosX, float fPosY ) : CBaseMessage(MSG_CREATE_ENEMY_TANK)
	{
		m_fPosX = fPosX;
		m_fPosY = fPosY;
	}

	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
};

class CCreateTank : public CBaseMessage
{
	float m_fPosX;
	float m_fPosY;
public:
	CCreateTank( float fPosX, float fPosY ) : CBaseMessage(MSG_CREATE_TANK)
	{
		m_fPosX = fPosX;
		m_fPosY = fPosY;
	}

	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
};

class CCreateAlly : public CBaseMessage
{
	float m_fPosX;
	float m_fPosY;
	bool m_bHostage;
public:
	CCreateAlly( float fPosX, float fPosY, bool bHostage = false) : CBaseMessage(MSG_CREATE_ALLY)
	{
		m_fPosX = fPosX;
		m_fPosY = fPosY;
		m_bHostage = bHostage;
	}

	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
	bool GetHostage() { return m_bHostage; }
};

class CDestroyEnemy : public CBaseMessage
{
	CEnemy* m_pEnemy;
public:
	CDestroyEnemy(CEnemy* pEnemy) : CBaseMessage(MSG_DESTROY_ENEMY)
	{
		m_pEnemy = pEnemy;
	}

	CEnemy* GetEnemy(void) {return m_pEnemy;}
};

class CDestroyBase : public CBaseMessage
{
	CBase* m_pBase;
public:
	CDestroyBase(CBase* pBase) : CBaseMessage(MSG_DESTROY_BASE)
	{
		m_pBase = pBase;
	}

	CBase* GetBase(void) {return m_pBase;}
};

class CCreateGate : public CBaseMessage
{
	int m_nPosX;
	int m_nPosY;
	int m_nImageID;
	int m_nWidth;
	int m_nHeight;

public:
	CCreateGate(int nPosX, int nPosY, int nImageID, int nWidth, int nHeight) : CBaseMessage(MSG_CREATE_GATE)
	{
		m_nPosX = nPosX;
		m_nPosY = nPosY;
		m_nImageID = nImageID;
		m_nWidth = nWidth;
		m_nHeight = nHeight;
	}

	int GetPosX(void) { return m_nPosX; }
	int GetPosY(void) { return m_nPosY; }
	int GetImadeID(void) { return m_nImageID; }
	int GetWidth(void) { return m_nWidth; }
	int GetHeight(void) { return m_nHeight; }
};

#endif