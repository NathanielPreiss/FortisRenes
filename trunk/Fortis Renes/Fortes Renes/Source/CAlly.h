#ifndef CALLY_H_
#define CALLY_H_

#include "CBase.h"
#include "IArtIntState.h"

class CWeapon;

class CAlly : public CBase
{
private:
	CWeapon* m_pWeapon;
	IArtIntState* m_pAIState;
	CBase* m_pTarget;
	tVector2D m_vFacingNormal;

	int m_nSpeed;
	int m_nWeaponSoundID;

public:
	CAlly(bool bHostage = false);
	~CAlly(void);

	void SetSpeed(int nSpeed) { m_nSpeed = nSpeed; }
	void SetTarget(CBase* pTarget) { m_pTarget = pTarget; }
	void SetFacing(float x, float y) { m_vFacingNormal.fX = x; m_vFacingNormal.fY = y; }
	void SetWeaponSoundID(int nID) { m_nWeaponSoundID = nID; }

	int GetSpeed(void) { return m_nSpeed; }
	CBase* GetTarget(void) { return m_pTarget; }
	CWeapon* GetWeapon(void) { return m_pWeapon; }
	tVector2D& GetFacing(void) { return m_vFacingNormal; }
	int GetWeaponSoundID(void) { return m_nWeaponSoundID; }

	void Update(float fElapsedTime);
	void Render(float fCamPosX, float fCamPosY);

	bool CheckCollision(CBase* pBase);

	void HandleEvent(CEvent* pEvent);
};
#endif