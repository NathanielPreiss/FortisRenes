#ifndef CPLAYER_H_
#define CPLAYER_H_

#include <windows.h>

#include "DirectX Wrappers/SGD_Math.h"

#include "CBase.h"
#include "IPlayerState.h"
#include "CInventory.h"
#include "CConsumable.h"
#include "CWeapon.h"

class IPlayerState;
class CJeep;
class CTank;

class CPlayer : public CBase
{
private:
	vector<CWeapon*> m_pWeapon;
	int m_nCurrentWeapon;
	CInventory m_Inventory;
	int m_nCurrentItem;
	int m_nMoney;
	int m_nRep;
	int m_nNumWeapons;
	bool m_bMoving;
	bool m_bFiring;
	unsigned char m_chResearchArmorLevel;
	unsigned char m_chResearchWeaponLevel;
	unsigned char m_chResearchConsumableLevel;
	unsigned char m_chProgress;
	IPlayerState* m_pPlayerState;
	CTank* m_pTempTank;
	CJeep* m_pTempJeep;

	bool m_bCanTalk;

	bool m_bConActive;
	float m_fConsumableTimer;
	float m_fTimeBucket;
	
	int m_nSpeed;
	// normalized vector of the direction the player is facing.
	tVector2D m_vFacingNormal;

	
	CPlayer(void);
	~CPlayer(void);

public:
	// 
	static CPlayer* GetInstance(void);

	void SaveProfile(void);
	// Load the player from xml
	void LoadProfile(void);

	// New Player profile
	void NewPlayer(void);
	// Uload the player to clean memory
	void ClosePlayer(void);

	bool CheckCollision(CBase* pBase );
	RECT GetRect(void);
	
	void HandleEvent( CEvent* pEvent );

	CWeapon* GetCurrWeapon(void) 
	{
		if( (unsigned int)m_nCurrentWeapon < m_pWeapon.size() )
			return m_pWeapon[m_nCurrentWeapon];
		else
			return NULL;
	}

	void NextWeapon(void);
	void PrevWeapon(void);
	void NextItem(void);

	CInventory* GetInventory(void) { return &m_Inventory; }
	int GetCurrItem(void)	{ return m_nCurrentItem; }
	int GetSpeed(void)		{ return m_nSpeed; }
	IPlayerState* GetPlayerState(void) { return m_pPlayerState; }
	CTank* GetTempTank(void) { return m_pTempTank; }
	CJeep* GetTempJeep(void) { return m_pTempJeep; }
	int GetNumWeapons(void) { return m_nNumWeapons; }
	int GetMoney(void) { return m_nMoney; }
	int GetRep(void) { return m_nRep; }
	bool SpendMoney(int nSpendingAmount); 
	void AddWeapon(int nWeapon);
	unsigned char GetResearchArmorLevel(void) { return m_chResearchArmorLevel; }
	unsigned char GetResearchWeaponLevel(void) { return m_chResearchWeaponLevel; }
	unsigned char GetResearchConsumableLevel(void) { return m_chResearchConsumableLevel; }
	void UpgradeResearchArmorLevel(void) { m_chResearchArmorLevel++; }
	void UpgradeResearchWeaponLevel(void) { m_chResearchWeaponLevel++; }
	void UpgradeResearchConsumableLevel(void) { m_chResearchConsumableLevel++; }
	tVector2D& GetFacing(void) { return m_vFacingNormal; }
	unsigned char GetProgress(void) { return m_chProgress; }
	IPlayerState* GetState(void) { return m_pPlayerState; }
	CWeapon* GetWeapon(int nWeaponID) { return m_pWeapon[nWeaponID]; }
	bool GetTalkBool(void) { return m_bCanTalk; }
	bool GetIfFiring(void) { return m_bFiring; }
	bool GetIfMoving(void) { return m_bMoving; }
	void SetIfFiring(bool bFiring) { m_bFiring = bFiring; }
	void SetIfMoving(bool bMoving) { m_bMoving = bMoving; }

	void SetFacing(float x, float y) { m_vFacingNormal.fX = x; m_vFacingNormal.fY = y; }
	void SetPlayerState(IPlayerState* pPlayerState) { m_pPlayerState = pPlayerState; }
	void SetCurrentWeapon(int nCurrentWeapon) { m_nCurrentWeapon = nCurrentWeapon; }
	void LevelFinished(void);
	void SetMoney(int nMoney) { m_nMoney = nMoney; }
	void SetRep(int nRep) { m_nRep = nRep; }
	void SetTalkBool(bool bCanTalk) { m_bCanTalk = bCanTalk; }

	void Update(float fElapsedTime);
	void Render(float fCamPosX, float fCamPosY);
	void ChangeState( IPlayerState* newState );

	void Walk(void);
	void Shoot(void);
	void Idle(void);
	
};
#endif