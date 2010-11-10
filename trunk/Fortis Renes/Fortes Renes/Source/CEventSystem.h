//////////////////////////////////////////////////////////////////////////////
// File: "CEventSystem.h"
//
// Date Edited: 10/12/2010
//
// Purpose: Process and send events when nessisary
//
//////////////////////////////////////////////////////////////////////////////

// Standard header protetion
#ifndef CEVENTSYSTEM_H_
#define CEVENTSYSTEM_H_

// Nessisary includes
#include <list>
#include <map>
using std::multimap;
using std::pair;
using std::list;

#include "CEvent.h"

// Forward declarations
class IListener;

//////////////////////////////////////////////////////////////////////////////
//	Class: CEventSystem
//
//	Notes: Process' and sends events and is a singleton
//////////////////////////////////////////////////////////////////////////////
class CEventSystem
{
private:
	//	Our Database, this will contain clients that can "listen" for events.
	multimap<EVENTID, IListener*>	m_ClientDatabase;

	//	Events waiting to be processed.
	list<CEvent>		m_CurrentEvents;

	// Constructors
	CEventSystem() {}
	CEventSystem(const CEventSystem&);
	// Assignment Operator
	CEventSystem& operator=(const CEventSystem&);
	// Destructor
	~CEventSystem() {}

	//	Utility functions 
	void DispatchEvent(CEvent* pEvent);
	bool AlreadyRegistered(EVENTID eventID, IListener* pClient);

public:

	// Gets the singleton instance
	static CEventSystem* GetInstance(void);

	//	This adds a client to the database
	void RegisterClient(EVENTID eventID, IListener* pClient);

	//	Unregisters the client for the specified event only
	void UnregisterClient(EVENTID eventID, IListener* pClient);

	//	Removes the client from the database entirely
	void UnregisterClientAll(IListener* pClient);

	//	Sends an event to be processed later on.
	void SendEvent(EVENTID eventID, void* pData = NULL);

	//	Processes all events in our event list.
	void ProcessEvents(void);

	//	Clears all pending events
	void ClearEvents(void);

	//	Unregisters all objects
	void ShutdownEventSystem(void);
};
#endif