#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H 
class State
{
public:
	// Player states -1(nostate), 0(Idle), 1(run right), 2(run left), 3(jump), 4(shoot), 5(slide)
	int stateID, frameCount;
	State();
	~State();
	void setStateID(int i);
	int getStateID();
	void setNumFrames(int i);
	int getNumFrames();

};

#endif
