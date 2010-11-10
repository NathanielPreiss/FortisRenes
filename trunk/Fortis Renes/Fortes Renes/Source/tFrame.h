/**
 * 
 * Description:
 * The frame structure contains all the information for the particular frame of an animation. From how long the frame takes to the collision.
 * 
 * Stipulations:
 * Will not contain functions only data to be used by the other structures involved in the animations.
 * 
 * Interface:
 * There are no functions in the frames.
 */
#include <windows.h>
#include "DirectX Wrappers/SGD_Math.h"
#pragma once

struct tFrame
{

	/**
	 * duration of frame
	 */
	float fDuration;
	/**
	 * trigger boolean
	 */
	bool bTrigger;

	char* szTriggerName;
	/**
	 * color of particle
	 */
	DWORD dwColor;
	/**
	 * Rect for the particle to render
	 */
	RECT rDraw;
	RECT rCollision;
	/**
	 * collision bool
	 */
	bool bActiveCollision;
	/**
	 * starting position of particle
	 */
	int nAnchorX;
	int nAnchorY;

	tFrame();
};