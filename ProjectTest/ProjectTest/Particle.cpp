#include "Particle.h"

Particle::Particle()
{
}

Particle::~Particle()
{
}

// Once the particle emitter is initialized the graphic is sent to the particle class
void Particle::particle_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int width, int height, int lifeTime)
{
	// read the textures and assign it to the sdl rect of this particle

	//std::cout << "Particle x, y, w, h, lifetime: " << start_x << ", " << start_y << ", " << width << ", " << height << ", " << lifeTime << std::endl;
	SDL_Surface* tempSurface;
	SDL_Texture* tempTex;


	int frameWidth, frameHeight, textureWidth, textureHeight;

	tempSurface = IMG_Load(graphic);

	//if (tempSurface != NULL)
		//std::cout << "Particle tex load" << std::endl;
	//else
		//std::cout << "Particle tex load" << std::endl;


	tempTex = SDL_CreateTextureFromSurface(ren, tempSurface);

	/*SDL_QueryTexture(tempTex, NULL, NULL, &textureWidth, &textureHeight);
	frameWidth = textureWidth / 3;
	frameHeight = textureHeight / 4;*/

	obj_rect.x = start_x;
	obj_rect.y = start_y;
	x_pos = start_x;
	y_pos = start_y;
	obj_rect.w = width;
	obj_rect.h = height;
	lifetime = lifeTime;
	//std::cout << "Particle x, y, w, h, lifetime: " << start_x << ", " << start_y << ", " << width << ", " << height << ", " << lifeTime << std::endl;
	obj_graphic = tempTex;

	SDL_FreeSurface(tempSurface);
}

void Particle::particle_update()
{
	// update the velocity, position and lifetime of the particle
	//std::cout << "Particle x, y: " << x_pos << ", " << y_pos << std::endl;
	x_pos += x_vel;
	y_pos += y_vel;
	
	y_vel += 9.8 * 100 / 3600;
	if (lifetime > 0) {
		//obj_rect.x = (int) x_pos;
		//obj_rect.y = (int) y_pos;
		obj_rect.x = x_pos;
		obj_rect.y = y_pos;

		/*obj_rect.w = (int) width / 2 + width * (int) (10*lifetime/100);
		obj_rect.h = (int) height / 2 + height * (int)(10 * lifetime / 100);*/
	}
	lifetime -= 1;
}

void Particle::particle_draw(SDL_Renderer* ren, int alphaNum)
{
	// Draw the particle to the game engine renderer
	//std::cout << "Particle x, y, w, h, lifetime: " << obj_rect.x << ", " << obj_rect.y << ", " << obj_rect.w << ", " << obj_rect.h << ", " << lifetime << std::endl;
	if (alphaNum == 0) {
		if (lifetime > 0) {
			SDL_RenderCopy(ren, obj_graphic, NULL, &obj_rect);
		}
	}
	else {
		if (lifetime > 0) {
			SDL_SetTextureAlphaMod(obj_graphic, (int)255 * lifetime / 20);
			SDL_RenderCopy(ren, obj_graphic, NULL, &obj_rect);
		}
		else {
			SDL_SetTextureAlphaMod(obj_graphic, 255);
		}
	}
}

void Particle::particle_quit()
{
	SDL_DestroyTexture(obj_graphic);
}

int Particle::getXPos()
{
	return this->x_pos;
}

int Particle::getXVel()
{
	return this->x_vel;
}

int Particle::getYPos()
{
	return this->y_pos;
}

int Particle::getYVel()
{
	return this->y_vel;
}

void Particle::setXPos(int newXpos)
{
	this->x_pos = newXpos;
}

void Particle::setXVel(int newXVel)
{
	this->x_vel = newXVel;
}

void Particle::setYPos(int newYpos)
{
	this->y_pos = newYpos;
}

void Particle::setYVel(int newYVel)
{
	this->y_vel = newYVel;
}

void Particle::setLifeTime(int newLT)
{
	this->lifetime = newLT;
}
