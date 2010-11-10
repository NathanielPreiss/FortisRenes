//////////////////////////////////////////////////////////////////////////////
// File: "CMessageSystem.cpp"
//
// Date Edited: 10/12/2010
//
// Purpose: Fills functions declared in "CMessage.h"
//
//////////////////////////////////////////////////////////////////////////////

// Nessessary includes
#include "CMessageSystem.h"

////////////////////////////////////////////////////////
// Function: GetInstance
// Paramaters: void
// Returns: CMessageSystem* instance - pointer to the singleton
////////////////////////////////////////////////////////
CMessageSystem* CMessageSystem::GetInstance(void)
{
	static CMessageSystem instance;	// Can only be one of them
	return &instance;				// Return address of this
}

////////////////////////////////////////////////////////
// Function: InitMessageSystem
// Paramaters: MESSAGEPROC pfnMsgProc
// Returns: void
////////////////////////////////////////////////////////
void CMessageSystem::InitMessageSystem(MESSAGEPROC pfnMsgProc)
{
	//	Error check to make sure the message proc is valid.
	if (!pfnMsgProc)	return;

	//	Get the Msg Proc
	m_pfnMsgProc = pfnMsgProc;
}

////////////////////////////////////////////////////////
// Function: SendMsg
// Paramaters: CBaseMessage* pMsg - pointer to the message
// Returns: void
////////////////////////////////////////////////////////
void CMessageSystem::SendMsg(CBaseMessage* pMsg)
{
	//	Make sure the message exists.
	if (!pMsg)	return;

	//	Send the message to the queue for processing later on.
	m_MsgQueue.push(pMsg);
}

////////////////////////////////////////////////////////
// Function: ProcessMessages
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CMessageSystem::ProcessMessages(void)
{
	// This is called once a frame
	//	Error check to make sure we get a message proc.
	if(!m_pfnMsgProc)	return;

	//	go through the entire queue and process the messsages that are waiting.
	while(!m_MsgQueue.empty())
	{
		m_pfnMsgProc(m_MsgQueue.front());		//	Process the first message.
		delete m_MsgQueue.front();				//	Delete the message memory.
		m_MsgQueue.pop();						//	Go to the next message.
	}
}

////////////////////////////////////////////////////////
// Function: ClearMessages
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CMessageSystem::ClearMessages(void)
{
	//	Clear out any messages waititng.
	while(!m_MsgQueue.empty())
	{
		delete m_MsgQueue.front();
		m_MsgQueue.pop();
	}
}

////////////////////////////////////////////////////////
// Function: ShutdownMessageSystem
// Paramaters: void 
// Returns: void
////////////////////////////////////////////////////////
void CMessageSystem::ShutdownMessageSystem(void)
{
	//	Clear out any messages waiting.
	ClearMessages();

	//	Clear the function pointer
	m_pfnMsgProc = NULL;
}