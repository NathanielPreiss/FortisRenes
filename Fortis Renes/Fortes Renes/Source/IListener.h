//////////////////////////////////////////////////////////////////////////////
// File: "IListener.h"
//
// Date Edited: 10/12/2010
//
// Purpose: To provide a base class to derive classes that will need to 
//			listen for events.
//////////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef ILISTENER_H_
#define ILISTENER_H_

// Forward Declarations
class pEvent;
#include "CEvent.h"


//////////////////////////////////////////////////////////////////////////////
//	Class: IListener		
//
//	Notes: This class is needed for classes that will be "listening" for events
//////////////////////////////////////////////////////////////////////////////
class IListener
{
public:
	// Default Constructor
	IListener(void) {}
	// Destructor
	virtual ~IListener(void) {}

	// Class Interface Functions
	virtual void HandleEvent(CEvent* pEvent) = 0;
};
#endif