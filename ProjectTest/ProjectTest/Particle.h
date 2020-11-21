#ifndef PARTICLE_H
#define PARTICLE_H 

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

class Particle {
public:
	Particle();
	~Particle();

	void particle_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int width, int height, int lifeTime);
	void particle_update();
	// inform renderer of the main game loop
	void particle_draw(SDL_Renderer* ren, int alphaNum);
	void particle_quit();

	// getters and setters
	int getXPos(), getXVel(), getYPos(), getYVel();
	void setXPos(int newXpos), setXVel(int newXVel), setYPos(int newYpos), setYVel(int newYVel), setLifeTime(int newLT);

	int texCount, objVel = 0, x_pos = 0, y_pos = 0, screen_width = 640, screen_height = 480;
    int maxVel = 0, minVel = 0, x_vel = 0, y_vel = 0, lifetime, width, height, state;

	SDL_Renderer* obj_renderer;
	SDL_Texture* obj_graphic;
	SDL_Rect obj_rect, obj_srcRect;
};

#endif
