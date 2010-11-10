
#include "CBase.h"

class CCursor : public CBase
{
private:

	CCursor(void);
	~CCursor(void);

public:
	static CCursor* GetInstance(void);

	void Update(float fElapsedTime);
	void Render(void);
	void UnloadCursor(void);

	void HandleEvent(CBase* pBase);
};
