#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h> 
#include <SDL_timer.h>
#include "gameEngine.h"
#include "gameObject.h"

using namespace std;
#undef main

//ParticleManager walkDust = ParticleManager("WalkDust");
vector<GameObject> GameEngine::allGameObjects;
// handle game events, update mechanics, render, adding a function for inti and quit

GameEngine::GameEngine()
{}
GameEngine::~GameEngine()
{}

void GameEngine::init(const char* title, int xpos, int ypos, int screen_width, int screen_height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}
	else {
		std::cout << "Finished SDL_init" << std::endl;
	}

	screenHeight = screen_height;
	screenWidth = screen_width;

	//Enable gpu_enhanced textures
	IMG_Init(IMG_INIT_PNG);

	gameEngine_window = SDL_CreateWindow("my_game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screen_width,
		screen_height, 0);
	gameEngine_renderer = SDL_CreateRenderer(gameEngine_window, -1, 0);

	game_is_running = true;
	
	Texture texture;
	for (int i = GameEngine::allGameObjects.size() - 1; i >= 0; i--)
	{
		GameObject go = allGameObjects[i];

		if (go.name == "Player")
			Player = go;
	}


}

void GameEngine::handleEvents()
{
	SDL_Event game_event;
	SDL_PollEvent(&game_event);
	if (game_event.type == SDL_QUIT) game_is_running = false;
	else if (game_event.type == SDL_KEYDOWN) {
		switch (game_event.key.keysym.sym) {
			Texture texture;
			case SDLK_d:
				//cout << "D is pressed" << endl;
				//allGameObjects[0].setXPos(allGameObjects[0].getXPos() + playerVel); // new delta pos
				//allGameObjects[0].setXVel(playerVel); // new vel
				//allGameObjects[0].setXVel(allGameObjects[0].getXVel() + 3); // delta vel
				//allGameObjects[0].objState.setStateID(1);
				if (this->allGameObjects[0].objState.getStateID() == 0 || this->allGameObjects[0].objState.getStateID() == 1) {
					allGameObjects[0].setXVel(allGameObjects[0].getXVel() + 3); // delta vel
					allGameObjects[0].objState.setStateID(1);
					//walkDust.ParticleManager_draw(gameEngine_renderer);
					//allParticleEmitters[0].ParticleManager_draw(gameEngine_renderer);
				}
				//for (int i = 0; i < allGameObjects[0].texCount; i++)
				//{ 
				//	(allGameObjects[0].textures)[i].destTextureRect.x += playerVel; //delta pos
				//	(allGameObjects[0].textures)[i].destTextureRect.x += (playerVel * deltaTime); // vel
				//}

				if (allGameObjects[0].getXPos() > screenWidth) allGameObjects[0].setXPos(0);
				break;
			case SDLK_a:
				//cout << "A is pressed" << endl;
				//allGameObjects[0].setXPos(allGameObjects[0].getXPos() - playerVel); // new delta pos
				//allGameObjects[0].setXVel(-1*playerVel); // new vel
				if (this->allGameObjects[0].objState.getStateID() == 0 || this->allGameObjects[0].objState.getStateID() == 1) {
					allGameObjects[0].setXVel(allGameObjects[0].getXVel() - 3); // delta vel
					allGameObjects[0].objState.setStateID(2);
				}
				//allGameObjects[0].setXVel(allGameObjects[0].getXVel() - 3); // delta vel
				//allGameObjects[0].objState.setStateID(1);
				//for (int i = 0; i < allGameObjects[0].texCount; i++)
				//{
				//	(allGameObjects[0].textures)[i].destTextureRect.x -= playerVel; //delta pos
				//	(allGameObjects[0].textures)[i].destTextureRect.x += (-1*playerVel*deltaTime); // vel
				//}
				if (allGameObjects[0].getXPos() < 0) {
					allGameObjects[0].setXPos(0);
					allGameObjects[0].setXVel(0);
				}
				break;
			case SDLK_SPACE:
				//cout << "Space is pressed" << endl;
				//if (allGameObjects[0].getXVel() < 0) {
				//	allGameObjects[0].setXVel(allGameObjects[0].getXVel() - 10); // delta vel
				//}
				//if (allGameObjects[0].getXVel() > 0) {
				//	allGameObjects[0].setXVel(allGameObjects[0].getXVel() + 10);
				//}
				
				if (allGameObjects[0].getXVel() == 0 && allGameObjects[0].getYVel() == 0) {
					allGameObjects[0].setYVel(5); // delta vel
					allGameObjects[0].objState.setStateID(3);
					allGameObjects[0].objState.setNumFrames(30);
				}
				break;
			case SDLK_RCTRL:
				//cout << "Right Control is pressed" << endl;
				allGameObjects[0].objState.setStateID(4);
				allGameObjects[0].objState.setNumFrames(10);
				break;
			default: // for delta vel
				int tempXVel = allGameObjects[0].getXVel();
				// inset tempYVel?
				if (tempXVel < 0)
					allGameObjects[0].setXVel(tempXVel + 1);
				if (tempXVel > 0)
					allGameObjects[0].setXVel(tempXVel - 1);
		}
	}
	else if (game_event.type == SDL_KEYUP) {
		switch (game_event.key.keysym.sym) {
		case SDLK_d:
			//cout << "D is released" << endl;
			allGameObjects[0].setXVel(0);
			allGameObjects[0].objState.setStateID(0);
			break;
		case SDLK_a:
			//cout << "A is released" << endl;
			allGameObjects[0].setXVel(0);
			allGameObjects[0].objState.setStateID(0);
			break;
		}
	}
}

// Do all of the updates to all of the different objects
void GameEngine::updateMechanics()
{
	gameUpdate();
	for (int i = 0; i < GameEngine::allGameObjects.size(); i++)
	{
		allGameObjects[i].obj_update();
		// Update all the particles associated with each game object
		for (int j = 0; j < GameEngine::allGameObjects[i].particlesEmitters.size(); j++) {
			allGameObjects[i].particlesEmitters[j].ParticleManager_update();
		}
	}
}

void GameEngine::render()
{
	
	SDL_RenderClear(gameEngine_renderer);

	SDL_Texture* tempTex;
	SDL_Rect rect;
	SDL_Rect tileSrcRect;
	SDL_Rect destRect;

	Texture texture;

	//SDL_SetRenderDrawColor(gameEngine_renderer, 160, 82, 45, 255);
	//SDL_RenderFillRect(gameEngine_renderer, &land_rect);
	//SDL_RenderCopy(gameEngine_renderer, my_texture, NULL, &rect);
	//SDL_SetRenderDrawColor(gameEngine_renderer, 0, 0, 255, 0);
	//SDL_RenderDrawRect(gameEngine_renderer, &allGameObjects[1].textures[0].destTextureRect);
	//std::cout << allGameObjects[1].textures[0].destTextureRect.x << ", " << allGameObjects[1].textures[0].destTextureRect.y << ", " << allGameObjects[1].textures[0].destTextureRect.w << ", " << allGameObjects[1].textures[0].destTextureRect.h << std::endl;
	for (int i = GameEngine::allGameObjects.size() - 1; i >= 0; i--)
	{
		GameObject go = allGameObjects[i];

		// render all the particles associated with every game object
		for (int k = 0; k < GameEngine::allGameObjects[i].particlesEmitters.size(); k++) {
			allGameObjects[i].particlesEmitters[k].ParticleManager_draw(gameEngine_renderer);
		}
		//cout << go.name << endl;

		for (int j = go.texCount - 1; j >= 0; j--)
		{
			//cout << i << " " << j << endl;
			//cout << go.name << " " << go.textures[j].destTextureRect->x << ", " << go.textures[j].destTextureRect->y << endl;
			texture = go.textures[j];
			SDL_SetRenderDrawColor(gameEngine_renderer, 0, 255, 0, 0);
			SDL_RenderDrawRect(gameEngine_renderer, &texture.destTextureRect);

			//cout << texture.destTextureRect->x << ", " << texture.destTextureRect->y << endl;
			SDL_RenderCopy(gameEngine_renderer, texture.SDLTexture, &texture.srcTextureRect, &texture.destTextureRect);
		}
	}
	renderParticles();
	//cout << "ending loop" << endl;
	SDL_RenderPresent(gameEngine_renderer);
}

void GameEngine::quit()
{
	SDL_DestroyWindow(gameEngine_window);
	SDL_DestroyRenderer(gameEngine_renderer);
	SDL_Quit();
	std::cout << " GAME CLOSED" << std::endl;
}

void GameEngine::LoadTextures(GameObject& go, const char* folderName, int textureCount, SDL_Rect src, SDL_Rect dest)
{
	for (int i = 0; i < textureCount; i++)
	{
		loadTexture(go, folderName, i, src, dest);
	}
}


// Read Multiple Textures
void GameEngine::loadTexture(GameObject& myObj, const char* folderName, int numOfTextures, SDL_Rect src, SDL_Rect dest)
{
	myObj.texCount++;
	SDL_Surface* tempSurface;
	SDL_Texture* tempTex;

	string s = folderName + std::to_string(numOfTextures) + ".png";
	Texture tempTexture;

	int frameWidth, frameHeight, textureWidth, textureHeight;

	char tempChar[5000];
	strcpy_s(tempChar, s.c_str());

	tempSurface = IMG_Load(tempChar);
	tempTex = SDL_CreateTextureFromSurface(gameEngine_renderer, tempSurface);
	SDL_QueryTexture(tempTex, NULL, NULL, &textureWidth, &textureHeight);
	frameWidth = textureWidth / 3;
	frameHeight = textureHeight / 4;


	tempTexture.srcTextureRect.x = 0;
	tempTexture.srcTextureRect.y = 0;
	tempTexture.srcTextureRect.w = frameWidth;
	tempTexture.srcTextureRect.h = frameHeight;

	tempTexture.SDLTexture = tempTex;
	tempTexture.destTextureRect = dest;
	tempTexture.srcTextureRect = src;

	//myObj.textures.push_back(tempTexture);
	
	cout << "Initialize Textures" << endl;
	cout << "Object name: " << myObj.name << endl;

	cout << "frame width: " << frameWidth << ", frame height: " << frameHeight << endl;

	myObj.textures.push_back(tempTexture);
	SDL_FreeSurface(tempSurface);
}

// Read Single Texture
void GameEngine::loadTexture(GameObject& myObj, const char* folderName, SDL_Rect src, SDL_Rect dest)
{
	myObj.texCount = 1;
	SDL_Surface* tempSurface;
	SDL_Texture* tempTex;

	string s = folderName;

	Texture tempTexture;
	Texture texture;

	s = folderName + std::to_string(0) + ".png";

	char tempChar[5000];
	strcpy_s(tempChar, s.c_str());


	int frameWidth, frameHeight, textureWidth, textureHeight;

	tempSurface = IMG_Load(tempChar);

	cout << tempChar << endl;
	if (tempSurface != NULL)
		cout << "TEXTURE LOADED" << endl;
	else
		cout << "TEXTURE NOT LOADED" << endl;


	tempTex = SDL_CreateTextureFromSurface(gameEngine_renderer, tempSurface);

	SDL_QueryTexture(tempTex, NULL, NULL, &textureWidth, &textureHeight);
	frameWidth = textureWidth / 3;
	frameHeight = textureHeight / 4;


	tempTexture.srcTextureRect.x = 0;
	tempTexture.srcTextureRect.y = 0;
	tempTexture.srcTextureRect.w = frameWidth;
	tempTexture.srcTextureRect.h = frameHeight;

	tempTexture.SDLTexture = tempTex;
	tempTexture.destTextureRect = dest;
	tempTexture.srcTextureRect = src;

	myObj.textures.push_back(tempTexture);
	cout << "Initialize Textures" << endl;
	cout << "frame width: " << frameWidth << ", frame height: " << frameHeight << endl;
	//cout << tempTexture.destTextureRect.x << endl;
	//cout << myObj.textures[0].destTextureRect.x << ", " << myObj.textures[0].destTextureRect.y << endl;
	
	SDL_FreeSurface(tempSurface);
}
