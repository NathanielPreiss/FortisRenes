#ifndef CENEMY_H_
#define CENEMY_H_

#include "CBase.h"
#include "IArtIntState.h"
#include "CWeapon.h"
#include "DirectX Wrappers\SGD_Math.h"

enum ENEMY{ENEMY_NULL, ENEMY_LIGHT, ENEMY_MEDIUM, ENEMY_HEAVY, ENEMY_JEEP, ENEMY_TANK, ENEMY_HELICOPTER, ENEMY_BOSS, ENEMY_COUNT};

class CEnemy : public CBase
{
private:
	int m_nEnemyID;
	IArtIntState* m_pAiState;
	int m_nSoundDetection;
	CBase* m_pTarget;
	bool m_bCalculate;
	CWeapon* m_Weapon;
	bool m_bAttack;
	tVector2D m_vFacingNormal;
	float m_fSpeed;
	int m_nWeaponSoundID;
	bool m_bDead;
	bool m_bPlayerKill;
	int m_nMoneyReward;
	int m_nRepReward;

public:
	
	CEnemy(int nWeapon);
	~CEnemy(void);

	void LoadTexture(void);
	void UnloadTexture(void);
	RECT GetRect(void);
	bool GetCalculate(void) { return m_bCalculate; }
	IArtIntState* GetState(void) { return m_pAiState; }
	CBase* GetTarget(void) { return m_pTarget; }
	CWeapon* GetWeapon(void) { return m_Weapon; }
	tVector2D& GetFacing(void) { return m_vFacingNormal; }
	bool Attack(void) { return m_bAttack; }
	float GetSpeed(void) { return m_fSpeed; }
	int GetEnemyID(void) { return m_nEnemyID; }
	int GetWeaponSoundID(void) { return m_nWeaponSoundID; }
	bool GetDead(void) { return m_bDead; }
	bool GetPlayerKill(void) { return m_bPlayerKill; }
	int GetMoneyReward(void) { return m_nMoneyReward; }
	int GetRepReward(void) { return m_nRepReward; }

	virtual void Update(float fElapsedTime);
	virtual void Render(float fCamPosX, float fCamPosY);
	void SetCalculate(bool calc) { m_bCalculate = calc; }
	void SetTarget(CBase* target) { m_pTarget = target; }
	void SetAttack(bool attack) { m_bAttack = attack; }
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }
	void SetFacing(float x, float y) { m_vFacingNormal.fX = x; m_vFacingNormal.fY = y; }
	void SetEnemyID(int id) { m_nEnemyID = id; }
	void SetWeaponSoundID(int nID) { m_nWeaponSoundID = nID; }
	void SetDead(bool bDead) { m_bDead = bDead; }
	void SetPlayerKill(bool bPlayerKill) { m_bPlayerKill = bPlayerKill; }
	void SetMoneyReward(int nNum) { m_nMoneyReward = nNum; }
	void SetRepReward(int nNum) { m_nRepReward = nNum; }

	void ChangeState(IArtIntState*);
	virtual bool CheckCollision( CBase *pBase );
	virtual void Shoot(void);
	virtual void Walk(void);

};
#endif