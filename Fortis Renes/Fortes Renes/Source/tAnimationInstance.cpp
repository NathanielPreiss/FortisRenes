#include "tAnimationInstance.h"
#include "CEventSystem.h"

tAnimationInstance::tAnimationInstance()
{
	currFrame		= NULL;

	currAnimation	= NULL;
	
	currSheet		= NULL;
}

void tAnimationInstance::Render(float fPosX, float fPosY, float fScaleX, float fScaleY)
{
	CSGD_TextureManager::GetInstance()->Draw(currSheet->ImageID, (int)fPosX, (int)fPosY, fScaleX, fScaleY, &currFrame->rDraw);
}

void tAnimationInstance::Update(float fElapsedTime)
{
	if(!currAnimation)
		currAnimation = currSheet->m_vAnimations[0];

	//	if it is not playing, quit function
	if(!currAnimation->bIsPlaying)
		return;

	currFrame = currAnimation->m_vFrames[currAnimation->nCurrFrame];
	
	//	update time waited
	currAnimation->fTimeWaited += fElapsedTime;

	//	see if it is time to change frames
	if(currAnimation->fTimeWaited > currFrame->fDuration)
	{
		currAnimation->fTimeWaited = 0.0f;
		//	Increment the frame
		currAnimation->nCurrFrame++;

		//	Check if at end of anim
		if (currAnimation->nCurrFrame >= currAnimation->m_vFrames.size())
		{
			if(currAnimation->bIsLooping)
				currAnimation->nCurrFrame = 0;
			else
			{
				currAnimation->Stop();
				currAnimation->nCurrFrame = currAnimation->m_vFrames.size() - 1;
			}
		}
	}

	if( currAnimation->m_vFrames[currAnimation->nCurrFrame]->bTrigger == true )
	{
		CEventSystem::GetInstance()->SendEvent(currAnimation->m_vFrames[currAnimation->nCurrFrame]->szTriggerName,this);
	}
}