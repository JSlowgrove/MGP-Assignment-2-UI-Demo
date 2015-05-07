#include "Pause.h"

/**************************************************************************************************************/

/*Constructs the pause object*/
PauseState::PauseState(JAM_StateManager * stateManager, SDL_Renderer* renderer, int screenWidth, int screenHeight, JAM_Audio* music)
	: JAM_State(stateManager, renderer, screenWidth, screenHeight)
{
	/*initialise the background*/
	background = new JAM_Texture("img/backgroundOverlay.png", renderer);

	/*initialise the text*/
	info = new JAM_Text("Hit SPACE to play", "font/Underdog_tt_hinted.ttf", 48, renderer, 255, 255, 255);
	
	/*initialise the music*/
	this->music = music;
}

/**************************************************************************************************************/

/*Destructs the pause object*/
PauseState::~PauseState()
{
	/*delete pointers*/
	delete background;
	delete info;
}

/**************************************************************************************************************/

/*handles inputs*/
bool PauseState::input()
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
bool PauseState::windowsInput(SDL_Event& incomingEvent)
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

		case SDLK_SPACE:  /*If Space is pressed, return to the game*/

			/*return to the game*/
			stateManager->removeLastState();
			break;
		}
		break;
	}
	return true;
}

/**************************************************************************************************************/

/*handles android inputs*/
bool PauseState::androidInput(SDL_Event& incomingEvent)
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

	case SDL_MOUSEBUTTONDOWN: /*If the mouse is pressed*/

		/*if the left mouse button return to the game*/
		if (incomingEvent.button.button == SDL_BUTTON_LEFT)
		{
			/*return to the game*/
			stateManager->removeLastState();
		}
		break;
	}
	return true;
}


/**************************************************************************************************************/

/*updates the pause*/
void PauseState::update(float dt)
{
	/*keep the music playing*/
	music->startAudio();
}

/**************************************************************************************************************/

/*draws the pause*/
void PauseState::draw()
{
	/*draw the background*/
	background->pushToScreen(renderer, 0, 0);

	/*draw the text*/
	info->pushToScreen(140, 50);
}