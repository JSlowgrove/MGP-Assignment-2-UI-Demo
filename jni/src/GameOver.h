#pragma once

#include <SDL.h>
#include <vector>
#include "JAM/State.h"
#include "JAM/StateManager.h"
#include "JAM/Texture.h"
#include "JAM/Audio.h"
#include "JAM/Text.h"

/**
@brief Creates a GameOver object that inherits State and runs the GameOver state.
*/
class GameOver : public JAM_State
{
private:
	/**The background Texture*/
	JAM_Texture* background;
	/**The info Text*/
	JAM_Text* info;
	/**A pointer to the background music*/
	JAM_Audio* music;

public:
	/**
	Constructs a GameOver object.
	@param stateManager A pointer to the StateManager.
	@param renderer A pointer to the renderer.
	@param screenWidth The screen width.
	@param screenHeight The screen height.
	*/
	GameOver(JAM_StateManager* stateManager, SDL_Renderer* renderer, int screenWidth, int screenHeight, JAM_Audio* music);

	/**
	Destructs an GameOver object.
	*/
	~GameOver();

	/**
	Handles the GameOver input.
	@returns If false then quit the GameOver State.
	*/
	bool input();

	/**
	A function to update the GameOver to allow the GameOver to run.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	A function to draw to the screen.
	*/
	void draw();
};