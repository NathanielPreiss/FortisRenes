//////////////////////////////////////////////////////////////////////////////
// File: "CEventSystem.cpp"
//
// Date Edited: 10/12/2010
//
// Purpose: Fill out functions outlined in the header file
//
//////////////////////////////////////////////////////////////////////////////

// Nessisary includes
#include "CEventSystem.h"
#include "IListener.h"

////////////////////////////////////////////////////////
// Function: RegisterClient
// Paramaters: EVENTID eventID - What they are listening for
//			   IListener* pClient - Who is being registered
// Returns: void
////////////////////////////////////////////////////////
void CEventSystem::RegisterClient(EVENTID eventID, IListener* pClient)
{
	//	Error check to make sure the client exists and hasn't been registered for this event already.
	if (!pClient || AlreadyRegistered(eventID, pClient))	return;

	//	Register (Build) the database of clients.
	m_ClientDatabase.insert( make_pair(eventID, pClient) );
}

////////////////////////////////////////////////////////
// Function: GetInstance
// Paramaters: void
// Returns: CEventSystem* instance - Pointer to the singleton
////////////////////////////////////////////////////////
CEventSystem* CEventSystem::GetInstance(void)
{
	static CEventSystem instance;
	return &instance;
}

////////////////////////////////////////////////////////
// Function: UnregisterClient
// Paramaters: EVENTID eventID - What they are no longer listening to
//			   IListener* pClient - Who to unregister
// Returns: void
////////////////////////////////////////////////////////
void CEventSystem::UnregisterClient(EVENTID eventID, IListener *pClient)
{
	//	Make an iterator that will iterate all of our clients that
	//	should be receiveing this event
	pair<multimap<EVENTID, IListener*>::iterator,
		 multimap<EVENTID, IListener*>::iterator> range;

	//	Find all of the clients that are able to receive this event.
	range = m_ClientDatabase.equal_range(eventID);

	//	Go through the list of clients that are able to receive this event.
	for(multimap<EVENTID, IListener*>::iterator mmIter = range.first;
					mmIter != range.second; mmIter++)
	{
		//	check if the pointer is equal to the client
		if((*mmIter).second == pClient)
		{
			//	remove the client from the list
			mmIter = m_ClientDatabase.erase(mmIter);
			break;
		}
	}
}

////////////////////////////////////////////////////////
// Function: UnregisterClientAll
// Paramaters: IListener* pClient - Who to unregister
// Returns: void 
////////////////////////////////////////////////////////
void CEventSystem::UnregisterClientAll(IListener *pClient)
{
	multimap<string, IListener*>::iterator mmIter = m_ClientDatabase.begin();

	while(mmIter !=m_ClientDatabase.end())
	{
		if((*mmIter).second == pClient)
		{
			mmIter = m_ClientDatabase.erase(mmIter);
		}
		else
			mmIter++;
	}
}

////////////////////////////////////////////////////////
// Function: DispatchEvent
// Paramaters: CEvent* pEvent - What event is being dispatched
// Returns: void
////////////////////////////////////////////////////////
void CEventSystem::DispatchEvent(CEvent *pEvent)
{
	//	Make an iterator that will iterate all of our clients that
	//	should be receiveing this event
	pair<multimap<EVENTID, IListener*>::iterator,
		 multimap<EVENTID, IListener*>::iterator> range;

	//	Find all of the clients that are able to receive this event.
	range = m_ClientDatabase.equal_range(pEvent->GetEventID());

	//	Go through the linked list of clients that are able to receive this event.
	for(multimap<EVENTID, IListener*>::iterator mmIter = range.first;
					mmIter != range.second; mmIter++)
	{
		//	Pass this event to the client
		(*mmIter).second->HandleEvent(pEvent);
	}
}

////////////////////////////////////////////////////////
// Function: AlreadyRegistered
// Paramaters: EVENTID eventID - What event to check for
//			   IListener* pClient - Who to check if they are registered
// Returns: bool bIsAlreadyRegistered - Returns if client has been registered for that event
////////////////////////////////////////////////////////
bool CEventSystem::AlreadyRegistered(EVENTID eventID, IListener* pClient)
{
	bool bIsAlreadyRegistered = false;

	//	Make an iterator that will iterate all of our clients that
	//	should be receiveing this event
	pair<multimap<EVENTID, IListener*>::iterator,
		 multimap<EVENTID, IListener*>::iterator> range;

	//	Find all of the clients that are able to receive this event.
	range = m_ClientDatabase.equal_range(eventID);

	//	Go through the list of clients that are able to receive this event.
	for(multimap<EVENTID, IListener*>::iterator mmIter = range.first;
					mmIter != range.second; mmIter++)
	{
		//	check if the pointer is equal to the client
		if((*mmIter).second == pClient)
		{
			bIsAlreadyRegistered = true;
			break;
		}
	}
	return bIsAlreadyRegistered;
}

////////////////////////////////////////////////////////
// Function: SendEvent
// Paramaters: EVENTID eventID - Event to be pushed into the list
//			   void* pData - Can be anything
// Returns: void
////////////////////////////////////////////////////////
void CEventSystem::SendEvent(EVENTID eventID, void* pData)
{
	//	Push my event into the list.
	CEvent newEvent(eventID, pData);

	m_CurrentEvents.push_back(newEvent);
}

////////////////////////////////////////////////////////
// Function: ProcessEvents
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CEventSystem::ProcessEvents(void)
{
	//	Go through my list of events that are waiting to be processed.
	while(m_CurrentEvents.size())
	{
		DispatchEvent(&m_CurrentEvents.front());
		m_CurrentEvents.pop_front();
	}
}

////////////////////////////////////////////////////////
// Function: ClearEvents
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CEventSystem::ClearEvents(void)
{
	m_CurrentEvents.clear();
}

////////////////////////////////////////////////////////
// Function: ShutdownEventSystem
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CEventSystem::ShutdownEventSystem(void)
{
	m_ClientDatabase.clear();
}