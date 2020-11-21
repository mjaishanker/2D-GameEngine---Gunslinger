#include "Sprite.h"

Sprite::Sprite(){}


Sprite::~Sprite(){}

void Sprite::spriteUpdate(int frameCount, int frameDuration, SDL_Rect &srcTextureRect, int row)
{
	srcTextureRect.y = row * srcTextureRect.h;
	frameCount = frameCount;
	frameDuration = frameDuration;
	int frame_time = (int)(SDL_GetTicks() / frameCount) % frameDuration;
	//std::cout << "Frame: " << frame_time << std::endl;

	static int last_frame_time = 0;

	if (last_frame_time != frame_time) {
		if (frame_time < 1) { // reset sprite x
			srcTextureRect.x = 0;
		}
		else {
			srcTextureRect.x += srcTextureRect.w;
		}
	}

	last_frame_time = frame_time;
}
