#ifndef CDIALOGUEMANAGER_H_
#define CDIALOGUEMANAGER_H_

#include <iostream>
using namespace std;

#include <vector>

//////////////////////////////////////////////////////////////////////
//	Each sentence is basically what shows up per box and will be
//		cycles through by hitting the enter button
//	The sentences contain a string for what is shown and an event
//		for flow of the game
//////////////////////////////////////////////////////////////////////

class CSentence
{
private:
	string m_szSentence;
	string m_szTrigger;
	bool m_bSendEvent;

public:
	CSentence(string szSentence, string szTrigger);

	string& GetSentence(void) { return m_szSentence; }
	string& GetTrigger(void) { return m_szTrigger; }
	bool GetEventBool(void) { return m_bSendEvent; }

	void SetEventBool(bool bSendEvent) { m_bSendEvent = bSendEvent; }
};

//////////////////////////////////////////////////////////////////////
//	Each script has a name and a vector of the sentences
//////////////////////////////////////////////////////////////////////

class CScript
{
private:
	string m_szScriptName;
	vector<CSentence*> m_vScript;

	int m_nCurrentSentence;

public:
	CScript(string szScriptName);
	~CScript(void);

	void AddSentence(CSentence* pSentence) { m_vScript.push_back(pSentence); }

	string& GetName(void) { return m_szScriptName; }

	void Render(void);
	void SetCurrentSentence(int nCS) { m_nCurrentSentence = nCS; }
	void CallEvent(void);

	int GetCurrentSentence(void) { return m_nCurrentSentence; }
};

//////////////////////////////////////////////////////////////////////
//	The dialogue manager holds all the scripts for dialogue
//		in the game
//////////////////////////////////////////////////////////////////////

class CDialogueManager
{
private:
	vector<CScript*> m_vScripts;
	int m_nScriptIndex;

	CDialogueManager(void);
	~CDialogueManager(void);
	CDialogueManager(const CDialogueManager&);
	CDialogueManager& operator=(const CDialogueManager&);

public:
	static CDialogueManager* GetInstance(void);

	void LoadDialogue(const char* szFilename);
	void UnloadDialogue(void);

	void UseProgressDialogue(void);
	void SetDialogue(const char* szName);

	void NextSentence(void);

	void Render(void);

};

#endif