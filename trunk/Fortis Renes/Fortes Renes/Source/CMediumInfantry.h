#ifndef CMEDIUMINFANTRY_H_
#define CMEDIUMINFANTRY_H_

#include "CEnemy.h"		// Derived from this header

class CMediumInfantry : public CEnemy
{
private:
	
public:
	CMediumInfantry(void);
	~CMediumInfantry(void);

	void Update(float fElapsedTime);

	void HandleEvent(CEvent* pEvent);
	bool CheckCollision(CBase* pBase);

	void Shoot(void);
	void Walk(void);
};
#endif