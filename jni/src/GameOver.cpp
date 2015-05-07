#include "GameOver.h"
#include "Game.h"

/**************************************************************************************************************/

/*Constructs the GameOver object*/
GameOver::GameOver(JAM_StateManager * stateManager, SDL_Renderer* renderer, int screenWidth, int screenHeight, JAM_Audio* music)
	: JAM_State(stateManager, renderer, screenWidth, screenHeight)
{
	/*initialise the background*/
	background = new JAM_Texture("img/backgroundOverlay.png", renderer);

	/*initialise the text*/
	info = new JAM_Text("Hit SPACE to restart", "font/Underdog_tt_hinted.ttf", 48, renderer, 255, 255, 255);

	/*initialise the music*/
	this->music = music;
}

/**************************************************************************************************************/

/*Destructs the GameOver object*/
GameOver::~GameOver()
{
	/*delete pointers*/
	delete background;
	delete info;
}

/**************************************************************************************************************/

/*handles inputs*/
bool GameOver::input()
{
	/*Check for user input*/
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{
		switch (incomingEvent.type)
		{
		case SDL_QUIT: /*If player closes the window, end the game loop*/

			return false;
			break;

		case SDL_KEYDOWN:

			switch (incomingEvent.key.keysym.sym)
			{
			case SDLK_SPACE: /*If Space is pressed, restart the game*/

				/*restart the game*/
				stateManager->changeState(new Game(stateManager, renderer, screenWidth, screenHeight));
				break;
			}
			break;
		}
	}
	return true;
}

/**************************************************************************************************************/

/*updates the pause*/
void GameOver::update(float dt)
{
	/*keep the music playing*/
	music->startAudio();
}

/**************************************************************************************************************/

/*draws the pause*/
void GameOver::draw()
{
	/*draw the background*/
	background->pushToScreen(renderer, 0, 0);

	/*draw the text*/
	info->pushToScreen(120, 50);
}