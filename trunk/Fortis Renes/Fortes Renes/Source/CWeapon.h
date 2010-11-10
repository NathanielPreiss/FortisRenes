#ifndef CWEAPON_H_
#define CWEAPON_H_

#include "CBase.h"

class CWeapon : public CBase
{
private:
	int m_nWeaponID;	// Weapon ID based off enum
	int m_nBulletID;	// Bullet ID based off enum
	int m_nDamage;		// Base damage of this gun
	int m_nRange;		// How far bullets travel
	int m_nMaxMagazine; // Rounds per magazine
	int m_nCurrMagazine;// Rounds currently in magazine
	int m_nMaxAmmo;		// Max ammo that can be carried
	int m_nCurrAmmo;	// Current ammo held
	int m_nBulletSpeed;	// Speed of bullet fired
	int m_nNumBulletsFired; // How many shots fired per shot
	int m_nSoundDistance;// Distance sound travels to alert enemies
	float m_fRateOfFire; // How quick weapon fires
	float m_fReloadTime;// How long it takes for a player to reload
	float m_fAccuracy;	 // Angle of innacuracy
	float m_fFireDelayTimer;
	float m_fReloadTimer;
public:
	CWeapon(void);
	CWeapon(int nWeapon);
	~CWeapon(void) {}
	//void Render(float fCamPosX, float fCamPosY);
	void Update(float fElapsedTime);
	void LoadWeapon(int nWeapon);
	void FireWeapon(CBase *pShooter);

	void SetAmmo(int nAmmo)		{ m_nCurrAmmo = nAmmo; if(m_nCurrAmmo > m_nMaxAmmo)m_nCurrAmmo = m_nMaxAmmo; }

	int GetWeaponID(void)		{ return m_nWeaponID; }
	int GetBulletID(void)		{ return m_nBulletID; }
	int GetDamage(void)			{ return m_nDamage; }	
	int GetRange(void)			{ return m_nRange; }
	int GetMaxMagazine(void)	{ return m_nMaxMagazine; }
	int GetCurrMagazine(void)	{ return m_nCurrMagazine; }
	int GetMaxAmmo(void)		{ return m_nMaxAmmo; }
	int GetCurrAmmo(void)		{ return m_nCurrAmmo; }
	int GetBulletSpeed(void)	{ return m_nBulletSpeed; }
	int GetNumBulletsFired(void){ return m_nNumBulletsFired; }
	int GetSoundDistance(void)	{ return m_nSoundDistance; }
	float GetRateOfFire(void)	{ return m_fRateOfFire; }
	float GetReloadTimer(void)	{ return m_fReloadTimer; }
	float GetAccuracy(void)		{ return m_fAccuracy; }
};
#endif