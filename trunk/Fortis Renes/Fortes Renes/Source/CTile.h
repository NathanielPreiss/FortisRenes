#ifndef CTILE_H_
#define CTILE_H_

#include <windows.h>
#include <vector>
#include <string>
using std::vector;
using std::string;

#include "CEventSystem.h"
#include "IListener.h"

class CBase;

struct trigger
{
	string triggeredEvent;
	int triggerObject;
};

class CTile : IListener
{
private:
	RECT m_rSource;
	int m_nImageID;
	float m_fPosX;
	float m_fPosY;
	int m_nHeight;
	int m_nWidth;
	bool m_bTraversable;
	bool m_bCull;
	vector<trigger*> m_vTriggers;

public:
	~CTile();
	void SetTile( int imageID, int imagePos, int rows, int columns, int size, float posX, float posY, int worldSize );
	bool CheckTraversability(void) {return m_bTraversable;}
	void Render(void);
	RECT GetRect(void)	{return m_rSource;}
	void AddTrigger( string e, int o );
	void CallEvents(CBase* pBase);
	void SetCull(bool bCull) { m_bCull  = bCull; }
	bool GetCull(void) { return m_bCull; }

	RECT GetWorldRect(void);
	void HandleEvent(CEvent* pEvent);

};
#endif