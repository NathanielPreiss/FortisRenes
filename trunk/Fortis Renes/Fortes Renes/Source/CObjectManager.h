#ifndef COBJECTMANAGER_H_
#define COBJECTMANAGER_H_

#include <vector>
using std::vector;

#include <fstream>
using std::ifstream;

#include "CBase.h"
#include "CTile.h"

struct GameMap
{
	int imageID;
	int MapRow;
	int MapColumn;
	int SourceRow;
	int SourceColumn;
	int MapTileSize;
	int SourceTileSize;
	float tileRatio;
	CTile** m_vTileList;
};

class CObjectManager
{
private:
	vector<CBase*> m_vObjectList;
	GameMap m_gmMap; 
	static CObjectManager* instance;
	CObjectManager(void);
	~CObjectManager(void);

public:
	static CObjectManager* GetInstance(void);
	static void DeleteInstance(void);

	// this will fill in the tilemap information as read in by the file that is being loaded
	void LoadWorldMap(ifstream& in);
	void UnLoadWorldMap(void);

	GameMap* GetMap(void) { return &m_gmMap; }

	void UpdateObjects(float);
	void RenderObjects(void);

	void AddObject(CBase* pObject);
	void RemoveObject(CBase* pObject);

	void RemoveAllObjects(void);
};
#endif