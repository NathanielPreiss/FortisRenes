#ifndef CROCKET_H_
#define CROCKET_H_

#include "CBullet.h"
#include "CEmitter.h"

class CRocket : public CBullet
{
private:
	float m_fDelayTime;
	float m_fTimeBucket;
	float m_fScale;
	CEmitter* m_Explosion;
public:
	CRocket(float fDelay);
	~CRocket(void);
	void Update(float fElapsedTime);
	void Render(float fCamPosX, float fCamPosY);
};

#endif