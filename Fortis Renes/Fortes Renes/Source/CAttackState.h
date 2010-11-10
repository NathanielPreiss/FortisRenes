#ifndef CATTACKSTATE_H_
#define CATTACKSTATE_H_

#include "IArtIntState.h"

class CAttackState : public IArtIntState
{
private:
	CAttackState(void);
	CAttackState(const CAttackState&);
	CAttackState& operator=(const CAttackState&);

public:
	static CAttackState* GetInstance(void);

	void CalculateAI(float fElapsedTime, CBase* pBase);
};
#endif