#ifndef CHEAVYINFANTRY_H_
#define CHEAVYINFANTRY_H_

#include "CEnemy.h"

class CHeavyInfantry : public CEnemy
{
private:
	
public:
	CHeavyInfantry(void);
	~CHeavyInfantry(void);

	void Update(float fElapsedTime);

	void HandleEvent(CEvent* pEvent);
	bool CheckCollision(CBase* pBase);

	void Shoot(void);
	void Walk(void);
};
#endif