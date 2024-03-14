#include "Game.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"
#include <vector>
#include "Input.h"
#include"GameObjects/GameObjects.h"



//DEBUG
#include"Graphics/Animation.h"
#include"Math/Vector2.h"
#include"GameObjects/PhysicsObject.h"

using namespace std;
Game* Game::GetGame()
{

	//static - only run initilisation once
	// that means this line will only run once
	//this is completely thread safe 
	static Game* Gamesinglton = new Game();
	return Gamesinglton;
}

void Game::DestroyGame()
{
	delete Game::GetGame();
}

Texture* Game::ImportTexture(const char* PathToFile)
{
	Texture* NewTexture = new Texture(m_RendererRef);

	// loop through all of the texture in the game 
	for (Texture* TexRef : m_TextureStack) {
		//check if the texture has already been imported 
		if (strcmp(TexRef->GetPath(), PathToFile) == 0) {
			// if there was a matching path 
			//Copy the successfully mached element 
			NewTexture->CopyTexture(TexRef);
			//add it to the texture stack
			m_TextureStack.push_back(NewTexture);
			//return the new texture here to ignore the rest of the fnction 
			return NewTexture;
		}
	}

	//attempt to import the texture 
	if (!NewTexture->ImportTexture(PathToFile)) {
		//if it failed then delete and update new texture to nullptr 
		delete NewTexture;
		NewTexture = nullptr;
	}
	else {
		m_TextureStack.push_back(NewTexture);
	}
	return NewTexture;
}

void Game::DestroyTexture(Texture* TextureToDestroy)
{
	int TexturesFound = 0;
	//loop through all of the textures 
	for (Texture* TexRef : m_TextureStack) {
		//if the texture has a matching path
		if (strcmp(TextureToDestroy->GetPath(), TexRef->GetPath()) == 0) {
			++TexturesFound;

			if (TexturesFound > 1) {
				break;
			}

		}
	}

	if (TexturesFound <= 1) {
		TextureToDestroy->Cleanup();
	}

	auto it = find(m_TextureStack.begin(), m_TextureStack.end(), TextureToDestroy);

	// if we find the teture 
	if (it != m_TextureStack.end()) {
		m_TextureStack.erase(it);
	}
	

	delete TextureToDestroy;
	TextureToDestroy = nullptr;

	EE_LOG("Game", "Texture has been destroyed.");
}

template<typename T>
 T* Game::AddGameObject()
{
	T* NewObject = new T();

	//add the object to our pending apwan array 
	m_GameObjectPendingSpawn.push_back(NewObject);

	return NewObject;
}

Game::Game()
{
	printf("Game created.\n");
	m_IsGameOpen = true;
	m_WindowRef = nullptr;
	m_RendererRef = nullptr;

	//DEBUG VARS 
	m_TestAniml = nullptr;
	m_TestObject = nullptr;


}

Game::~Game()
{
	printf("Game destroyed.\n");


}

void Game::Initialise()
{

	//Initialise SDL and the game if it fail
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		EE_LOG("Game", "SDL failed to init: " << SDL_GetError());
		return;
	}

	EE_LOG("Game", "Game successfully initialised all libraries");
	Start();
}

void Game::Start()
{
	m_WindowRef = SDL_CreateWindow("Ember Eclipse", // Tittle of window
		SDL_WINDOWPOS_CENTERED_DISPLAY(1), SDL_WINDOWPOS_CENTERED_DISPLAY(1),//start position on the window 
		1280, 720,//resolution of the window
		0); //special flags to change the window settings

	//did the window successfully create 
	if (m_WindowRef == nullptr) {
		EE_LOG("Game", "SDL window failed to create: " << SDL_GetError());

		//deallocate all the stuff that has been allocated prior to this point 
		Cleanup();
		return;
	}

	//create randerer and check if it failed 
	m_RendererRef = SDL_CreateRenderer(m_WindowRef, -1, 0);


	//did the rendere fail
	if (m_RendererRef == nullptr) {
		EE_LOG("Game", "SDL renderer failed to create: " << SDL_GetError());

		Cleanup();
		return;
	}

	//create the game input 

	m_GameInput = new Input();


	//DEBUG


	m_TestObject = AddGameObject<PhysicsObject>();

	GameLoop();
}

void Game::GameLoop()
{
	while (m_IsGameOpen) {
		PreLoop();

		ProcessInput();

		Update();

		Render();

		CollectGarbage();

	}

	Cleanup();
}

void Game::PreLoop()
{
	//add all game object pending spwam to the game object stack 
	for (auto GO : m_GameObjectPendingSpawn) {
		m_GameObjectStack.push_back(GO);
		GO->Start();
		EE_LOG("game", "test");
	}

	m_GameObjectPendingSpawn.clear();
}

void Game::Cleanup()
{
	//desdtrtoy any object pending spwam 
	for (auto GO : m_GameObjectPendingSpawn) {
		GO->Cleanup();
		delete GO;
		GO = nullptr;
	}
	//destroy any remaining  game object
	for (auto GO : m_GameObjectStack) {
		GO->Cleanup();
		delete GO;
		GO = nullptr;
	}
	// cleanup and remove all textures from the texture stack 
	for (int i = m_TextureStack.size() - 1; i > -1;--i) {
		DestroyTexture(m_TextureStack[i]);
	}


	//does the renderer exist
	if (m_RendererRef != nullptr) {
		//deallocate the render from memory
		SDL_DestroyRenderer(m_RendererRef);
	}
	//does the window exist
	if (m_WindowRef != nullptr) {
		//deallocate the window from memory
		SDL_DestroyWindow(m_WindowRef);
	}

	SDL_Quit();

	EE_LOG("Game", "Gamer has dewallocated all memory");
}

void Game::ProcessInput()
{
	//process the input foe the game
	m_GameInput->ProcessInput();

	//run the input listner functiom for all game object 
	for (auto GO : m_GameObjectStack) {
		if (GO != nullptr) {
			GO->ProcessInput(m_GameInput);
		}
	}

	
	
}

void Game::Update()
{
	//recode the previous frame time 
	static double LastTickTime = 0.0;
	//recode the current frame time 
	double CurrentTickTime = (double)SDL_GetTicks64();
	//get the delta time - how much time has passed since the last frame
	double LongDelta = CurrentTickTime - LastTickTime;
	//convert from milliseconds 
	double DeltaTime = LongDelta / 1000.0;
	// set the last tick time 
	LastTickTime = CurrentTickTime;

	/*//DEBUG 
	//Position of the animation on the screen 
	static Vector2 Position(640.0f, 360.0f);
	float Speed(100.0f * (float)DeltaTime); //keep same speed 
	Vector2 MovementDirection(0.0f);

	if (m_GameInput->IsKeyDown(EE_KEY_W)) {
		MovementDirection.y += -1.0f;
	}
	if (m_GameInput->IsKeyDown(EE_KEY_S)) {
		MovementDirection.y += 1.0f;
	}
	if (m_GameInput->IsKeyDown(EE_KEY_A)) {
		MovementDirection.x += -1.0f;
	}
	if (m_GameInput->IsKeyDown(EE_KEY_D)) {
		MovementDirection.x += 1.0f;
	}
	if (m_GameInput->IsKeyDown(EE_KEY_Q)) {
		if (m_TestObject != nullptr) {
			m_TestObject->DestreyObject();
			m_TestObject = nullptr;
		}
	}

	// move the animation to the rigth 
	Position += MovementDirection*Speed;



	//TODO: Update game logic

	if (m_TestAniml != nullptr) {
		m_TestAniml->SetPosition(Position.x, Position.y);
		m_TestAniml->Update((float)DeltaTime);
	}
	*/

	//run the update logic for all game object 
	for (auto GO : m_GameObjectStack) {
		if (GO != nullptr) {
			GO->Update((float)DeltaTime);
			GO->PostUpdate((float)DeltaTime);
		}
	}
}

void Game::Render()
{
	
	SDL_SetRenderDrawColor(m_RendererRef, 25, 25, 25, 255);
	//User the color just started to clear the previous frame and fill in with that colour 
	SDL_RenderClear(m_RendererRef);

	//TODO: Render custom graphics
	for (Texture* TexRef : m_TextureStack) {
		if (TexRef != nullptr) {

			TexRef->Draw();
		}
	}
	
    
	//Present the graphics to the renderer 
	SDL_RenderPresent(m_RendererRef);
}

void Game::CollectGarbage()
{
	//TODO: Delete object at the end of each frame
	for (int i = m_GameObjectStack.size() - 1; i >= 0; --i) {
		if (!m_GameObjectStack[i]->IsPendingDestroy()) {
			continue;
		 }

		//make sure the game object is not nullptr 
		if (m_GameObjectStack[i] != nullptr) {
			m_GameObjectStack[i]->Cleanup();
			delete m_GameObjectStack[i];
		}

		//remove from and resize the array 
		m_GameObjectStack.erase(m_GameObjectStack.begin() + i);
	}
}
