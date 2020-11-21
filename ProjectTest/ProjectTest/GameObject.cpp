#include "gameObject.h"
#include "gameEngine.h"


GameObject::GameObject()
{
}

GameObject::GameObject(SDL_Renderer* ren) {
	texCount = 0;
}


GameObject::GameObject(const char *name, int maxVel, int minVel, int beginStateID) {
	texCount = 0;
	this->name = name;
	this->maxVel = maxVel;
	this->minVel = minVel;
	this->objState.setStateID(beginStateID);
	GameEngine::allGameObjects.push_back(*this);
}

GameObject::GameObject(const char* name, int maxVel, int minVel, int beginStateID, int initPosX, int initPosY, int initPosW, int initPosH, int initSrcX, int initSrcY, int initSrcW, int initSrcH, SDL_Renderer* gameRenderer)
{
	texCount = 0;
	this->name = name;
	this->maxVel = maxVel;
	this->minVel = minVel;
	this->objState.setStateID(beginStateID);
	this->obj_rect.x =  initPosX;
	this->obj_rect.y = initPosY;
	this->obj_rect.w = initPosW;
	this->obj_rect.h = initPosH;
	this->obj_srcRect.x = initSrcX;
	this->obj_srcRect.y = initSrcY;
	this->obj_srcRect.w = initSrcW;
	this->obj_srcRect.h = initSrcH;
	this->obj_renderer = gameRenderer;
	GameEngine::allGameObjects.push_back(*this);
}


GameObject::~GameObject()
{}

void GameObject::obj_init()
{

}

void GameObject::obj_update()
{
	// Done for the player object
	if(this->name == "Player"){
		std::cout << "Player" << std::endl;
		// create a temp game object to find and hold the properties of the gameobject named basefloor, which is instantiated in the main class
		GameObject tempObj = GameObject();
		findGameObjectByName("BaseFloor", tempObj);

		// if there is a collision with baseflooor then set the player object to original color (COLLSION RESPONSE)
		if (IntersectsWith(tempObj) == true) {
			
			SDL_SetTextureColorMod(this->textures[0].SDLTexture, 255, 255, 255);
			//std::cout << "Collision" << std::endl;
		}
		// if there is no collision (player is jumping), then set the player object to red
		else if (IntersectsWith(tempObj) == false){
			//std::cout << "No Collision" << std::endl;
			SDL_SetTextureColorMod(this->textures[0].SDLTexture, 255, 0, 0);
		}

		// Idle
		if (this->objState.getStateID() == 0) {
			for (int i = 0; i < textures.size(); i++) {
				// 2 = frame_duration; 5 = frameCount
				objSprite.spriteUpdate(300, 3, this->textures[i].srcTextureRect, 0);
			}
		}
		// Run right
		if (this->objState.getStateID() == 1) {
			/*ParticleManager tempPartEmm = ParticleManager();
			findParticleEmitterByName("WalkDust", tempPartEmm);*/
			for (int i = 0; i < textures.size(); i++) {
				objSprite.spriteUpdate(300, 3, this->textures[i].srcTextureRect, 1);
				this->textures[i].destTextureRect.x += x_pos + x_vel; // for vel add the +, else for delta pos use just equal to
				std::cout << "X: " << this->textures[i].destTextureRect.x << ", x_vel: " << x_vel << std::endl;
				this->obj_rect = this->textures[i].destTextureRect;

				// Keep a timer to make sure particle doesn't spawn too much
				if (SDL_GetTicks() - particleTimerCount > maxParticleTimer) {
					particleTimerCount = SDL_GetTicks();
					// Spawn the particle emmiter for running right (COLLSION EFFECT)
					ParticleManager walkDust = ParticleManager("WalkDust2");
					walkDust.ParticleManager_init("C:/Users/manij/Desktop/School/Game Engine Construction/ProjectTest/ProjectTest/Sprites/Particles/1.png", obj_renderer, obj_rect.x + 35,
						obj_rect.y + 130, 30, 30, 1, 25);
					// Add it to the list of particle emmiter this gameobject will render
					this->particlesEmitters.push_back(walkDust);
				}
				particleTimerCount++;
				/*tempPartEmm.setXPos(this->obj_rect.x);
				tempPartEmm.setYPos(this->obj_rect.y + this->obj_rect.h);*/

				if (textures[i].destTextureRect.x < 0) {
					this->textures[i].destTextureRect.x = 0;
					x_vel = 0;
					this->obj_rect = this->textures[i].destTextureRect;
					/*tempPartEmm.setXPos(this->obj_rect.x);
					tempPartEmm.setYPos(this->obj_rect.y + this->obj_rect.h);*/
				}
				else if (textures[i].destTextureRect.x > screen_width) {
					this->textures[i].destTextureRect.x = 0;
					this->obj_rect = this->textures[i].destTextureRect;
					/*tempPartEmm.setXPos(this->obj_rect.x);
					tempPartEmm.setYPos(this->obj_rect.y + this->obj_rect.h);*/
				}
				if (x_vel >= maxVel)
					x_vel = maxVel;
				if (x_vel < minVel)
					x_vel = minVel;
			}
		}
		// Run Left
		if (this->objState.getStateID() == 2) {
			for (int i = 0; i < textures.size(); i++) {
				objSprite.spriteUpdate(300, 3, this->textures[i].srcTextureRect, 2);
				this->textures[i].destTextureRect.x -= x_pos - x_vel; // for vel add the +, else for delta pos use just equal to
				//std::cout << "X: " << this->textures[i].destTextureRect.x << ", x_vel: " << x_vel << std::endl;
				this->obj_rect = this->textures[i].destTextureRect;
				if (SDL_GetTicks() - particleTimerCount > maxParticleTimer) {
					particleTimerCount = SDL_GetTicks();

					// Spawn the particle emmiter for running right
					ParticleManager walkDust = ParticleManager("WalkDust2");
					walkDust.ParticleManager_init("C:/Users/manij/Desktop/School/Game Engine Construction/ProjectTest/ProjectTest/Sprites/Particles/1.png", obj_renderer, obj_rect.x + obj_rect.w - 35,
						obj_rect.y + 130, 30, 30, 2, 25);
					this->particlesEmitters.push_back(walkDust);
				}
				particleTimerCount++;
				if (textures[i].destTextureRect.x < 0) {
					this->textures[i].destTextureRect.x = 0;
					x_vel = 0;
					this->obj_rect = this->textures[i].destTextureRect;
				}
				else if (textures[i].destTextureRect.x > screen_width) {
					this->textures[i].destTextureRect.x = 0;
					this->obj_rect = this->textures[i].destTextureRect;
				}
				if (x_vel <= maxVel)
					x_vel = maxVel;
				if (x_vel > minVel)
					x_vel = minVel;
			}
		}
		// Jump
		if (this->objState.getStateID() == 3) {
			this->objState.setNumFrames(this->objState.getNumFrames() - 1);
			//std::cout << "TempFrameCount: " << this->objState.getNumFrames() << std::endl;
			//while (tempFrameCount > 0) {
			if (this->objState.getNumFrames() > 0) {
				for (int i = 0; i < textures.size(); i++) {

					this->textures[i].destTextureRect.y -= y_pos + y_vel;
					//std::cout << "Y: " << this->textures[i].destTextureRect.y << ", y_vel: " << y_vel << std::endl;
					this->obj_rect = this->textures[i].destTextureRect;
				}
			}

			// when the number of frames is decreasing for the jump animation then do the following
			if (this->objState.getNumFrames() <= 0) {
				for (int i = 0; i < textures.size(); i++) {

					// Chack if there is a collision with the ground, if there is no collision then start decreasing the velocity and position of the player object
					if (IntersectsWith(tempObj) == false) {
						this->textures[i].destTextureRect.y -= y_pos - y_vel;
						//std::cout << "Y: " << this->textures[i].destTextureRect.y << ", y_vel: " << y_vel << std::endl;
						this->obj_rect = this->textures[i].destTextureRect;
					}
					
					// Chack if there is a collision with the ground, if there is a collision then stop the velocity and position of the player object and set state to idle of the player
					if (IntersectsWith(tempObj) == true) {
						std::cout << tempObj.name << std::endl;
						std::cout << this->textures[i].destTextureRect.y << std::endl;

						//SDL_SetTextureColorMod(this->textures[0].SDLTexture, 0, 255, 0);
						y_vel = 0;
						this->textures[i].destTextureRect.y = tempObj.obj_rect.y - this->textures[i].destTextureRect.h + 6;
						std::cout << this->textures[i].destTextureRect.y << std::endl;
						//y_vel = 0;
						this->obj_rect = this->textures[i].destTextureRect;
						std::cout << this->obj_rect.y << std::endl;

						this->objState.setStateID(0);

						// Spawn the particle emmiter for Jjumping and landing on the ground
						ParticleManager jumpDust = ParticleManager("WalkDust2");
						jumpDust.ParticleManager_init("C:/Users/manij/Desktop/School/Game Engine Construction/ProjectTest/ProjectTest/Sprites/Particles/0.png", obj_renderer, obj_rect.x + 35,
							obj_rect.y + 110, 100, 100, 3, 50);
						this->particlesEmitters.push_back(jumpDust);
					}
				}
			}
		}
		// Shoot state for the player
		if (this->objState.getStateID() == 4) {
			this->objState.setNumFrames(this->objState.getNumFrames() - 1);
			if (this->objState.getNumFrames() > 0) {
				for (int i = 0; i < textures.size(); i++) {
					objSprite.spriteUpdate(5, 3, this->textures[i].srcTextureRect, 3);
				}
			}
			else
				this->objState.setStateID(0);
		}
	}
		//std::cout << "X: " <<this->textures[i].destTextureRect.x << ", x_vel: " << x_vel << std::endl;
}

void GameObject::obj_render()
{
	//SDL_RenderCopy(obj_renderer, (*gunSlingerHolstered.textures)[0], NULL, NULL);

}

void GameObject::obj_quit()
{
}

int GameObject::getXPos()
{
	return this->x_pos;
}

void GameObject::setXPos(int newXpos)
{
	this->x_pos = newXpos;
}

int GameObject::getXVel()
{
	return this->x_vel;
}

int GameObject::getYPos()
{
	return this->y_pos;
}

int GameObject::getYVel()
{
	return this->y_vel;
}

void GameObject::setXVel(int newXVel)
{
	this->x_vel = newXVel;
}

void GameObject::setYPos(int newYpos)
{
	this->y_pos = newYpos;
}

void GameObject::setYVel(int newYVel)
{
	this->y_vel = newYVel;
}

void GameObject::findGameObjectByName(const char* name, GameObject &tempObj)
{
	GameObject tempGameObj;
	for (int i = 0; i < GameEngine::allGameObjects.size(); i++) {
		if (GameEngine::allGameObjects[i].name == name)
			tempObj = GameEngine::allGameObjects[i];
			//tempGameObj = GameEngine::allGameObjects[i];
	}
	//return tempGameObj;
}

//void GameObject::findParticleEmitterByName(const char* name, ParticleManager& tempPartEmm)
//{
//
//	for (int i = 0; i < GameEngine::allParticleEmitters.size(); i++) {
//		if (GameEngine::allParticleEmitters[i].name == name)
//			tempPartEmm = GameEngine::allParticleEmitters[i];
//		//tempGameObj = GameEngine::allGameObjects[i];
//	}
//}

// Returns a boolean to check if the gameobjects are colliding with one another, collsion detection
bool GameObject::IntersectsWith(GameObject &otherObj)
{
	//std::cout << "This Obj_Rect X_L: " << this->obj_rect.x << ", This Obj_Rect Y_T: " << this->obj_rect.y << 
	//	", This Obj_Rect w: " << this->obj_rect.w << ", This Obj_Rect h: " << this->obj_rect.h <<
	//	", (Xr) This Obj_Rect x + w: " << this->obj_rect.x + this->obj_rect.w << 
	//	", (Yb) This Obj_Rect y + h: " << this->obj_rect.y + this->obj_rect.h << std::endl;
	////////std::cout << "This Obj_Rect x + w: " << this->obj_rect.x + this->obj_rect.w << std::endl;
	////////std::cout << "This Obj_Rect y + h: " << this->obj_rect.y + this->obj_rect.h << std::endl;

	//std::cout << "OtherObj_Rect x_L: " << otherObj.obj_rect.x << ", OtherObj_Rect Y_T: " << otherObj.obj_rect.y <<
	//	" OtherObj_Rect w: " << otherObj.obj_rect.w << ", OtherObj_Rect h: " << otherObj.obj_rect.h <<
	//	", (Xr) OtherObj_Rect x + w: " << otherObj.obj_rect.x + otherObj.obj_rect.w << 
	//	", (Yb) OtherObj_Rect y + h: " << otherObj.obj_rect.y + otherObj.obj_rect.h << std::endl;
	/*std::cout << "OtherObj_Rect x + w: " << otherObj.obj_rect.x + otherObj.obj_rect.w << std::endl;
	std::cout << "OtherObj_Rect y + h: " << otherObj.obj_rect.y + otherObj.obj_rect.h << std::endl;*/

	// If casses to check if there is a collsion with another object
	if (this->obj_rect.x + this->obj_rect.w < otherObj.obj_rect.x) {
		//std::cout << "No Collision" << std::endl;
		std::cout << "(X_AR < X_BL)" << std::endl;
		return false;
	}
	if (this->obj_rect.x > otherObj.obj_rect.x + otherObj.obj_rect.w) {
		std::cout << "(X_AL > X_BR)" << std::endl;
		//std::cout << "No Collision" << std::endl;
		return false;
	}
	if (this->obj_rect.y + this->obj_rect.h < otherObj.obj_rect.y) {
		std::cout << "(Y_AB < Y_BT)" << std::endl;
		//std::cout << "No Collision" << std::endl;
		return false;
	}
	if (this->obj_rect.y > otherObj.obj_rect.y + otherObj.obj_rect.h) {
		std::cout << "(Y_AT > Y_BB)" << std::endl;
		//std::cout << "No Collision" << std::endl;
		return false;
	}
	//std::cout << "Collision" << std::endl;
	// else return true
	return true;

	/*if (this->obj_rect.x + this->obj_rect.w < otherObj.obj_rect.x ||
		this->obj_rect.x > otherObj.obj_rect.x + otherObj.obj_rect.w ||
		this->obj_rect.y + this->obj_rect.h < otherObj.obj_rect.y ||
		this->obj_rect.y > otherObj.obj_rect.y + otherObj.obj_rect.h) {

		return false;
	}*/
	/*else {

		return true;
	}*/
}

void MoveMainCharacter(GameObject& myObj, int direction)
{
}

void transformObject(int x, int y, float vel) {

}

