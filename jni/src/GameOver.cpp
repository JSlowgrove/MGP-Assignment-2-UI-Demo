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
	info = new JAM_Text("Hit SPACE to restart", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(48.0f, screenHeight), 
		renderer, 255, 255, 255);

	/*initialise the button*/
	button = new JAM_Button(new JAM_Texture("img/buttonBackground.png", renderer), JAM_Utilities::scaleNumber(140.0f, screenHeight),
		JAM_Utilities::scaleNumber(50.0f, screenHeight),
		"Press to restart", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(48.0f, screenHeight),
		255, 255, 255, renderer,
		JAM_Utilities::scaleNumber(25.0f, screenHeight),
		JAM_Utilities::scaleNumber(100.0f, screenHeight), JAM_Utilities::scaleNumber(50.0f, screenHeight));

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
		}
#ifdef __ANDROID__

		/*handle the android inputs*/
		return androidInput(incomingEvent);

#elif _WIN32	

		/*handle the windows inputs*/
		return windowsInput(incomingEvent);

#endif

	}
	return true;
}

/**************************************************************************************************************/

/*handles windows inputs*/
bool GameOver::windowsInput(SDL_Event& incomingEvent)
{
	switch (incomingEvent.type)
	{
	case SDL_KEYDOWN:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_ESCAPE: /*If Escape is pressed, end the game loop*/

			SDL_Log("Exiting Main Loop");
			return false;
			break;

		case SDLK_SPACE: /*If Space is pressed, restart the game*/

			/*restart the game*/
			stateManager->changeState(new Game(stateManager, renderer, screenWidth, screenHeight));
			break;
		}
		break;
	}
	return true;
}

/**************************************************************************************************************/

/*handles android inputs*/
bool GameOver::androidInput(SDL_Event& incomingEvent)
{
	switch (incomingEvent.type)
	{
	case SDL_KEYDOWN:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_AC_BACK: /*If Back is pressed on the phone, end the game loop*/

			SDL_Log("Exiting Main Loop");
			return false;
			break;
		}
		break;
	}

	/*if the button is pressed restart the game*/
	if (button->input(incomingEvent))
	{
		/*restart the game*/
		stateManager->changeState(new Game(stateManager, renderer, screenWidth, screenHeight));
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
	background->pushToScreen(renderer, (int)JAM_Utilities::scaleNumber(0.0f, screenHeight), 
		(int)JAM_Utilities::scaleNumber(0.0f, screenHeight), screenWidth, screenHeight);

#ifdef __ANDROID__

	/*draw the button*/
	button->draw(renderer);
	button->drawText(renderer);

#elif _WIN32	

	/*draw the text*/
	info->pushToScreen((int)JAM_Utilities::scaleNumber(120.0f, screenHeight), (int)JAM_Utilities::scaleNumber(50.0f, screenHeight));

#endif
}