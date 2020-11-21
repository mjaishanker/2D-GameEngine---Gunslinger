#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H 

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
#include "Particle.h"
#include "ParticleManager.h"
// player, enemy are gameobjects. init (img_load // textures), update (sdl_rect.x += 5), renderer, quit

class GameObject {

public:
	GameObject();
	GameObject(SDL_Renderer* ren);
	GameObject(const char *name, int maxVel, int minVel, int beginStateID);
	GameObject(const char* name, int maxVel, int minVel, int beginStateID, int initPosX, int initPosY, int initPosW, int initPosH, 
		int initSrcX, int initSrcY, int initSrcW, int initSrcH, SDL_Renderer* gameRenderer);
	~GameObject();

	void obj_init();
	void obj_update();
	// inform renderer of the main game loop
	void obj_render();
	void obj_quit();
	void transformObj(int x, int y, float velocity);
	int getXPos(), getXVel(), getYPos(), getYVel();
	void setXPos(int newXpos), setXVel(int newXVel), setYPos(int newYpos), setYVel(int newYVel);
	void findGameObjectByName(const char* name, GameObject& tempObj);
	void findParticleEmitterByName(const char* name, ParticleManager& tempPartEmm);

	bool IntersectsWith(GameObject &otherObj);

	SDL_Renderer *obj_renderer;
	SDL_Texture *objInstantiateTexture;
	SDL_Surface* objInitiateSurface;
	const SDL_Rect *const_obj_rect, *const_obj_srcRect;
	SDL_Rect obj_rect, obj_srcRect;
	char* artFolder;
	int texCount, objVel = 0, x_pos = 0, y_pos = 0, screen_width = 640, screen_height = 480, maxVel = 0, minVel = 0, x_vel = 0, y_vel = 0, particleEmmitCount, maxParticleTimer = 150, particleTimerCount = 0;
	const char* name;
	//int objectState; // 0 to move, 1 to jump, 3 to shoot (0, 1, 2 is core for all char), 4 to slide

	
	
	std::vector<Texture> textures;
	// List of particle emitters for the game objects
	std::vector<ParticleManager> particlesEmitters;
	State objState;
	Sprite objSprite;
};

#endif // GAMEENGINE
