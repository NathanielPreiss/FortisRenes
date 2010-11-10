#ifndef CJEEPSTATE_H_
#define CJEEPSTATE_H_

#include "IPlayerState.h"
#include "DirectX Wrappers/SGD_Math.h"

class CPlayer;

class CJeepState : public IPlayerState
{
private:
	int m_nImageID;
	float m_fRot;
	float m_fRotationRate;
	float m_fSpeed;
	float m_fAccelerationRate;
	tVector2D	m_vDirection;
	CPlayer* pPlayer;

	//	Trilogy of Evil
	CJeepState(void);
	//		copy constructor
	CJeepState(const CJeepState&);
	//		assignment operator
	CJeepState& operator=(const CJeepState&);
	//		destructor
	~CJeepState(void);

public:
	//	Singleton accessor
	static CJeepState* GetInstance(void);

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
	void ChangeState( IPlayerState* newState );

};
#endif