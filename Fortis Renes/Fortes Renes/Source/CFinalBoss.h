#ifndef CFINALBOSS_H_
#define CFINALBOSS_H_

#include "CEnemy.h"

class CFinalBoss : public CEnemy
{
private:
	RECT los, empty;
	tVector2D m_vDirection;
	int m_nPhase;

public:
	CFinalBoss(void);
	~CFinalBoss(void);

	void Update(float fElapsedTime);
	void Render(float fCamPosX, float fCamPosY);
	void HandleEvent(CEvent* pEvent);
};




#endif