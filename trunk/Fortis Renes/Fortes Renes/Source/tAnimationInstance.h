/**
 * Description:
 * 
 * This structure will contain the current frame, animation, and sheet for a game object. This allows direct access to all these variables for collision checks and frame based attacks.
 * 
 * Stipulations:
 * Will not contain any functions of its own must use other structures functions.
 * 
 * Interface:
 * Will not contain any functions.
 */
#pragma once
#include "tSheet.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"

struct tAnimationInstance
{

	/**
	 * pointer to time
	 */
	//float* currTime;
	/**
	 * pointer to frame
	 */
	tFrame* currFrame;
	/**
	 * pointer to current animation
	 */
	tAnimation* currAnimation;
	/**
	 * pointer to current sheet
	 */
	tSheet* currSheet;
	/**
	 * rect for animation
	 */
	//RECT PassiveRect;

	tAnimationInstance();

	void Render(float fPosX, float fPosY, float fScaleX, float fScaleY);

	void Update(float fElapsedTime);
};
