#include "CShopState.h"
#include "CGame.h"
#include "CPlayer.h"
#include "CInventory.h"
#include "CCursor.h"

CShopState::CShopState(void)
{
	m_BuyRECT.left = 100;
	m_BuyRECT.top = 350;
	m_BuyRECT.right = 250;
	m_BuyRECT.bottom = 400;

	m_SellRECT.left = 390;
	m_SellRECT.top = 350;
	m_SellRECT.right = 540;
	m_SellRECT.bottom = 400;
	
	m_ExitRECT.left = 450;
	m_ExitRECT.top = 415;
	m_ExitRECT.right = 620;
	m_ExitRECT.bottom = 470;
}
CShopState::~CShopState(void)
{

}
CShopState* CShopState::GetInstance(void)
{
	static CShopState instance;
	return &instance;
}
void CShopState::Enter(void)
{
	m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/ShopStateBG.jpg");
	m_nSelectionBoxID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/ShopStateSelectionBox.png");
	m_nSellSelection = 0;
	m_nBuySelection = 0;
	m_vSellList.clear();
	for(int i = 0; i < (CON_NUMBER-1) + CPlayer::GetInstance()->GetNumWeapons(); i++)
	{
		RECT *temp = new RECT();
		temp->left = 340;
		temp->top = 100 +(20*i);
		temp->right = 590;
		temp->bottom = temp->top + 20;
		m_vSellList.push_back(temp);
	}
	m_vBuyList.clear();
	for(int i = 0; i < (CON_NUMBER-1) + CPlayer::GetInstance()->GetNumWeapons(); i++)
	{
		RECT *temp = new RECT();
		temp->left = 50;
		temp->top = 100 +(20*i);
		temp->right = 300;
		temp->bottom = temp->top + 20;
		m_vBuyList.push_back(temp);
	}
}
bool CShopState::Input(void)
{
	if(CSGD_DirectInput::GetInstance()->MouseButtonPressed(0))
	{
		RECT temp;
		if(IntersectRect(&temp, &m_MouseRECT, &m_ExitRECT))
		{
			CGame::GetInstance()->RemoveTopState();
			return true;
		}
		if(IntersectRect(&temp, &m_MouseRECT, &m_BuyRECT))
		{
			if(CPlayer::GetInstance()->SpendMoney( 100 ))
			switch(m_nBuySelection)
			{
			case 0:
				CPlayer::GetInstance()->GetInventory()->PickUpItem(CON_HEALTH);
				break;
			case 1:
				CPlayer::GetInstance()->GetInventory()->PickUpItem(CON_ADRENALINE);
				break;
			case 2:
				CPlayer::GetInstance()->GetWeapon(0)->SetAmmo(CPlayer::GetInstance()->GetWeapon(0)->GetMaxAmmo());
				break;
			case 3:
				CPlayer::GetInstance()->GetWeapon(1)->SetAmmo(CPlayer::GetInstance()->GetWeapon(1)->GetMaxAmmo());
				break;
			case 4:
				CPlayer::GetInstance()->GetWeapon(2)->SetAmmo(CPlayer::GetInstance()->GetWeapon(2)->GetMaxAmmo());
				break;
			case 5:
				CPlayer::GetInstance()->GetWeapon(3)->SetAmmo(CPlayer::GetInstance()->GetWeapon(3)->GetMaxAmmo());
				break;
			case 6:
				CPlayer::GetInstance()->GetWeapon(4)->SetAmmo(CPlayer::GetInstance()->GetWeapon(4)->GetMaxAmmo());
				break;
			case 7:
				CPlayer::GetInstance()->GetWeapon(5)->SetAmmo(CPlayer::GetInstance()->GetWeapon(5)->GetMaxAmmo());
				break;
			}
			return true;
		}
		if(IntersectRect(&temp, &m_MouseRECT, &m_SellRECT))
		{
			//CGame::GetInstance()->RemoveTopState();
			return true;
		}
		for(unsigned int i = 0; i < m_vBuyList.size(); i++)
		{
			if(IntersectRect(&temp, &m_MouseRECT, m_vBuyList[i]))
			{
				m_nBuySelection = i;
				return true;
			}
		}
		for(unsigned int i = 0; i < m_vSellList.size(); i++)
		{
			if(IntersectRect(&temp, &m_MouseRECT, m_vSellList[i]))
			{
				m_nSellSelection = i;
				return true;
			}
		}
	}
	return true;
}
void CShopState::Update(float fElapsedTime)
{
	m_MouseRECT.left = (LONG)CCursor::GetInstance()->GetPosX();
	m_MouseRECT.top = (LONG)CCursor::GetInstance()->GetPosY();
	m_MouseRECT.right = m_MouseRECT.left + 1;
	m_MouseRECT.bottom  = m_MouseRECT.top + 1;
}
void CShopState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBackgroundID, 0, 0);

	char buffer[16] = {0};

	sprintf_s(buffer, "Money:\n  %d", CPlayer::GetInstance()->GetMoney());

	CBitmapFont::GetInstance()->Draw(buffer, 30, 15, 0.5f);
	CBitmapFont::GetInstance()->Draw("Name      Cost", 55, 70, 0.5f);
	CBitmapFont::GetInstance()->Draw("Name     Value", 345, 70, 0.5f);
	CBitmapFont::GetInstance()->Draw("Buy", 130, 360, 0.75f);
	//CBitmapFont::GetInstance()->Draw("Sell", 410, 360, 0.75f);
	CBitmapFont::GetInstance()->Draw("Exit", 490, 430, 0.75f);

	if(m_vBuyList.size() > 0)
		CBitmapFont::GetInstance()->Draw("Healthpack  100", m_vBuyList[0]->left+5, m_vBuyList[0]->top+5, 0.5f);
	if(m_vBuyList.size() > 1)
		CBitmapFont::GetInstance()->Draw("Adrenaline  100", m_vBuyList[1]->left+5, m_vBuyList[1]->top+5, 0.5f);
	if(m_vBuyList.size() > 2)
		CBitmapFont::GetInstance()->Draw("Pistol Ammo 100", m_vBuyList[2]->left+5, m_vBuyList[2]->top+5, 0.5f);
	if(m_vBuyList.size() > 3)
		CBitmapFont::GetInstance()->Draw("MP5 Ammo    100", m_vBuyList[3]->left+5, m_vBuyList[3]->top+5, 0.5f);
	if(m_vBuyList.size() > 4)
		CBitmapFont::GetInstance()->Draw("Shotgun Ammo 100", m_vBuyList[4]->left+5, m_vBuyList[4]->top+5, 0.5f);
	if(m_vBuyList.size() > 5)
		CBitmapFont::GetInstance()->Draw("Rifle Ammo  100", m_vBuyList[5]->left+5, m_vBuyList[5]->top+5, 0.5f);
	if(m_vBuyList.size() > 6)
		CBitmapFont::GetInstance()->Draw("Bazooka Ammo 100", m_vBuyList[6]->left+5, m_vBuyList[6]->top+5, 0.5f);
	if(m_vBuyList.size() > 7)
		CBitmapFont::GetInstance()->Draw("RYNO V Ammo 100", m_vBuyList[7]->left+5, m_vBuyList[7]->top+5, 0.5f);
	//if(m_vBuyList.size() > 8)
		//CBitmapFont::GetInstance()->Draw("Something   100", m_vBuyList[8]->left+5, m_vBuyList[8]->top+5, 0.5f);
/*
	if(m_vSellList.size() > 0)
		CBitmapFont::GetInstance()->Draw("Healthpack  100", m_vSellList[0]->left+5, m_vSellList[0]->top+5, 0.5f);
	if(m_vSellList.size() > 1)
		CBitmapFont::GetInstance()->Draw("Adrenaline  100", m_vSellList[1]->left+5, m_vSellList[1]->top+5, 0.5f);
	if(m_vSellList.size() > 2)
		CBitmapFont::GetInstance()->Draw("Pistol Ammo 100", m_vSellList[2]->left+5, m_vSellList[2]->top+5, 0.5f);
	if(m_vSellList.size() > 3)
		CBitmapFont::GetInstance()->Draw("MP5 Ammo    100", m_vSellList[3]->left+5, m_vSellList[3]->top+5, 0.5f);
	if(m_vSellList.size() > 4)
		CBitmapFont::GetInstance()->Draw("Shotgun Ammo 100", m_vSellList[4]->left+5, m_vSellList[4]->top+5, 0.5f);
	if(m_vSellList.size() > 5)
		CBitmapFont::GetInstance()->Draw("Rifle Ammo  100", m_vSellList[5]->left+5, m_vSellList[5]->top+5, 0.5f);
	if(m_vSellList.size() > 6)
		CBitmapFont::GetInstance()->Draw("Bazooka Ammo 100", m_vSellList[6]->left+5, m_vSellList[6]->top+5, 0.5f);
	if(m_vSellList.size() > 7)
		CBitmapFont::GetInstance()->Draw("RYNO V Ammo 100", m_vSellList[7]->left+5, m_vSellList[7]->top+5, 0.5f);
	if(m_vSellList.size() > 8)
		CBitmapFont::GetInstance()->Draw("Something   100", m_vSellList[8]->left+5, m_vSellList[8]->top+5, 0.5f);
*/
	CSGD_TextureManager::GetInstance()->Draw(m_nSelectionBoxID, m_vBuyList[m_nBuySelection]->left, m_vBuyList[m_nBuySelection]->top);
//	CSGD_TextureManager::GetInstance()->Draw(m_nSelectionBoxID, m_vSellList[m_nSellSelection]->left, m_vBuyList[m_nSellSelection]->top);

}
void CShopState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBackgroundID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nSelectionBoxID);
}