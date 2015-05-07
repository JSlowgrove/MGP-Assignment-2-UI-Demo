#pragma once

#include <SDL.h>
#include <vector>
#include "JAM/State.h"
#include "JAM/StateManager.h"
#include "JAM/Texture.h"
#include "JAM/Audio.h"
#include "JAM/Utilities.h"
#include "JAM/Text.h"
#include "JAM/ParticleEffect.h"
#include "JAM/CollisionDetection.h"
#include "JAM/Button.h"
#include "Background.h"
#include "Player.h"
#include "ForceField.h"

/**
@brief Creates an Game object that inherits State and runs the Game.
*/
class Game : public JAM_State
{
private:
	/**The alien Texture*/
	JAM_Texture* alienDude;
	/**The background stars Texture*/
	JAM_Texture* backgroundStars;
	/**The force field Texture*/
	JAM_Texture* forceField;
	/**The first stars background*/
	Background* starsA;
	/**The second stars background*/
	Background* starsB;
	/**The Player Entity*/
	Player* player;
	/**A Vector for the ParticleEffect*/
	std::vector<JAM_ParticleEffect*> particleEffects;
	/**A Vector for the ForceFields*/
	std::vector<ForceField*> forceFields;
	/**A pointer to the background music*/
	JAM_Audio* music;
	/**A bool for the initial loop*/
	bool initalLoop;
	/**The info Text*/
	JAM_Text* info;
	/**The info Button*/
	JAM_Button* button;

	/**
	Handles the Windows Game input.
	@param incomingEvent A reference to the incoming SDL event.
	@returns If false then quit the Game State.
	*/
	bool windowsInput(SDL_Event& incomingEvent);

	/**
	Handles the Android Game input.
	@param incomingEvent A reference to the incoming SDL event.
	@returns If false then quit the Game State.
	*/
	bool androidInput(SDL_Event& incomingEvent);

public:
	/**
	Constructs a Game object.
	@param stateManager A pointer to the StateManager.
	@param renderer A pointer to the renderer.
	@param screenWidth The screen width.
	@param screenHeight The screen height.
	*/
	Game(JAM_StateManager* stateManager, SDL_Renderer* renderer, int screenWidth, int screenHeight);

	/**
	Destructs an Game object.
	*/
	~Game();

	/**
	Handles the Game input.
	@returns If false then quit the Game State.
	*/
	bool input();

	/**
	A function to update the Game to allow the Game to run.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};