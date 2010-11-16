#ifndef CBASE_H_
#define CBASE_H_

#include <windows.h>

#include "CAnimationManager.h"
#include "tAnimationInstance.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "IListener.h"

enum eWeaponTypes { WEP_PISTOL = 0, WEP_MACHINEGUN, WEP_RIFLE, WEP_SHOTGUN, WEP_BAZOOKA, WEP_RYNOV, WEP_NUMBER };
enum eBulletTypes { BUL_BULLET = 0, BUL_ROCKET, BUL_NUMBER };
enum eConsumableTypes { CON_HEALTH = 0, CON_ADRENALINE, CON_AMMO, CON_NUMBER };
enum Objects { OBJECT_BASE = 0, OBJECT_PLAYER, OBJECT_ENEMY, OBJECT_BULLET, OBJECT_ROCKET, OBJECT_CONSUMABLE, OBJECT_JEEP, OBJECT_TANK, OBJECT_ALLY, OBJECT_BOSS, OBJECT_BOMB, OBJECT_CURSOR, OBJECT_GATE, NUM_OBJECTS };

class CTile;

class CBase : public IListener
{
private:
	unsigned int m_uiRefCount;	// how many objects 
								// have a pointer to me.
	// position
	float	m_fPosX;
	float	m_fPosY;

	// velocity
	float	m_nVelX;
	float	m_nVelY;

	// image
	int		m_nImageID;
	int		m_nWidth;
	int		m_nHeight;

	bool	m_bCull;
	
	int m_nHealth;
	int m_nMaxHealth;
	tAnimationInstance* m_pAnimation;
	int m_nObjectID;
	int m_nLayer;
	int m_nArmor;

	bool m_bCoverObject;
	bool m_bDestructable;

protected:
	int		m_nType;
public:


	//////////////////////////////////
	// Function: "CBase"
	//
	// Purpose: Default Constructor
	//////////////////////////////////
	CBase(void);
	//////////////////////////////////
	// Function: "~CBase"
	//
	// Purpose: Clean up memory
	//////////////////////////////////
	virtual ~CBase(void);

	///////////////////////////////////////////////////////
	// Functions: "Accessors"
	//
	// Purpose: To get the specified type
	///////////////////////////////////////////////////////
	float GetPosX(void)	 { return m_fPosX; }
	float GetPosY(void)	 { return m_fPosY; }
	float GetVelX(void)	 { return m_nVelX; }
	float GetVelY(void)	 { return m_nVelY; }
	int GetLayer(void)	 { return m_nLayer; }
	int GetImageID(void) { return m_nImageID; }
	int GetType(void)	 { return m_nType; }
	int GetWidth(void)	 { return m_nWidth; }
	int GetHeight(void)	 { return m_nHeight; }
	int GetHealth(void)	 { return m_nHealth; }
	int GetMaxHealth(void) { return m_nMaxHealth; }
	int GetArmor(void) { return m_nArmor; }
	tAnimationInstance* GetAnimation(void) { return m_pAnimation; }

	bool IsCoverObject(void) { return m_bCoverObject; }
	bool IsDestructable(void) { return m_bDestructable; }
	bool GetCull(void) { return m_bCull; }

	virtual RECT GetRect(void);

	///////////////////////////////////////////////////////
	// Function: "Modifiers"
	//
	// Purpose: To set the specified type
	///////////////////////////////////////////////////////
	void SetPosX(float fPosX)		{ 
		if(m_fPosX != fPosX && m_nType == OBJECT_ALLY)
										m_fPosX =0;
										m_fPosX = fPosX;
	}
	void SetPosY(float fPosY)		{ m_fPosY = fPosY; }
	void SetVelX(float nVelX)		{ m_nVelX = nVelX; }
	void SetVelY(float nVelY)		{ m_nVelY = nVelY; }
	void SetLayer(int nLayer)		{ m_nLayer = nLayer; }
	void SetImageID( int nImageID)	{ m_nImageID = nImageID; }
	void SetWidth(int nWidth)		{ m_nWidth = nWidth; }
	void SetHeight(int nHeight)		{ m_nHeight = nHeight; }
	void SetHealth(int nHealth)		{ m_nHealth = nHealth; }
	void SetMaxHealth(int nMaxHealth){ m_nMaxHealth = nMaxHealth; }
	void SetAnimation(tAnimationInstance* pAnimation){ m_pAnimation = pAnimation; }
	void SetType(int nType)			{ m_nType = nType; }
	void SetArmor(int nArmor) { m_nArmor = nArmor; }
	void SetCurrAnimation(const char* szAnimationName);
	void SetCoverObject(bool cover) { m_bCoverObject = cover; }
	void SetDestructable(bool destroy) { m_bDestructable = destroy; }
	virtual void SetCull(bool bCull) { m_bCull = bCull; }

	///////////////////////////////////////////////////////
	// Function: "Update"
	//
	// Purpose: Update objects and get input if nessisary
	//////////////////////////////////////////////////////
	virtual void Update(float);

	///////////////////////////////////////////////////////
	// Function: Render
	//
	// Purpose: Draw objects to the screen
	///////////////////////////////////////////////////////
	virtual void Render(float fCamPosX, float fCamPosY);

	//////////////////////////////////////////////////////
	// Function: "CheckCollision"
	//
	// Purpose: Checks against other objects for collision
	//////////////////////////////////////////////////////
	bool CheckCollision( CBase *pBase, RECT *collision );

	//////////////////////////////////////////////////////
	// Function: "CheckCollision"
	//
	// Purpose: Checks against other objects for collision
	//////////////////////////////////////////////////////
	virtual bool CheckCollision( CBase *pBase );

	//////////////////////////////////////////////////////
	// Function: "CheckTerrain"
	//
	// Purpose: Checks if terrain is traversable
	//////////////////////////////////////////////////////
	virtual bool CheckTerrain( CTile *pTile );
	//////////////////////////////////////////////////////
	// Function: "AddRef"
	//
	// Purpose: To help keep track of objects which have
	//			pointers to this object
	//////////////////////////////////////////////////////
	void AddRef(void){ m_uiRefCount++; }

	//////////////////////////////////////////////////////
	// Function: "Release"
	//
	// Purpose: If there are no current pointers to this
	//			object it will delete itself
	/////////////////////////////////////////////////////
	void Release(void)
	{
		m_uiRefCount--;
		if( m_uiRefCount == 0 )
			delete this;
	}
	virtual void HandleEvent( CEvent* pEvent );
};

void SetCurrAnimation(const char* szAnimationName);
#endif