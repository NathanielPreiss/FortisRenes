#ifndef CLIGHINFANTRY_H_
#define CLIGHTINFANTRY_H_

#include "CEnemy.h"
#include "CEvent.h"

class CLightInfantry : public CEnemy
{
private:
	
public:
	CLightInfantry(void);
	~CLightInfantry(void);

	void Update(float fElapsedTime);

	bool CheckCollision( CBase *pBase );

	void HandleEvent(CEvent* pEvent);

	void Shoot(void);
	void Walk(void);
};
#endif