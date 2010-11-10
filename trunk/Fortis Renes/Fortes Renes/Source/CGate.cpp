#include "CGate.h"
#include "DirectX Wrappers/SGD_Math.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CMessageSystem.h"
#include "CEventSystem.h"

CGate::CGate()
{
	SetType(OBJECT_GATE);

	CEventSystem::GetInstance()->RegisterClient("generator.destroyed",this);
}

CGate::~CGate()
{
	CEventSystem::GetInstance()->UnregisterClient("generator.destroyed",this);
}

void CGate::HandleEvent(CEvent* pEvent)
{
	if( pEvent->GetEventID() == "generator.destroyed" )
	{
		CBase* generator = (CBase*)pEvent->GetParam();

		tVector2D toGenerator;

		toGenerator.fX = generator->GetPosX() - GetPosX();
		toGenerator.fY = generator->GetPosY() - GetPosY();

		if( Vector2DLength(toGenerator) < 700 )
		{
			CMessageSystem::GetInstance()->SendMsg( new CDestroyBase(this));
		}
	}
}