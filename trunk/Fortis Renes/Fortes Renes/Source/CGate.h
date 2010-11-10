#ifndef CGATE_H_
#define CGATE_H_

#include "CBase.h"

class CGate : public CBase
{
private:
	CBase* m_pGenerator;
public:
	CGate(void);
	~CGate(void);

	CBase* GetGenerator(void) { return m_pGenerator; }
	void SetGenerator(CBase* pBase) { m_pGenerator = pBase; }

	void HandleEvent(CEvent* pEvent);
};

#endif