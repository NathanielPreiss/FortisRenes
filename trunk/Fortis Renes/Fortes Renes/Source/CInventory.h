//////////////////////////////////////////////////////////////////////////////
// File: "CInventory.h"
//
// Date Edited: 10/16/2010
//
// Purpose: Class to hold onto the players inventory
//
//////////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CINVENTORY_H_
#define CINVENTORY_H_

// Nessisary includes 
#include "CConsumable.h"

//////////////////////////////////////////////////////////////////////////////
//	Class: cInventory
//
//	Notes: 
//////////////////////////////////////////////////////////////////////////////
class CInventory
{
private:
	int m_Inventory[CON_NUMBER];	// array of the available consumables
	int m_nMedkitID;
	int m_nAdrenalineID;

public:
	CInventory(void);
	~CInventory(void) {}
	void PickUpItem(int nType); // Try and add an item to the vector
	bool UseItem(int nItem);	// Player tries to use current item
	void ReduceNumItem(int nItem) { m_Inventory[nItem]--; }  // Reduce the item by 1;

	void Render(int currItem);

	int GetNumItem(int nItem);	// Returns how many of a specific item are being carried
	void ClearInventory(void);	// Set all items to 0
};
#endif