#ifndef IARTINTSTATE_H_
#define IARTINTSTATE_H_

#include "CBase.h"

class IArtIntState
{
private:
public:
	virtual void CalculateAI(float fElapsedTime, CBase* pBase) = 0;

};
#endif