#include "Player.h"

/**************************************************************************************************************/

/*Constructs a Player object.*/
Player::Player(JAM_Texture* sprite, float x, float y, float width, float height, JAM_Vec2 velocity, float screenWidth, 
	float screenHeight) 
	: JAM_Entity(sprite, x, y, width, height)
{
	/*initialise the velocity of the background*/
	this->velocity = velocity;
	/*initialise the user commands*/
	up = down = left = right = false;
	/*initialise the screen dimensions*/
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

/**************************************************************************************************************/

/*Destructs a Player object.*/
Player::~Player()
{
}

/**************************************************************************************************************/

/*A function that handles the input for the Player.*/
void Player::input(SDL_Event incomingEvent)
{
	switch (incomingEvent.type)
	{
	case SDL_KEYDOWN:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_w: /*If W/Up is pressed, set the up command to true*/
		case SDLK_UP:
			
			up = true;
			break;

		case SDLK_s: /*If S/Down is pressed, set the down command to true*/
		case SDLK_DOWN:

			down = true;
			break;

		case SDLK_a: /*If A/Left is pressed, set the left command to true*/
		case SDLK_LEFT:

			left = true;
			break;

		case SDLK_d: /*If D/Right is pressed, set the right command to true*/
		case SDLK_RIGHT:

			right = true;
			break;
		}
		break;

	case SDL_KEYUP:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_w: /*If W/Up is released, set the up command to false*/
		case SDLK_UP:

			up = false;
			break;

		case SDLK_s: /*If S/Down is released, set the down command to false*/
		case SDLK_DOWN:

			down = false;
			break;

		case SDLK_a: /*If A/Left is released, set the left command to false*/
		case SDLK_LEFT:

			left = false;
			break;

		case SDLK_d: /*If D/Right is released, set the right command to false*/
		case SDLK_RIGHT:

			right = false;
			break;
		}
		break;
	}
}

/**************************************************************************************************************/

/*A function that updates the Player.*/
void Player::update(float dt)
{
	/*A variable for the updated positions*/
	float updatedX = getPosition().x;
	float updatedY = getPosition().y;

	/*check if the up user command is true*/
	if (up)
	{
		/*update the updated position of the player*/
		updatedY -= (velocity.y * dt);
	}

	/*check if the down user command is true*/
	if (down)
	{
		/*update the updated position of the player*/
		updatedY += (velocity.y * dt);
	}

	/*check if the left user command is true*/
	if (left)
	{
		/*update the updated position of the player*/
		updatedX -= (velocity.x * dt);
	}

	/*check if the right user command is true*/
	if (right)
	{
		/*update the updated position of the player*/
		updatedX += (velocity.x * dt);
	}

	/*if the updated position is off the right of the screen*/
	if (updatedX >= (screenWidth - getDimensions().x))
	{
		/*reset the updated x position*/
		updatedX = getPosition().x;
	}

	/*if the updated position is off the left of the screen*/
	if (updatedX <= 0.0f)
	{
		/*reset the updated x position*/
		updatedX = getPosition().x;
	}

	/*if the updated position is off the top of the screen*/
	if (updatedY >= (screenHeight - getDimensions().y))
	{
		/*reset the updated y position*/
		updatedY = getPosition().y;
	}

	/*if the updated position is off the bottom of the screen*/
	if (updatedY <= 0.0f)
	{
		/*reset the updated y position*/
		updatedY = getPosition().y;
	}

	/*update the position of the player*/
	setPosition(updatedX, updatedY);
}