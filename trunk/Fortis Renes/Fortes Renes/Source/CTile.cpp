#include "CTile.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CBase.h"

CTile::~CTile()
{
	for( unsigned int index = 0; index < m_vTriggers.size(); index++ )
	{
		delete m_vTriggers[index];
	}
	m_vTriggers.clear();
}

void CTile::SetTile( int imageID, int imagePos, int rows, int columns, int size, float posX, float posY, int worldSize )
{
	m_fPosX = posX;
	m_fPosY = posY;
	this->m_nImageID = imageID;
	m_rSource.left = (imagePos % rows)*size;
	m_rSource.top = (imagePos / rows)*size;
	m_rSource.bottom = m_rSource.top + size;
	m_rSource.right = m_rSource.left + size;
	m_nHeight = worldSize;
	m_nWidth = worldSize;
}

void CTile::Render(void)
{
}

void CTile::AddTrigger( string e, int o )
{
	trigger* toAdd = new trigger();
	toAdd->triggeredEvent = e;
	toAdd->triggerObject = o;
	m_vTriggers.push_back(toAdd);
}

void CTile::HandleEvent(CEvent* pEvent)
{
}

void CTile::CallEvents(CBase* pBase)
{
	for( unsigned int index = 0; index < m_vTriggers.size(); index++ )
	{
		if( pBase->GetType()-1 == m_vTriggers[index]->triggerObject )
		{
			CEventSystem::GetInstance()->SendEvent(m_vTriggers[index]->triggeredEvent.c_str());
		}
	}
}

RECT CTile::GetWorldRect(void)
{
	RECT rTile;
	rTile.top = (LONG)this->m_fPosY;
	rTile.left = (LONG)m_fPosX;
	rTile.right = (LONG)(rTile.left + m_nWidth);
	rTile.bottom = (LONG)(rTile.top + m_nHeight);

	return rTile;
}