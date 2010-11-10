#ifndef CREBELSTATE_H_
#define CREBELSTATE_H_

#include "IArtIntState.h"

class CRebelState : public IArtIntState
{
private:
	private:
	CRebelState(void);
	CRebelState(const CRebelState&);
	CRebelState& operator=(const CRebelState&);
	
public:
	static CRebelState* GetInstance(void);

	void CalculateAI(float fElapsedTime, CBase* pBase);
};
#endif