#ifndef CTANKSTATE_H_
#define CTANKSTATE_H_

#include "IPlayerState.h"
#include "IListener.h"
#include "DirectX Wrappers/SGD_Math.h"
#include "CWeapon.h"

class CPlayer;

class CTankState : public IPlayerState, IListener
{
private:
	int m_nBaseImageID;
	int m_nTurretImageID;
	float m_fTimer;
	float m_fRot;
	float m_fRotationRate;
	float m_fSpeed;
	float m_fAccelerationRate;
	tVector2D m_vTurretDirection;
	float m_fTurretRot;
	tVector2D	m_vDirection;
	CPlayer* pPlayer;

	//	Trilogy of Evil
	CTankState(void);
	//		copy constructor
	CTankState(const CTankState&);
	//		assignment operator
	CTankState& operator=(const CTankState&);
	//		destructor
	~CTankState(void);

public:
	//	Singleton accessor
	static CTankState* GetInstance(void);

	// Accessors
	float GetSpeed() { return m_fSpeed; }
	float GetAccelerationRate() { return m_fAccelerationRate; }
	float GetRotation() { return m_fRot; }
	float GetDirectionX() { return m_vDirection.fX; }
	float GetDirectionY() { return m_vDirection.fY; }

	// Mutators
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }
	void SetAccelerationRate(float fAccelerationRate) { m_fAccelerationRate = fAccelerationRate; }

	void Enter();
	void Update(float fElapsedTime);
	void Render(float fCamPosX, float fCamPosY);
	void HandleEvent( CEvent* pEvent );
	void ChangeState( IPlayerState* newState );

};
#endif