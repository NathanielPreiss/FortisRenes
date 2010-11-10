#ifndef CENEMYSQUAD_H_
#define CENEMYSQUAD_H_

#include <windows.h>
#include <vector>
#include <string>
using std::vector;
using std::string;

#include "CEventSystem.h"
#include "IListener.h"

class CEnemy;

class CEnemySquad : public IListener
{
private:
	CEnemy* m_pLeader;
	vector<CEnemy*> m_vSquad;
	float m_fPosX;
	float m_fPosY;

	float m_fTimeBucket;
	float m_fAttackTimer;
	float m_fGroupUpTime;

	CEnemySquad(void);
	CEnemySquad(const CEnemySquad& that);
	CEnemySquad& operator=(const CEnemySquad& that);
	~CEnemySquad(void);
public:
	static CEnemySquad* GetInstance(void);

	float GetPosX(void) { return m_fPosX; }
	float GetPosY(void) { return m_fPosY; }

	void Update(float fElapsedTime);

	void EmptySquad(void);

	void HandleEvent(CEvent* pEvent);
};

#endif