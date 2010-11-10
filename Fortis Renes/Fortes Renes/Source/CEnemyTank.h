#ifndef CENEMYTANK_H_
#define CENEMYTANK_H_

#include "CEnemy.h"

class CEnemyTank : public CEnemy
{
private:
	float m_fShotTimer;
	float m_fTimeBucket;

	float m_fRotation;

public:
	CEnemyTank();
	~CEnemyTank();

	void Update(float fElapsedTime);

	void Render(float fCamPosX, float fCamPosY);

	bool CheckCollision(CBase* pBase);

};
#endif