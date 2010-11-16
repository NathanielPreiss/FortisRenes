#include "CObjectManager.h"
#include "CCamera.h"
#include <string>
using std::string;

#include "CProfiler.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"

CObjectManager* CObjectManager::instance = NULL;

CObjectManager::CObjectManager(void)
{
	m_gmMap.m_vTileList = NULL;
}

CObjectManager::~CObjectManager(void)
{
}

void CObjectManager::UpdateObjects(float fElapsedTime)
{
	RECT rWindow;
	rWindow.top = (LONG)(CCamera::GetInstance()->GetPosY());
	rWindow.left = (LONG)(CCamera::GetInstance()->GetPosX());
	rWindow.right = (LONG)(rWindow.left + CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferWidth);
	rWindow.bottom = (LONG)(rWindow.top + CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferHeight);
	RECT rDummy;

	vector<CBase*>::iterator iter = m_vObjectList.begin();

	while(iter != m_vObjectList.end())
	{
		(*iter)->Update(fElapsedTime);
		// Check for object culling
		if( IntersectRect(&rDummy,&rWindow,&(*iter)->GetRect()) )
			(*iter)->SetCull(false);
		else
			(*iter)->SetCull(true);	
	
		if( !(*iter)->GetCull() )
		{
			for( unsigned int j = 0; j < m_vObjectList.size(); ++j )
			{
				if( (*iter)->GetType() != m_vObjectList[j]->GetType() )
					 if((*iter)->CheckCollision( m_vObjectList[j] ))
						break;
			}
		}

		iter++;
	}

	// Check for tile culling
	if( m_gmMap.m_vTileList != NULL )
	{
		for( int c = 0; c < m_gmMap.MapColumn; c++ )
		{
			for( int r = 0; r < m_gmMap.MapRow; r++ )
			{
				if( IntersectRect(&rDummy,&rWindow,&m_gmMap.m_vTileList[c][r].GetWorldRect()) )
					m_gmMap.m_vTileList[c][r].SetCull(false);
				else
					m_gmMap.m_vTileList[c][r].SetCull(true);
			}
		}
	}

}

void CObjectManager::RenderObjects(void)
{
	float nCamX = CCamera::GetInstance()->GetPosX();
	float nCamY = CCamera::GetInstance()->GetPosY();

	for( int c = 0; c < m_gmMap.MapColumn; c++ )
	{
		for( int r = 0; r < m_gmMap.MapRow; r++ )
		{
			if( m_gmMap.m_vTileList[c][r].GetCull() == false )
				CSGD_TextureManager::GetInstance()->Draw(m_gmMap.imageID, (int)(r*m_gmMap.MapTileSize-nCamX), 
														(int)(c*m_gmMap.MapTileSize-nCamY), m_gmMap.tileRatio,
														m_gmMap.tileRatio, &(m_gmMap.m_vTileList[c][r].GetRect()));
		}
	}

	for (unsigned int i=0; i < m_vObjectList.size(); i++)
		if( m_vObjectList[i]->GetCull() == false )
			m_vObjectList[i]->Render(nCamX, nCamY);
}

void CObjectManager::AddObject(CBase* pObject)
{
	//	Check for valid object pointer
	if(pObject == NULL)
		return;

	// Check to make sure all objects have valid layer
#ifdef _DEBUG
	if(pObject->GetLayer() == -1)
		PostQuitMessage(-1);
#endif

	//	Add object to object list
	if(m_vObjectList.size() == 0)
	{
		m_vObjectList.push_back(pObject);
		pObject->AddRef();
		return;
	}
	// smaller # layer = rendered lower then other objects
	vector<CBase*>::iterator iter = m_vObjectList.end();
	for(int i = (int)(m_vObjectList.size()-1); i >= 0; i--)
	{
		if(m_vObjectList[i]->GetLayer() < pObject->GetLayer())
		{
			m_vObjectList.insert(iter, pObject);
			pObject->AddRef();
			return;
		}
		iter--;
	}
	//iter = m_vObjectList.begin();
	m_vObjectList.insert(iter, pObject);
	pObject->AddRef();
}

void CObjectManager::RemoveObject(CBase* pObject)
{
	//	Check for valid object pointer
	if (pObject == NULL)
		return;

	for (vector<CBase*>::iterator iter = m_vObjectList.begin();
		 iter != m_vObjectList.end();
		 iter++)
	{
		// if this is the object we are looking for.
		if ((*iter) == pObject)
		{
			// Remove my reference to this object.
			(*iter)->Release();

			// Remove the object from the list
			iter = m_vObjectList.erase(iter);
			break;
		}
	}
}

void CObjectManager::RemoveAllObjects(void)
{
	//	Call Release() on all objects.
	for (unsigned int i=0; i < m_vObjectList.size(); i++)
	{
		m_vObjectList[i]->Release();
	}

	//	Collapse the vector
	m_vObjectList.clear();
}

CObjectManager* CObjectManager::GetInstance(void)
{
	if( !instance )
		instance = new CObjectManager();
	return instance;
}

void CObjectManager::DeleteInstance(void)
{
	if( instance )
	{
		delete instance;
		instance = NULL;
	}
}

void CObjectManager::LoadWorldMap(ifstream& in)
{
	CProfiler::GetInstance()->CheckFrequency();
	CProfiler::GetInstance()->StartCount();
	char strLength;
	char* buffer;
	int sr, sc, ss, pos, obj, numTrigger;
	//	-	6 ints in order: map columns, map rows, map tilesize, set columns, set rows, set tilesize
	in.read((char*)&m_gmMap.MapColumn,4);
	in.read((char*)&m_gmMap.MapRow,4);
	in.read((char*)&m_gmMap.MapTileSize,4);
	in.read((char*)&sc,4);
	in.read((char*)&sr,4);
	in.read((char*)&ss,4);

	m_gmMap.tileRatio = (float)m_gmMap.MapTileSize / (float)ss;

	//	-	1 byte for the length of the coming string
	in.read(&strLength,1);

	buffer = new char[(int)strLength+1];

	buffer[strLength] = '\0';

	//	-	file name of the image for the tileset, string size determined above
	in.read(buffer,strLength);

	// use the loaded in filename to load image and save id
	string filename = "Resource\\Graphics\\";
	filename += buffer;
	m_gmMap.imageID = CSGD_TextureManager::GetInstance()->LoadTexture(filename.c_str());

	delete[] buffer;

	m_gmMap.m_vTileList = new CTile*[m_gmMap.MapColumn];

	for( int c = 0; c < m_gmMap.MapColumn; c++ )
	{
		m_gmMap.m_vTileList[c] = new CTile[m_gmMap.MapRow];
	}

	//	-	for each tile: imagepos, num of triggers, size of coming string, event triggered, object that triggers
	for( int c = 0; c < m_gmMap.MapColumn; c++ )
	{
		for( int r = 0; r < m_gmMap.MapRow; r++ )
		{
			in.read((char*)&pos,4);
			m_gmMap.m_vTileList[c][r].SetTile(m_gmMap.imageID,pos,sr,sc,ss,(float)(r*m_gmMap.MapTileSize),(float)(c*m_gmMap.MapTileSize), m_gmMap.MapTileSize);
			in.read((char*)&numTrigger,4);
			for( int i = 0; i < numTrigger; i++ )
			{
				in.read(&strLength,1);
				buffer = new char[(int)strLength+1];
				buffer[strLength] = '\0';
				in.read(buffer,strLength);
				string newEvent(buffer);
				in.read((char*)&obj,4);
				m_gmMap.m_vTileList[c][r].AddTrigger(newEvent,obj);
				delete[] buffer;
			}
		}
	}
	CProfiler::GetInstance()->EndCount();
	CProfiler::GetInstance()->Result();
}

void CObjectManager::UnLoadWorldMap(void)
{
	if( m_gmMap.m_vTileList != NULL )
	{
		for( int c = 0; c < m_gmMap.MapColumn; c++ )
		{
			delete[] m_gmMap.m_vTileList[c];
			m_gmMap.m_vTileList[c] = NULL;
		}
		delete[] m_gmMap.m_vTileList;
		m_gmMap.m_vTileList = NULL;
	}
}