#include "CDialogueManager.h"
#include "CBitmapFont.h"
#include "CEventSystem.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "CPlayer.h"
#include "CGame.h"
#include <fstream>
using namespace std;

CSentence::CSentence(std::string szSentence, std::string szTrigger)
{
	m_szSentence = szSentence;
	m_szTrigger = szTrigger;
}

CScript::CScript(std::string szScriptName)
{
	m_nCurrentSentence = 0;
	m_szScriptName = szScriptName;
}

CScript::~CScript()
{
	for( unsigned int i = 0; i < m_vScript.size(); i++ )
	{
		delete (m_vScript[i]);
	}
}

void CScript::Render()
{
	if( m_nCurrentSentence == m_vScript.size() )
	{
		CGame::GetInstance()->RemoveTopState();
		return;
	}

	CBitmapFont::GetInstance()->Draw(m_vScript[m_nCurrentSentence]->GetSentence().c_str(),25,CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferHeight-120,0.75f);
}

CDialogueManager::CDialogueManager()
{
}

CDialogueManager::~CDialogueManager()
{
}

CDialogueManager* CDialogueManager::GetInstance()
{
	static CDialogueManager instance;
	return &instance;
}

void CDialogueManager::LoadDialogue(const char *szFilename)
{
	int scriptNum;
	int sentenceNum;
	int strLen;
	char* buffer;
	// Load in all the dialogue from file at beginning of game
	ifstream in;

	in.open(szFilename,ios_base::in | ios_base::binary);

	if( in.is_open() )
	{
		in.read((char*)&scriptNum,sizeof(int));

		for( int script = 0; script < scriptNum; script++ )
		{
			in.read((char*)&strLen,sizeof(int));
			buffer = new char[strLen+1];
			in.read(buffer,strLen);
			buffer[strLen] = '\0';
			string szName = buffer;
			CScript* newScript = new CScript(szName);

			delete[] buffer;

			in.read((char*)&sentenceNum,sizeof(int));
			for( int sentence = 0; sentence < sentenceNum; sentence++ )
			{
				in.read((char*)&strLen,sizeof(int));
				buffer = new char[strLen+1];
				in.read(buffer,strLen);
				buffer[strLen] = '\0';
				string szSentence = buffer;
				
				delete[] buffer;

				in.read((char*)&strLen,sizeof(int));
				buffer = new char[strLen+1];
				in.read(buffer,strLen);
				buffer[strLen] = '\0';
				string szTrigger = buffer;

				delete[] buffer;

				CSentence* newSentence = new CSentence(szSentence,szTrigger);
				if( strLen < 1 )
					newSentence->SetEventBool(false);
				else
					newSentence->SetEventBool(true);

				newScript->AddSentence(newSentence);
			}

			m_vScripts.push_back(newScript);
		}
	}
}

void CDialogueManager::UnloadDialogue()
{
	// Unload the dialogues from the game
	for( unsigned int i = 0; i < m_vScripts.size(); i++ )
	{
		delete (m_vScripts[i]);
	}
}

void CDialogueManager::Render(void)
{
	m_vScripts[m_nScriptIndex]->Render();
}

void CDialogueManager::UseProgressDialogue(void)
{
	switch( CPlayer::GetInstance()->GetProgress() )
	{
	case 0:
		SetDialogue("LeavePrison");
		break;
	case 1:
		SetDialogue("Mission1");
		break;
	case 2:
		SetDialogue("Mission2");
		break;
	case 3:
		SetDialogue("Mission3");
		break;
	case 4:
		SetDialogue("Mission4");
		break;
	case 5:
		SetDialogue("SiegeMission");
	};
}

void CDialogueManager::SetDialogue(const char* szName)
{
	for( unsigned int i = 0; i < m_vScripts.size(); i++ )
	{
		if( m_vScripts[i]->GetName() == szName )
		{
			m_nScriptIndex = i;
			break;
		}
	}
	m_vScripts[m_nScriptIndex]->SetCurrentSentence(0);
}

void CDialogueManager::NextSentence()
{
	m_vScripts[m_nScriptIndex]->CallEvent();
	m_vScripts[m_nScriptIndex]->SetCurrentSentence(m_vScripts[m_nScriptIndex]->GetCurrentSentence()+1);
}

void CScript::CallEvent()
{
	if( m_vScript[m_nCurrentSentence]->GetEventBool() == true )
	{
		CEventSystem::GetInstance()->SendEvent(m_vScript[m_nCurrentSentence]->GetTrigger());
		m_vScript[m_nCurrentSentence]->SetEventBool(false);
	}
}