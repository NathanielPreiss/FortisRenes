//////////////////////////////////////////////////////////////////////////////
// File: "CInventory.cpp"
//
// Date Edited: 10/19/2010
//
// Purpose: 
//
//////////////////////////////////////////////////////////////////////////////

// Nessisary includes 
#include "CInventory.h"
#include "CBitmapFont.h"
#include "CEventSystem.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CPlayer.h"

CInventory::CInventory(void)
{
	m_nMedkitID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Medkit.png");
	m_nAdrenalineID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Adrenaline.png");
	for(int i = 0; i < CON_NUMBER; i++)
		m_Inventory[i] = 0;
}
void CInventory::PickUpItem(int nType)
{
	m_Inventory[nType]++;
}
bool CInventory::UseItem(int nItem)
{
	if(m_Inventory[nItem] > 0)
	{
		switch(nItem)
		{
		case CON_HEALTH:
			CEventSystem::GetInstance()->SendEvent("player_use_healthpack", CPlayer::GetInstance());
			break;
		case CON_ADRENALINE:
			CEventSystem::GetInstance()->SendEvent("player_use_adrenaline", CPlayer::GetInstance());
			break;
		}
		return true;
	}
	m_Inventory[nItem]++;
	return false;
}
void CInventory::ClearInventory(void)
{
	for(int i = 0; i < CON_NUMBER; i++)
		m_Inventory[i] = 0;
}
int CInventory::GetNumItem(int nItem)
{
	// Not a valid index
	if(nItem < 0 || nItem >= CON_NUMBER)
		return -1;

	return m_Inventory[nItem];
}
void CInventory::Render(int currItem)
{
	char buffer[32];
	CSGD_TextureManager::GetInstance()->Draw( m_nMedkitID, 64, 385, 0.5f, 0.5f);
	sprintf_s(buffer, _countof(buffer), "%d", m_Inventory[0]);
	CBitmapFont::GetInstance()->Draw(buffer, 80, 385, 0.5f, -1, (!currItem)?true:false);
	CSGD_TextureManager::GetInstance()->Draw( m_nAdrenalineID, 128, 385, 0.5f, 0.5f);
	sprintf_s(buffer, _countof(buffer), "%d", m_Inventory[1]);
	CBitmapFont::GetInstance()->Draw(buffer, 144, 385, 0.5f, -1, (currItem)?true:false);	
}