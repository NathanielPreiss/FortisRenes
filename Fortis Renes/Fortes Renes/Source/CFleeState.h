#ifndef CFLEESTATE_H_
#define CFLEESTATE_H_

#include "IArtIntState.h"

class CFleeState : public IArtIntState
{
private:
	CFleeState(void);
	CFleeState(const CFleeState&);
	CFleeState& operator=(const CFleeState);

public:
	static CFleeState* GetInstance(void);

	void CalculateAI(float fElapsedTime, CBase* pBase);

};
#endif