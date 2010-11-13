#include "CResearchCenterState.h"
#include "CCursor.h"
#include "CGame.h"
#include "CPlayer.h"
CResearchCenterState::CResearchCenterState(void)
{
	m_ReturnRECT.left = 430;
	m_ReturnRECT.top = 12;
	m_ReturnRECT.right = 635;
	m_ReturnRECT.bottom = 76;

	m_ArmorRECT.left = 30;
	m_ArmorRECT.top = 100;
	m_ArmorRECT.right = 180;
	m_ArmorRECT.bottom = 150;

	m_WeaponRECT.left = 245;
	m_WeaponRECT.top = 100;
	m_WeaponRECT.right = 395;
	m_WeaponRECT.bottom = 150;

	m_ConsumableRECT.left = 460;
	m_ConsumableRECT.top = 100;
	m_ConsumableRECT.right = 610;
	m_ConsumableRECT.bottom = 150;

}
CResearchCenterState::~CResearchCenterState(void)
{
}
CResearchCenterState* CResearchCenterState::GetInstance(void)
{
	static CResearchCenterState instance;
	return &instance;
}
void CResearchCenterState::Enter(void)
{
	m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/ResearchCenterStateBG.jpg");
	m_nAlphaID= CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/ResearchCenterAlpha.png");
}
bool CResearchCenterState::Input(void)
{
	
/*	
	// SEXY BIT OF CODE
	int x = CSGD_DirectInput::GetInstance()->GetDIKCode();

	if(CSGD_DirectInput::GetInstance()->KeyPressed(x) && x >= DIK_1 && x <= DIK_0)
	{
		x = (x-1)%10;
		m_nInvestAmount = (m_nInvestAmount * 10) + x;
		if(m_nInvestAmount > 1000000)
			m_nInvestAmount = 1000000;
	}
	

	else if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_BACK))
	{
		m_nInvestAmount /= 10;
	}
*/
	if(CSGD_DirectInput::GetInstance()->MouseButtonPressed(0))
	{
		RECT temp;
		if(IntersectRect(&temp, &m_MouseRECT, &m_ReturnRECT))
			CGame::GetInstance()->RemoveTopState();
		if(CPlayer::GetInstance()->GetResearchArmorLevel() < 3&& IntersectRect(&temp, &m_MouseRECT, &m_ArmorRECT))
		{
			if(CPlayer::GetInstance()->SpendMoney(100*(CPlayer::GetInstance()->GetResearchArmorLevel()+1)))
				CPlayer::GetInstance()->UpgradeResearchArmorLevel();
		}
		if(CPlayer::GetInstance()->GetResearchWeaponLevel() < 3 && IntersectRect(&temp, &m_MouseRECT, &m_WeaponRECT))
		{
			if(CPlayer::GetInstance()->SpendMoney(100*(CPlayer::GetInstance()->GetResearchWeaponLevel()+1)))
				CPlayer::GetInstance()->UpgradeResearchWeaponLevel();
		}
		if(CPlayer::GetInstance()->GetResearchConsumableLevel() < 3 && IntersectRect(&temp, &m_MouseRECT, &m_ConsumableRECT))
		{
			if(CPlayer::GetInstance()->SpendMoney(100*(CPlayer::GetInstance()->GetResearchConsumableLevel()+1)))
				CPlayer::GetInstance()->UpgradeResearchConsumableLevel();
		}
	}
	return true;
}
void CResearchCenterState::Update(float fElapsedTime)
{
	m_MouseRECT.left = (LONG)CCursor::GetInstance()->GetPosX();
	m_MouseRECT.top = (LONG)CCursor::GetInstance()->GetPosY();
	m_MouseRECT.right = m_MouseRECT.left + 1;
	m_MouseRECT.bottom  = m_MouseRECT.top + 1;
}
void CResearchCenterState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBackgroundID, 0, 0);
	
	char buffer[16] = {0};

	sprintf_s(buffer, "Money:\n%d", CPlayer::GetInstance()->GetMoney());
	CBitmapFont::GetInstance()->Draw(buffer,20,20,0.75f);	
	CBitmapFont::GetInstance()->Draw("EXIT",450,30,0.75f);

	sprintf_s(buffer, "Fund: %d", 100*(CPlayer::GetInstance()->GetResearchArmorLevel()+1));
	CBitmapFont::GetInstance()->Draw((CPlayer::GetInstance()->GetResearchArmorLevel()<3)?buffer:"MAX",40,110,0.5f);
	sprintf_s(buffer, "Fund: %d", 100*(CPlayer::GetInstance()->GetResearchWeaponLevel()+1));
	CBitmapFont::GetInstance()->Draw((CPlayer::GetInstance()->GetResearchWeaponLevel()<3)?buffer:"MAX",250,110,0.5f);
	sprintf_s(buffer, "Fund: %d", 100*(CPlayer::GetInstance()->GetResearchConsumableLevel()+1));
	CBitmapFont::GetInstance()->Draw((CPlayer::GetInstance()->GetResearchConsumableLevel()<3)?buffer:"MAX",470,110,0.5f);

	CBitmapFont::GetInstance()->Draw("+2 Damage",0, 200, 1.0f);
	CBitmapFont::GetInstance()->Draw("+3 Damage",0, 300, 1.0f);
	CBitmapFont::GetInstance()->Draw("+5 Damage",0, 400, 1.0f);
	
	CBitmapFont::GetInstance()->Draw("+2 Armor",208, 200, 1.0f);
	CBitmapFont::GetInstance()->Draw("+3 Armor",208, 300, 1.0f);
	CBitmapFont::GetInstance()->Draw("+5 Armor",208, 400, 1.0f);
	
	CBitmapFont::GetInstance()->Draw("+20 Health",433, 200, 1.0f);
	CBitmapFont::GetInstance()->Draw("+30 Health",433, 300, 1.0f);
	CBitmapFont::GetInstance()->Draw("+50 Health",433, 400, 1.0f);

	for(int i = 0; i < 3 - CPlayer::GetInstance()->GetResearchArmorLevel(); i++)
		CSGD_TextureManager::GetInstance()->Draw(m_nAlphaID, -17, 393 - (i*110));
	for(int i = 0; i < 3 - CPlayer::GetInstance()->GetResearchWeaponLevel(); i++)
		CSGD_TextureManager::GetInstance()->Draw(m_nAlphaID, 208, 393 - (i*110));
	for(int i = 0; i < 3 - CPlayer::GetInstance()->GetResearchConsumableLevel(); i++)
		CSGD_TextureManager::GetInstance()->Draw(m_nAlphaID, 433, 393 - (i*110));
}
void CResearchCenterState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBackgroundID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nAlphaID);
}