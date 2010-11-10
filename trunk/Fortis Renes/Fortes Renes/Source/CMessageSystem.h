//////////////////////////////////////////////////////////////////////////////
// File: "CMessageSystem.h"
//
// Date Edited: 10/12/2010
//
// Purpose: Handle messages that are passed from class to class
//
//////////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CMESSAGESYSTEM_H_
#define CMESSAGESYSTEM_H_

// Includes for nessisary headers
#include <queue>
using std::queue;

#include "CMessages.h"

typedef void (*MESSAGEPROC)(CBaseMessage*);

//////////////////////////////////////////////////////////////////////////////
//	Class: CMessageSystem
//
//	Notes: Process' all messages
//////////////////////////////////////////////////////////////////////////////
class CMessageSystem
{
private:
	// Queue to store the list of messages
	queue<CBaseMessage*>		m_MsgQueue;	
	// Holds the message function
	MESSAGEPROC					m_pfnMsgProc;

	// Constructors
	CMessageSystem() { m_pfnMsgProc = NULL;	}
	CMessageSystem(const CMessageSystem&);
	// Destructor
	~CMessageSystem() {}	
	
	// Assignment Operator
	CMessageSystem& operator=(const CMessageSystem&);

public:
	
	// Get singleton isntance
	static CMessageSystem* GetInstance(void);

	//	Accessors
	int GetNumMessages(void) { return (int)m_MsgQueue.size(); }

	//	Setup the function pointer for our messages.
	void InitMessageSystem(MESSAGEPROC pfnMsgProc);

	//	Sends message into the queue 
	void SendMsg(CBaseMessage* pMsg);

	//	Processes messages that are waiting in queue
	void ProcessMessages(void);

	//	Clears remaining messages
	void ClearMessages(void);

	//	Clears messages and sets function pointer to NULL
	void ShutdownMessageSystem(void);
};
#endif