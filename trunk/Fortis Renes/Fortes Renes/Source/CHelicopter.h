#ifndef CHELICOPTER_H_
#define CHELICOPTER_H_

#include "CEnemy.h"

class CHelicopter : public CEnemy
{
private:
	// Sound ID
	int m_nSoundID;
	float m_fRotation;
	float m_fShadowPosX;
	float m_fShadowPosY;
	
public:
	CHelicopter(void);
	~CHelicopter(void);

	void Update(float fElapsedTime);
	void Render(float fCamPosX, float fCamPosY);

	void SetCull(bool bCull){CBase::SetCull(false);}

	void HandleEvent(CEvent *pEvent);
};
#endif