#ifndef CSHOP_H_
#define CSHOP_H_

#include <vector>
using std::vector;

#include "CConsumable.h"

class CShop
{
private:
	vector<CConsumable*> m_vInventory;
	int m_nImageID;

public:
	void SellItem(CConsumable* pConsumable);
	void BuyItem(CConsumable* pConsumable);
};
#endif