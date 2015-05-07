#pragma once

#include <SDL.h>
#include <vector>
#include "JAM/State.h"
#include "JAM/StateManager.h"
#include "JAM/Texture.h"
#include "JAM/Audio.h"
#include "JAM/Text.h"
#include "JAM/Utilities.h"

/**
@brief Creates an pause object that inherits State and runs the pause state.
*/
class PauseState : public JAM_State
{
private:
	/**The background Texture*/
	JAM_Texture* background;
	/**The info Text*/
	JAM_Text* info;
	/**A pointer to the background music*/
	JAM_Audio* music;

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
	Constructs a PauseState object.
	@param stateManager A pointer to the StateManager.
	@param renderer A pointer to the renderer.
	@param screenWidth The screen width.
	@param screenHeight The screen height.
	*/
	PauseState(JAM_StateManager* stateManager, SDL_Renderer* renderer, int screenWidth, int screenHeight, JAM_Audio* music);

	/**
	Destructs an PauseState object.
	*/
	~PauseState();

	/**
	Handles the Game input.
	@returns If false then quit the pause State.
	*/
	bool input();

	/**
	A function to update the pause state to allow the Game to run.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};