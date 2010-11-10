////////////////////////////////////////////////////
// File: "CHowToPlayState.h"
//
// Date Edited: 10/14/2010
//
// Purpose: To load image to show player
//			controls of the game
////////////////////////////////////////////////////

#ifndef CHOWTOPLAYSTATE_H_
#define CHOWTOPLAYSTATE_H_

#include "IGameState.h"

class CHowToPlayState : public IGameState
{
private:
	int		m_nBackgroundID;

	CHowToPlayState(void);
	~CHowToPlayState(void);

public:
	static CHowToPlayState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);

};
#endif