#ifndef CBOSS1_H_
#define CBOSS1_H_

#include "CEnemy.h"

class CBase;

class CBoss1 : public CEnemy
{
private:
	RECT los, empty;
	tVector2D m_vDirection;
	float m_fCounter;
	float m_fDestroyCounter;
	bool m_bForCounter;
	CBase* bomb;
	CBase* bomb2;
	CBase* bomb3;
public:
	CBoss1(void);
	~CBoss1(void);

	void Update(float fElapsedTime);
	void Render(float fCamPosX, float fCamPosY);
	void HandleEvent(CEvent* pEvent);
	bool CheckCollision( CBase *pBase );
};

#endif