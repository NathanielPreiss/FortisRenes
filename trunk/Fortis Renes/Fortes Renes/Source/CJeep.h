#ifndef CJEEP_H_
#define CJEEP_H_

#include "CBase.h"

class CJeep : public CBase
{
private:
	float m_fRot;
	tVector2D m_vDirection;

public:
	CJeep(void);
	~CJeep(void);

	// Accessors
	float GetRotation() { return m_fRot; }
	tVector2D GetDirection() { return m_vDirection; }

	// Mutators
	void SetRotation(float fRot) { m_fRot = fRot; }
	void SetDirection(float fDirectionX, float fDirectionY) { m_vDirection.fX = fDirectionX; m_vDirection.fY = fDirectionY; }

	void Render(float fCamPosX, float fCamPosY);
	void Update(float fElapsedTime);
	void HandleEvent( CEvent* pEvent );
};


#endif