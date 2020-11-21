#include "State.h"

State::State() {}
State::~State(){}

void State::setStateID(int id)
{
	this->stateID = id;
}

int State::getStateID()
{
	return this->stateID;
}

void State::setNumFrames(int i)
{
	this->frameCount = i;
}

int State::getNumFrames()
{
	return this->frameCount;
}
