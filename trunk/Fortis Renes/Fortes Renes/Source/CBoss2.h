#ifndef CBOSS2_H_
#define CBOSS2_H_

#include "CEnemy.h"

class CEmitter;

class CBoss2 : public CEnemy
{
private:
	RECT los, empty;
	bool once;
	bool uno;
	bool dos;
	bool tres;
	tVector2D m_vDirection;
	tVector2D Spot1;
	tVector2D Spot2;
	tVector2D Spot3;
	float m_fCounter;
public:
	CBoss2(void);
	~CBoss2(void);

	void Update(float fElapsedTime);
	void Render(float fCamPosX, float fCamPosY);
	void HandleEvent(CEvent* pEvent);
};


#endif
