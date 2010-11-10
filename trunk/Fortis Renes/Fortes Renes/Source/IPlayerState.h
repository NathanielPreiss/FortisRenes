#ifndef IPLAYERSTATE_H_
#define IPLAYERSTATE_H_

class IPlayerState
{
protected:
	IPlayerState(void) {}
	virtual ~IPlayerState(void) {}

public:
	virtual void Enter() {}

	virtual void Update(float fElapsedTime) = 0;
	virtual void Render(float fCamPosX, float fCamPosY) = 0;
};
#endif