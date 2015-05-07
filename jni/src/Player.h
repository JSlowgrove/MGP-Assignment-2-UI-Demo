#pragma once

#include <iostream>
#include "JAM/Entity.h"
#include "ArrowPad.h"

/**
@brief Creates a Player object that inherits Entity.
*/
class Player : public JAM_Entity
{
private:
	/**The velocity of the Player*/
	JAM_Vec2 velocity;
	/**The up user command for the Player*/
	bool up;
	/**The down user command for the Player*/
	bool down;
	/**The left user command for the Player*/
	bool left;
	/**The right user command for the Player*/
	bool right;
	/**The width of the screen*/
	float screenWidth;
	/**The height of the screen*/
	float screenHeight;
	/**A pointer to the arrowPad*/
	JAM_ArrowPad* arrowPad;

	/**
	Handles the Windows Game input.
	@param incomingEvent A reference to the incoming SDL event.
	*/
	void windowsInput(SDL_Event& incomingEvent);

	/**
	Handles the Android Game input.
	@param incomingEvent A reference to the incoming SDL event.
	*/
	void androidInput(SDL_Event& incomingEvent);

public:
	/**
	Constructs an Player object.
	@param sprite A pointer to the objects Texture.
	@param x The x position of the Player.
	@param y The y position of the Player.
	@param width The width of the Player.
	@param height The height of the Player.
	@param velocity The velocity of the Player.
	@param screenWidth The width of the screen.
	@param screenHeight The height of the screen.
	@param arrowPad A pointer to the arrow pad.
	*/
	Player(JAM_Texture* sprite, float x, float y, float width, float height, JAM_Vec2 velocity, 
		float screenWidth, float screenHeight, JAM_ArrowPad* arrowPad);

	/**
	Destructs an Player object.
	*/
	~Player();

	/**
	A function that handles the input for the Player.
	@param incomingEvent The incoming SDL event.
	*/
	void input(SDL_Event incomingEvent);

	/**
	A function that updates the Background.
	@param dt The delta time.
	*/
	void update(float dt);
};