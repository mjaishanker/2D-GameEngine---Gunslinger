#ifndef TEXTURE_H
#define TEXTURE_H 

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h> 
#include <SDL_timer.h>
#include <vector>


class Texture {

public:
	SDL_Rect srcTextureRect;
	SDL_Rect destTextureRect;
	SDL_Texture* SDLTexture;

};


#endif // TextureClass