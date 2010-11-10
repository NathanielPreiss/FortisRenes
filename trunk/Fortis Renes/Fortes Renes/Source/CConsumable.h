//////////////////////////////////////////////////////////////////////////////
// File: "CConsumable.h"
//
// Date Edited: 10/19/2010
//
// Purpose: 
//
//////////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CCONSUMABLE_H_
#define CCONSUMABLE_H_

// Nessisary header includes
#include "CBase.h"

//////////////////////////////////////////////////////////////////////////////
//	Class: CConsumable
//	
//	Notes: All pickups are this class
//////////////////////////////////////////////////////////////////////////////
class CConsumable : public CBase
{
private:
	int m_nItemID;

public:
	// Constructor
	CConsumable(int nItemID);
	// Destructor
	~CConsumable(void);

	void Render(float fCamPosX, float fCamPosY);

	void SetItemID(int nItemID){m_nItemID = nItemID;}
	int GetItemID(void) {return m_nItemID;}

	RECT GetRect(void);

	void HandleEvent( CEvent* pEvent );

};
#endif