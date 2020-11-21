#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

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

// basic traits of a player object, jump walk left and right and intialize max particles for them
const int MAX_PARTS = 10, MAX_PARTS_JUMP = 10, MAX_PARTS_WALK_RIGHT = 2, MAX_PARTS_WALK_LEFT = 2;
const int PART_TYPE_JUMP = 3, PART_TYPE_WALK_RIGHT = 1, PART_TYPE_WALK_LEFT = 2;
class ParticleManager {
public:
	ParticleManager();
	ParticleManager(const char* name);
	~ParticleManager();

	void ParticleManager_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int width, int height, int type, int lifeTime);
	void ParticleManager_update(); //update all particles
	// inform renderer of the main game loop
	void ParticleManager_draw(SDL_Renderer* ren); // draw all particles if theyre alive
	void ParticleManager_quit();

	int getXPos(), getYPos();
	void setXPos(int newXpos), setYPos(int newYpos);

	Particle allParticles[MAX_PARTS]; // holds all particles

	int x_pos = 0, y_pos = 0, partType;
	const char* name;
};

#endif