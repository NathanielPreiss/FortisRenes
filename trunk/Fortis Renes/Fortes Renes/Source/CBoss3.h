#ifndef CBOSS3_H_
#define CBOSS3_H_

#include "CEnemy.h"

class CBoss3 : public CEnemy
{
private:
	RECT los, empty;
	tVector2D m_vDirection;
	bool tankmode;
	float m_fRot;
public:
	CBoss3(void);
	~CBoss3(void);

	void Update(float fElapsedTime);
	void Render(float fCamPosX, float fCamPosY);
	void HandleEvent(CEvent* pEvent);
};

#endif