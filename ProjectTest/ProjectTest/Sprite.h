#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h> 
#include <SDL_timer.h>
#include <vector>

class Sprite {
public:
	Sprite();
	~Sprite();
	void spriteUpdate(int frameCount, int frameDuration, SDL_Rect &srcTextureRect, int row);

	int frameCount, frameDuration;
};

#endif