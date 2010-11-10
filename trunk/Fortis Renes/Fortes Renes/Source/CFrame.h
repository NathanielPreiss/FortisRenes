#ifndef CFRAME_H_
#define CFRAME_H_

#include <windows.h>
#include <vector>
using std::vector;

#include "CEvent.h"

class CFrame
{
private:
	RECT m_SourceRect;
	float m_fDuration;
	vector<CEvent> m_vTriggers;
	RECT m_CollisionRect;

public:
	void ActivateTriggers(void);

};
#endif