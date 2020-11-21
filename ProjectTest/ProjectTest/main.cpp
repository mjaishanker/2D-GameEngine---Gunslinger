#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h> 
#include <SDL_timer.h>

#include "gameEngine.h"
#include "gameObject.h"
#include "PlayerObject.h"
#include "Particle.h"
#include "ParticleManager.h"

#undef main

const int fps = 60;
const int frame_duration = 1+ 1000 / fps; // time of a frame in a milliseconds

Uint64 NOW = SDL_GetPerformanceCounter();
Uint64 LAST = 0;
double deltaTime = 0;

//Screen dimension
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* my_window = NULL;
SDL_Renderer* my_renderer = NULL;
SDL_Event input;
ParticleManager *walkDust = new ParticleManager("WalkDust");

void my_SDL_init() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}
	else {
		std::cout << "Finished SDL_init" << std::endl;
	}

	//Enable gpu_enhanced textures
	IMG_Init(IMG_INIT_PNG);

	my_window = SDL_CreateWindow("my_game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT, 0);
	my_renderer = SDL_CreateRenderer(my_window, -1, 0);

}

void GameEngine::gameStart()
{
	SDL_Rect src, backSrc;
	SDL_Rect dest, backDest;

	//src.x = 0;
	//src.y = 0;
	//src.w = 300;
	//src.h = 300;

	//dest.x = 0;
	//dest.y = 320;
	//dest.w = 150;
	//dest.h = 150;

	//backDest.x = 0;
	//backDest.y = 0;
	//backDest.w = 640;
	//backDest.h = 480;

	//backSrc.x = 0;
	//backSrc.y = 0;
	//backSrc.w = 1920;
	//backSrc.h = 1080;

	//280
	GameObject Player = GameObject("Player", 3, -3, 0, 0, 253, 150, 150, 0, 0, 288, 288, GameEngine::gameEngine_renderer);

	//PlayerObject Player = PlayerObject("Player", 3, -3, 0, 0, 320, 150, 150, 0, 0, 288, 288);
	

	GameEngine::LoadTextures(allGameObjects[allGameObjects.size() - 1], "C:/Users/manij/Desktop/School/Game Engine Construction/ProjectTest/ProjectTest/Sprites/PlayerChar/", 1, Player.obj_srcRect, Player.obj_rect);
	
	//ParticleManager walkDust2 = ParticleManager("WalkDust");
	/*walkDust->ParticleManager_init("C:/Users/manij/Desktop/School/Game Engine Construction/ProjectTest/ProjectTest/Sprites/Particles/0.png", GameEngine::gameEngine_renderer, 300,
		200, 10, 10, 0, 5000);*/
	/*walkDust->ParticleManager_init("C:/Users/manij/Desktop/School/Game Engine Construction/ProjectTest/ProjectTest/Sprites/Particles/0.png", GameEngine::gameEngine_renderer, allGameObjects[0].obj_rect.x,
		allGameObjects[0].obj_rect.y + allGameObjects[0].obj_rect.h, 50, 50, 0, 5000);*/
	/*walkDust2.ParticleManager_init("C:/Users/manij/Desktop/School/Game Engine Construction/ProjectTest/ProjectTest/Sprites/Particles/0.png", GameEngine::gameEngine_renderer, allGameObjects[0].obj_rect.x,
		allGameObjects[0].obj_rect.y + allGameObjects[0].obj_rect.h, 50, 50, 0, 5000);
	Player.particlesEmitters.push_back(walkDust2);*/
	//GameEngine::allParticleEmitters.push_back(walkDust);
	//GameEngine::addParticleEmmiter(walkDust);

	//GameObject baseFloor = GameObject("BaseFloor", 0, 0, -1, 0, 80, 640, 700, 0, 0, 1920, 1080);
	GameObject baseFloor = GameObject("BaseFloor", 0, 0, -1, 0, 400, 640, 50, 0, 0, 96, 96, GameEngine::gameEngine_renderer);
	//GameObject baseFloor = GameObject("BaseFloor", 0, 0, -1, 0, 0, 640, 50, 0, 0, 96, 96);
	//SDL_FillRect(baseFloor.objInitiateSurface, baseFloor.const_obj_rect, SDL_MapRGB(baseFloor.objInitiateSurface->format, 255, 0, 0));
	GameEngine::LoadTextures(allGameObjects[allGameObjects.size() - 1], "C:/Users/manij/Desktop/School/Game Engine Construction/ProjectTest/ProjectTest/Sprites/Platforms/", 1, baseFloor.obj_srcRect, baseFloor.obj_rect);

	GameObject Background = GameObject("WestBackground", 0, 0, -1, 0, 0, 640, 480, 0, 0, 1920, 1080, GameEngine::gameEngine_renderer);
	GameEngine::LoadTextures(allGameObjects[allGameObjects.size() - 1], "C:/Users/manij/Desktop/School/Game Engine Construction/ProjectTest/ProjectTest/Sprites/Background/", 1, Background.obj_srcRect, Background.obj_rect); ///////Figure out which textures to load



	//allGameObjects.push_back(Background);
	//allGameObjects.push_back(Player);
	//gameObjects.push_back(eveningBackground);*/
}

void MovePlayer(GameObject& myObj);

void GameEngine::gameUpdate()
{
	walkDust->ParticleManager_update();
	//MovePlayer(allGameObjects[0]);
}

void GameEngine::renderParticles() {
	walkDust->ParticleManager_draw(GameEngine::gameEngine_renderer);
}

int main() {

	GameEngine gameEngine = GameEngine();
	int this_start_time, fps_counter = 0, last_count_start_time = 0, current_fps = 0, this_duration = 0;
	gameEngine.init("MYGAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);
	gameEngine.gameStart();
	while (gameEngine.game_is_running == true)
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		gameEngine.deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

		this_start_time = SDL_GetTicks();

		fps_counter++;
		if (this_start_time >= (last_count_start_time + 1000)) {
			last_count_start_time = this_start_time;
			current_fps = fps_counter;
			fps_counter = 0;
		}

		std::cout << current_fps << std::endl;

		///////// PUT MAIN GAME CODE HERE /////////////////
		gameEngine.handleEvents();
		gameEngine.updateMechanics();
		gameEngine.render();

		this_duration = SDL_GetTicks() - this_start_time;

		if (this_duration < frame_duration) {
			SDL_Delay(frame_duration - this_duration);
		}
	}
	gameEngine.quit();

	return 0;
}

//
//int main()
//{
//	my_SDL_init();
//	SDL_Event my_input, ev;
//
//	int this_start_time, fps_counter = 0, last_count_start_time = 0, current_fps = 0, this_duration = 0;
//	SDL_Texture* my_texture = NULL;
//	SDL_Texture* my_instruction_texture = NULL;
//	SDL_Surface* Slinger_holster = IMG_Load("Sprites/GunSlinger-1.png.png");
//	SDL_Surface* slinger_drawn = IMG_Load("Sprites/GunSlinger-4.png.png");
//	SDL_Surface* instructions = IMG_Load("Sprites/Instructions.png");
//	SDL_Surface* currentImage = nullptr;
//
//	currentImage = Slinger_holster;
//
//	my_texture = SDL_CreateTextureFromSurface(my_renderer, currentImage);
//	SDL_SetRenderDrawColor(my_renderer, 255, 223, 0, 255);
//	SDL_RenderClear(my_renderer);
//	
//	SDL_Rect rect;
//	rect.x = 0;
//	rect.y = 320;
//	rect.w = 150;
//	rect.h = 150;
//
//	SDL_Rect land_rect;
//	land_rect.x = 0;
//	land_rect.y = SCREEN_HEIGHT - 40;
//	land_rect.w = SCREEN_WIDTH;
//	land_rect.h = 80;
//
//	SDL_Rect inst_rect;
//	inst_rect.x = 170;
//	inst_rect.y = 140;
//	inst_rect.w = 300;
//	inst_rect.h = 200;
//
//	SDL_SetRenderDrawColor(my_renderer, 255, 223, 0, 255);
//
//
//	//bool game_is_running = true, gun_drawn = false;
//
//	GameEngine gameEngine = GameEngine();
//
//	gameEngine.init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);
//
//	while (gameEngine.game_is_running) {
//		
//		// Copy the info from the texture (where we put the rocket) using the information of the rectangle and hand it over to the renderer
//		/*SDL_RenderCopy(my_renderer, my_texture, NULL, &rect);
//				
//		SDL_RenderPresent(my_renderer);*/
//
//		gameEngine.render();
//		this_start_time = SDL_GetTicks();
//		fps_counter++;
//		if (this_start_time >= (last_count_start_time + 1000)) {
//			last_count_start_time = this_start_time;
//			current_fps = fps_counter;
//			fps_counter = 0;
//		}
//		//std::cout << current_fps << std::endl;
//
//		// counter++;
//		//	if (counter > 10000)
//		//game_is_running = false;
//		gameEngine.HandleEvents();
//		gameEngine->Update();
//		gameEngine->Render();
//		this_duration = SDL_GetTicks() - this_start_time;
//
//		if (this_duration < frame_duration) {
//			SDL_Delay(frame_duration - this_duration);
//		}
//
//	}
//	SDL_FreeSurface(Slinger_holster);
//	SDL_FreeSurface(slinger_drawn);
//	SDL_FreeSurface(instructions);
//	SDL_DestroyRenderer(my_renderer);
//	SDL_DestroyWindow(my_window);
//
//	IMG_Quit();
//	SDL_Quit();
//
//	return 0;
//}
//
//this_start_time = SDL_GetTicks();
//fps_counter++;
//while (SDL_PollEvent(&my_input) > 0) {
//	if (my_input.type == SDL_QUIT) game_is_running = false;
//	else if (my_input.type == SDL_KEYDOWN) {
//		switch (my_input.key.keysym.sym) {
//		case SDLK_1:
//			currentImage = Slinger_holster;
//			my_texture = SDL_CreateTextureFromSurface(my_renderer, currentImage);
//			SDL_SetRenderDrawColor(my_renderer, 255, 223, 0, 255);
//			gun_drawn = false;
//			break;
//		case SDLK_2:
//			currentImage = slinger_drawn;
//			my_texture = SDL_CreateTextureFromSurface(my_renderer, currentImage);
//			SDL_SetRenderDrawColor(my_renderer, 255, 0, 0, 255);
//			gun_drawn = true;
//			//SDL_RenderClear(my_renderer);
//			break;
//		case SDLK_d:
//			rect.x += 10;
//			if (rect.x > SCREEN_WIDTH) rect.x = 0;
//			break;
//		case SDLK_a:
//			rect.x -= 10;
//			if (rect.x < 0) rect.x = SCREEN_WIDTH;
//			break;
//		}
//	}
//}
//
///*rect.x += 5;
//if (rect.x > SCREEN_WIDTH) rect.x = 0;*/
//
//SDL_RenderClear(my_renderer);
//
//if (gun_drawn == false) {
//	SDL_SetRenderDrawColor(my_renderer, 255, 223, 0, 255);
//	SDL_RenderClear(my_renderer);
//
//	my_instruction_texture = SDL_CreateTextureFromSurface(my_renderer, instructions);
//	SDL_RenderFillRect(my_renderer, &inst_rect);
//	SDL_RenderCopy(my_renderer, my_instruction_texture, NULL, &inst_rect);
//
//	SDL_SetRenderDrawColor(my_renderer, 160, 82, 45, 255);
//	SDL_RenderFillRect(my_renderer, &land_rect);
//	SDL_RenderCopy(my_renderer, my_texture, NULL, &rect);
//
//	SDL_RenderPresent(my_renderer);
//}
//else {
//	SDL_SetRenderDrawColor(my_renderer, 255, 0, 0, 255);
//	SDL_RenderClear(my_renderer);
//
//	my_instruction_texture = SDL_CreateTextureFromSurface(my_renderer, instructions);
//	SDL_RenderFillRect(my_renderer, &inst_rect);
//	SDL_RenderCopy(my_renderer, my_instruction_texture, NULL, &inst_rect);
//
//	SDL_SetRenderDrawColor(my_renderer, 160, 82, 45, 255);
//	SDL_RenderFillRect(my_renderer, &land_rect);
//	SDL_RenderCopy(my_renderer, my_texture, NULL, &rect);
//
//	SDL_RenderPresent(my_renderer);
//}