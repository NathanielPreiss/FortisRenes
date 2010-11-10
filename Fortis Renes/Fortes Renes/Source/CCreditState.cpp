///////////////////////////////////////////////////
// File: "CCreditState.cpp"
//
// Date Edited: 10/14/2010
//
// Purpose: Fill functions that are declared in
//			class header
//////////////////////////////////////////////////

#include "CMainMenuState.h"
#include "CCreditState.h"
#include "DirectX Wrappers/CSGD_WaveManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CGame.h"
#include "Tinyxml/tinyxml.h"

CCreditState::CCreditState(void)
{
	m_nBackgroundID = 0;
}
CCreditState::~CCreditState(void)
{
}
CCreditState* CCreditState::GetInstance(void)
{
	static CCreditState instance;
	return &instance;
}
void CCreditState::Enter(void)
{
	// Load texture
	m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/CreditStateBG.jpg");
	LoadCredits();
	m_fScrollPosition = 500.0f;
}
void CCreditState::LoadCredits(void)
{
	TiXmlDocument doc;

	if(doc.LoadFile("Resource/Data/Credits.xml") == false)
		return;
	
	TiXmlElement* pCredit = doc.RootElement()->FirstChildElement();

	while(pCredit)
	{
		char* temp = new char[64];
		const char* szName = pCredit->GetText();
		if(!szName)
		{
			temp[0] = ' ';
			m_vCredits.push_back(temp);
			pCredit = pCredit->NextSiblingElement();
			continue;
		}
		for(int i = 0; i < 64; i++)
			temp[i] = szName[i];

		m_vCredits.push_back(temp);
		pCredit = pCredit->NextSiblingElement();
	}	
}
bool CCreditState::Input(void)
{
	if(CSGD_DirectInput::GetInstance()->CheckBufferedKeysEx())
			CGame::GetInstance()->RemoveTopState();

	return true;
}
void CCreditState::Update(float fElapsedTime)
{
	m_fScrollPosition -= 120.0f * fElapsedTime;
	if(m_fScrollPosition < -(int)(CBitmapFont::GetInstance()->GetCharHeight() * m_vCredits.size()+100) )
		CGame::GetInstance()->RemoveTopState();
		
}
void CCreditState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw( m_nBackgroundID, 0, 0 );
	for(unsigned int i = 0; i < m_vCredits.size(); i++)
	{
		CBitmapFont::GetInstance()->DrawCenter(m_vCredits[i], 320, (int)((32*i)+m_fScrollPosition), 1.0);
	}
}
void CCreditState::UnloadCredits(void)
{
	for(unsigned int i = 0; i < m_vCredits.size(); i++)
	{
		delete m_vCredits[i];
	}
	m_vCredits.clear();
}
void CCreditState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBackgroundID);
	UnloadCredits();
}