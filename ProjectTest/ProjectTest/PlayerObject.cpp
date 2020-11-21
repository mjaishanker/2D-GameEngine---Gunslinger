#include "PlayerObject.h"


PlayerObject::PlayerObject()
{
	texCount = 0;
}

PlayerObject::PlayerObject(SDL_Renderer* ren)
{
}

PlayerObject::PlayerObject(const char* name, int maxVel, int minVel, int beginStateID)
{
	texCount = 0;
	this->name = name;
	this->maxVel = maxVel;
	this->minVel = minVel;
	this->objState.setStateID(beginStateID);
	GameEngine::allGameObjects.push_back(*this);
}

PlayerObject::PlayerObject(const char* name, int maxVel, int minVel, int beginStateID, int initPosX, int initPosY, int initPosW, int initPosH, int initSrcX, int initSrcY, int initSrcW, int initSrcH)
{
	texCount = 0;
	this->name = name;
	this->maxVel = maxVel;
	this->minVel = minVel;
	this->objState.setStateID(beginStateID);
	this->obj_rect.x = initPosX;
	this->obj_rect.y = initPosY;
	this->obj_rect.w = initPosW;
	this->obj_rect.h = initPosH;
	this->obj_srcRect.x = initSrcX;
	this->obj_srcRect.y = initSrcY;
	this->obj_srcRect.w = initSrcW;
	this->obj_srcRect.h = initSrcH;

	GameEngine::allGameObjects.push_back(*this);
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::obj_update()
{
}

int PlayerObject::getXPos()
{
	return this->x_pos;
}

int PlayerObject::getXVel()
{
	return this->x_vel;
}

int PlayerObject::getYPos()
{
	return this->y_pos;
}

int PlayerObject::getYVel()
{
	return this->y_vel;
}

void PlayerObject::setXPos(int newXpos)
{
	this->x_pos = newXpos;
}

void PlayerObject::setXVel(int newXVel)
{
	this->x_vel = newXVel;
}

void PlayerObject::setYPos(int newYpos)
{
	this->y_pos = newYpos;
}

void PlayerObject::setYVel(int newYVel)
{
	this->y_vel = newYVel;
}


