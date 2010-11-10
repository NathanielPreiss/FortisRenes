#ifndef CIDLESTATE_H_
#define CIDLESTATE_H_

#include "IArtIntState.h"

class CIdleState : public IArtIntState
{
private:
	CIdleState();
	CIdleState(const CIdleState&);
	CIdleState& operator=(const CIdleState&);
	
public:
	static CIdleState* GetInstance(void);
	void CalculateAI(float fElapsedTime, CBase* pBase);

};
#endif