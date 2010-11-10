#include "tFrame.h"

tFrame::tFrame()
{
	
	fDuration = 0.0f;
	
	bTrigger = false;
	
	dwColor = 0;

	szTriggerName = "Trigger";
	
	rDraw.left = 0;
	rDraw.right = 0;
	rDraw.top = 0;
	rDraw.bottom = 0;

	rCollision.left = 0;
	rCollision.right = 0;
	rCollision.top = 0;
	rCollision.bottom = 0;

	bActiveCollision = true;

	nAnchorX = 0;
	nAnchorY = 0;
}