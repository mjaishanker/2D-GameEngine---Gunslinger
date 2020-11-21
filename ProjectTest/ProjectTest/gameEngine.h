#ifndef GAMEENGINE_H
#define GAMEENGINE_H 

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h> 
#include <SDL_timer.h>
#include <vector>
#include "gameObject.h"
#include "TextureClass.h"
#include "Particle.h"
#include "ParticleManager.h"

// SDL allows us to create a renderer for the game engine class, when game engine is instatiated, call that renderer. In game object if we do sdl render copy, is also going to be needing that same renderer. So hand off that renderer to
// game object

class GameEngine {
public:
	GameEngine();
	~GameEngine();

	void init(const char* title, int xpos, int ypos, int width, int height);
	void handleEvents();
	void updateMechanics();
	void render();
	void quit();
	void LoadTextures(GameObject& go, const char* folderName, int textureCount, SDL_Rect src, SDL_Rect dest);
	void loadTexture(GameObject& myObj, const char* folderName, SDL_Rect src, SDL_Rect dest);
	void loadTexture(GameObject& myObj, const char* folderName, int numOfTextures, SDL_Rect src, SDL_Rect dest);
	void gameStart();
	void gameUpdate();
	void renderParticles();
	void addParticleEmmiter(ParticleManager PE);

	bool game_is_running = false;
	SDL_Window* gameEngine_window;
	SDL_Renderer* gameEngine_renderer;
	SDL_Event game_event;

	GameObject Player;

	int screenHeight, screenWidth, this_start_time, fps_counter = 0, last_count_start_time = 0, current_fps = 0, this_duration = 0, playerVel = 7;
	double deltaTime = 0;
	static std::vector<GameObject> allGameObjects;

};


#endif // GAMEENGINE
