#include "Background.h"

/**************************************************************************************************************/

/*Constructs a Background object.*/
Background::Background(JAM_Texture* sprite, float x, float y, float width, float height, float velocity) 
	: JAM_Entity(sprite, x, y, width, height)
{
	/*initialise the velocity of the background*/
	this->velocity = velocity;
}

/**************************************************************************************************************/

/*Destructs a Background object.*/
Background::~Background()
{
}

/**************************************************************************************************************/

/*A function that updates the Background.*/
void Background::update(float dt)
{
	/*A variable for the update x position of the background*/
	float updatedX = getPosition().x - (velocity * dt);

	/*If the background is off the screen*/
	if (getPosition().x <= -getDimensions().x)
	{
		/*reset the position of the background*/
		updatedX += (getDimensions().x * 2.0f);
	}

	/*update the position of the background*/
	setX(updatedX);
}