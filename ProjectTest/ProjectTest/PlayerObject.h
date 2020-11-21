#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H 
#include <iostream>
#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h> 
#include <SDL_timer.h>
#include <vector>
#include "TextureClass.h"
#include "State.h"
#include "Sprite.h"
#include "gameObject.h"
#include "gameEngine.h"

class PlayerObject : public GameObject
{
public:
	PlayerObject();
	PlayerObject(SDL_Renderer* ren);
	PlayerObject(const char* name, int maxVel, int minVel, int beginStateID);
	PlayerObject(const char* name, int maxVel, int minVel, int beginStateID, int initPosX, int initPosY, int initPosW, int initPosH,
		int initSrcX, int initSrcY, int initSrcW, int initSrcH);
	~PlayerObject();

	void obj_update();
	int getXPos(), getXVel(), getYPos(), getYVel();
	void setXPos(int newXpos), setXVel(int newXVel), setYPos(int newYpos), setYVel(int newYVel);

	SDL_Renderer* obj_renderer;
	SDL_Texture* objInstantiateTexture;
	SDL_Rect obj_rect, obj_srcRect;
	char* artFolder;
	int texCount, objVel = 0, x_pos = 0, y_pos = 0, screen_width = 640, screen_height = 480, maxVel = 0, minVel = 0, x_vel = 0, y_vel = 0;
	const char* name;
	//int objectState; // 0 to move, 1 to jump, 3 to shoot (0, 1, 2 is core for all char), 4 to slide



	std::vector<Texture> textures;

	State objState;
	Sprite objSprite;
};
#endif
