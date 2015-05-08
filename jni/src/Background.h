#pragma once

#include <iostream>
#include "JAM/Entity.h"

/**
@brief Creates a Background object that inherits Entity.
@author Jamie Slowgrove
*/
class Background : public JAM_Entity
{
private:
	/**The velocity of the Background.*/
	float velocity;

public:
	/**
	Constructs the Background object.
	@param sprite A pointer to the objects Texture.
	@param x The x position of the Background.
	@param y The y position of the Background.
	@param width The width of the Background.
	@param height The height of the Background.
	@param velocity The velocity of the Background.
	*/
	Background(JAM_Texture* sprite, float x, float y, float width, float height, float velocity);

	/**
	Destructs the Background object.
	*/
	~Background();

	/**
	A function that updates the Background.
	@param dt The delta time.
	*/
	void update(float dt);
};