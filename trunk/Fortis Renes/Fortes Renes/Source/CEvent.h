//////////////////////////////////////////////////////////////////////////////
// File: "CEvent.h"
//
// Date Edited: 10/12/2010
//
// Purpose: Provide base for events that happen
//
//////////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CEVENT_H_
#define CEVENT_H_

// Nessisary includes
#include <string>
using std::string;

// Typedef to make reading code easier
typedef string EVENTID;		

//////////////////////////////////////////////////////////////////////////////
//	Class: CEvent
//
//	Notes: Events are passed when something happens in game
//////////////////////////////////////////////////////////////////////////////
class CEvent
{
private:
	// Event's ID
	EVENTID			m_EventID;
	// Store void* variable
	void*			m_pParam;

public:
	// Constructor
	CEvent(EVENTID eventID, void* pParam = NULL)
	{
		m_EventID = eventID;
		m_pParam  = pParam;
	}
	// Destructor
	~CEvent() {}

	//	Accessors
	EVENTID  GetEventID(void)	{ return m_EventID; }
	void*	GetParam(void)		{ return m_pParam; }
};
#endif