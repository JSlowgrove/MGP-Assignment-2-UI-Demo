#include "ForceField.h"

/**************************************************************************************************************/

/*Constructs a ForceField object.*/
ForceField::ForceField(JAM_Texture* sprite, float x, float y, float width, float height, float velocity, float screenWidth, 
	float screenHeight) 
	: JAM_Entity(sprite, x, y, width, height)
{
	/*initialise the velocity of the ForceField*/
	this->velocity = velocity;
	/*initialise the screen dimensions*/
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

/**************************************************************************************************************/

/*Destructs a ForceField object.*/
ForceField::~ForceField()
{
}

/**************************************************************************************************************/

/*A function that updates the ForceField.*/
void ForceField::update(float dt)
{
	/*A variable for the update x position of the ForceField*/
	float updatedX = getPosition().x - (velocity * dt);

	/*If the ForceField is off the screen*/
	if (updatedX + getDimensions().x < 0.0f)
	{
		/*reset the position of the ForceField*/
		updatedX += screenWidth + getDimensions().x;
	}

	/*update the position of the ForceField*/
	setX(updatedX);
}