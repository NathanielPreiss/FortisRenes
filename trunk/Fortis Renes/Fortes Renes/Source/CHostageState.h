#ifndef CHOSTAGESTATE_H_
#define CHOSTAGESTATE_H_

#include "IArtIntState.h"

class CHostageState : public IArtIntState
{
private:
	CHostageState(void);
	CHostageState(const CHostageState&);
	CHostageState& operator=(const CHostageState&);
	
public:
	static CHostageState* GetInstance(void);

	void CalculateAI(float fElapsedTime, CBase* pBase);
};
#endif