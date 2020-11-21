#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
}

ParticleManager::ParticleManager(const char* name)
{
	this->name = name;
	
}

ParticleManager::~ParticleManager()
{
}

// Once particle emetter is initialized, assign respective values to it and pass in the particle to the particle class
void ParticleManager::ParticleManager_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int start_width, int start_height, int type, int lifeTime)
{
	srand(5);
	partType = type;
	int maxParts = MAX_PARTS;

	// if jump type or walk type, set x and y velocity and assign it to a particle
	if (partType == PART_TYPE_JUMP) {
		//std::cout << "Particle x, y, w, h, lifetime: " << start_x << ", " << start_y << ", " << start_width << ", " << start_height << ", " << lifeTime << std::endl;
		for (int i = 0; i < maxParts; i++) {
			allParticles[i].particle_init(graphic, ren, start_x, start_y, start_width, start_height, lifeTime);


			allParticles[i].setXVel(3 - (rand() % 60) / 10);
			allParticles[i].setYVel(0);
			//std::cout << "Particle xVel, yVel: " << allParticles[i].getXVel() << ", " << allParticles[i].getYVel() << std::endl;
		}
	}
	if (partType == PART_TYPE_WALK_RIGHT) {
		//std::cout << "Particle x, y, w, h, lifetime: " << start_x << ", " << start_y << ", " << start_width << ", " << start_height << ", " << lifeTime << std::endl;
		for (int i = 0; i < maxParts; i++) {
			allParticles[i].particle_init(graphic, ren, start_x, start_y, start_width, start_height, lifeTime);

			allParticles[i].setXVel(3 - (rand() % 60) / 10);
			allParticles[i].setYVel(-8);
			//std::cout << "Particle xVel, yVel: " << allParticles[i].getXVel() << ", " << allParticles[i].getYVel() << std::endl;
		}
	}
	if (partType == PART_TYPE_WALK_LEFT) {
		//std::cout << "Particle x, y, w, h, lifetime: " << start_x << ", " << start_y << ", " << start_width << ", " << start_height << ", " << lifeTime << std::endl;
		for (int i = 0; i < maxParts; i++) {
			allParticles[i].particle_init(graphic, ren, start_x, start_y, start_width, start_height, lifeTime);


			allParticles[i].setXVel(3 - (rand() % 60) / 10);
			allParticles[i].setYVel(-8);
			//std::cout << "Particle xVel, yVel: " << allParticles[i].getXVel() << ", " << allParticles[i].getYVel() << std::endl;
		}
	}
}

// Update all the particles
void ParticleManager::ParticleManager_update()
{
	int max_parts = MAX_PARTS;

	if (partType == PART_TYPE_JUMP) {
		max_parts = MAX_PARTS_JUMP;
		for (int i = 0; i < max_parts; i++) {
			allParticles[i].particle_update();
		}
	}
	if (partType == PART_TYPE_WALK_RIGHT) {
		max_parts = MAX_PARTS_WALK_RIGHT;
		for (int i = 0; i < max_parts; i++) {
			allParticles[i].particle_update();
		}
	}
	if (partType == PART_TYPE_WALK_LEFT) {
		max_parts = MAX_PARTS_WALK_LEFT;
		for (int i = 0; i < max_parts; i++) {
			allParticles[i].particle_update();
		}
	}
}

// render all the particles
void ParticleManager::ParticleManager_draw(SDL_Renderer* ren)
{
	int max_parts = MAX_PARTS;

	if (partType == PART_TYPE_JUMP) {
		max_parts = MAX_PARTS_JUMP;
		for (int i = 0; i < max_parts; i++) {
			allParticles[i].particle_draw(ren, 0);
		}
	}
	if (partType == PART_TYPE_WALK_RIGHT) {
		max_parts = MAX_PARTS_WALK_RIGHT;
		for (int i = 0; i < max_parts; i++) {
			allParticles[i].particle_draw(ren, 1);
		}
	}
	if (partType == PART_TYPE_WALK_LEFT) {
		max_parts = MAX_PARTS_WALK_LEFT;
		for (int i = 0; i < max_parts; i++) {
			allParticles[i].particle_draw(ren, 1);
		}
	}
}

int ParticleManager::getXPos()
{
	return this->x_pos;
}

int ParticleManager::getYPos()
{
	return this->y_pos;
}

void ParticleManager::setXPos(int newXpos)
{
	this->x_pos = newXpos;
}

void ParticleManager::setYPos(int newYpos)
{
	this->y_pos = newYpos;
}

