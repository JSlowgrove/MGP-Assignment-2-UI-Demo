#pragma once

#include <iostream>
#include "JAM/Entity.h"

/**
@brief Creates a Background object that inherits Entity.
*/
class ForceField : public JAM_Entity
{
private:
	/**The velocity of the ForceField*/
	float velocity;
	/**The width of the screen*/
	float screenWidth;
	/**The height of the screen*/
	float screenHeight;

public:
	/**
	Constructs a ForceField object.
	@param sprite A pointer to the objects Texture.
	@param x The x position of the ForceField.
	@param y The y position of the ForceField.
	@param width The width of the ForceField.
	@param height The height of the ForceField.
	@param velocity The velocity of the ForceField.
	@param screenWidth The width of the screen.
	@param screenHeight The height of the screen.
	*/
	ForceField(JAM_Texture* sprite, float x, float y, float width, float height, float velocity, float screenWidth, float screenHeight);

	/**
	Destructs a ForceField object.
	*/
	~ForceField();

	/**
	A function that updates the ForceField.
	@param dt The delta time.
	*/
	void update(float dt);
};