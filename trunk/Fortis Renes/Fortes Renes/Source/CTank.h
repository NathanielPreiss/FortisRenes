#ifndef CTANK_H_
#define CTANK_H_

#include "CBase.h"

class CTank : public CBase
{
private:
	float m_fRot;
	tVector2D m_vDirection;

public:
	CTank(void);
	~CTank(void);

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