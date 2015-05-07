#include "Game.h"
#include "Pause.h"
#include "GameOver.h"

/**************************************************************************************************************/

/*Constructs the game object*/
Game::Game(JAM_StateManager * stateManager, SDL_Renderer* renderer, int screenWidth, int screenHeight)
	: JAM_State(stateManager, renderer, screenWidth, screenHeight)
{
	/*initialise the textures*/
	alienDude = new JAM_Texture("img/alienDude.png", renderer);
	backgroundStars = new JAM_Texture("img/backgroundStars.png", renderer);
	forceField = new JAM_Texture("img/forceField.png", renderer);

	/*initialise the backgrounds*/
	starsA = new Background(backgroundStars, 0.0f, 0.0f, (float)screenWidth, (float)screenHeight, 20.0f);
	starsB = new Background(backgroundStars, (float)screenWidth, 0.0f, (float)screenWidth, (float)screenHeight, 20.0f);

	/*initialise the player*/
	player = new Player(alienDude, 100.0f, 100.0f, 64.0f, 64.0f, JAM_Vec2(100.0f, 100.0f), (float)screenWidth, (float)screenHeight);

	/*initialise the particle effect for the player*/
	particleEffects.push_back(new JAM_ParticleEffect(player->getPosition(), true, renderer, 255, 0, 255, screenHeight));

	/*create an offset for the particle effect*/
	JAM_Vec2 offest = JAM_Vec2(0.0f, player->getDimensions().y);

	/*initialise the particle effect for the player*/
	particleEffects.push_back(new JAM_ParticleEffect(player->getPosition() + offest, true, renderer, 255, 0, 255, screenHeight));

	/*create an offset for the particle effect*/
	offest = JAM_Vec2(player->getDimensions().x, 0.0f);

	/*initialise the particle effect for the player*/
	particleEffects.push_back(new JAM_ParticleEffect(player->getPosition() + offest, true, renderer, 255, 0, 255, screenHeight));

	/*create an offset for the particle effect*/
	offest = JAM_Vec2(player->getDimensions().x, player->getDimensions().y);

	/*initialise the particle effect for the player*/
	particleEffects.push_back(new JAM_ParticleEffect(player->getPosition() + offest, true, renderer, 255, 0, 255, screenHeight));

	/*initialise the force fields*/
	for (int i = 0; i < 4; i++)
	{
		/*create the force field entity*/
		forceFields.push_back(new ForceField(forceField, (180.0f * i), ((i % 2) * (screenHeight - 300.0f)),
			50.0f, 300.0f, 50.0f, (float)screenWidth, (float)screenHeight));
	}

	/*initialise the bool for the first loop*/
	initalLoop = true;

	/*initialise the music*/
	music = new JAM_Audio("aud/Cool Hard Facts.ogg", true);
	music->startAudio();
}

/**************************************************************************************************************/

/*Destructs the game object*/
Game::~Game()
{
	/*stop music*/
	music->stopAudio();
	/*delete audio pointers*/
	delete music;
	/*delete pointers*/
	delete alienDude;
	delete backgroundStars;
	delete forceField;
	delete starsA;
	delete starsB;
	delete player;
	for (auto field : forceFields)
	{
		delete field;
	}
	for (auto particleEffect : particleEffects)
	{
		delete particleEffect;
	}
}

/**************************************************************************************************************/

/*handles inputs*/
bool Game::input()
{
	/*Check for user input*/
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{
		switch (incomingEvent.type)
		{
		case SDL_QUIT: /*If player closes the window, end the game loop*/

			SDL_Log("Exiting Main Loop");
			return false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (incomingEvent.button.button == SDL_TOUCH_MOUSEID || incomingEvent.button.button == SDL_BUTTON_LEFT)
				SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Touch/Click");
			break;
		}

		/*handle the player input*/
		player->input(incomingEvent);

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
bool Game::windowsInput(SDL_Event& incomingEvent)
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

		case SDLK_SPACE: /*If Space is pressed, go to the pause screen*/

			/*add the pause state*/
			stateManager->addState(new PauseState(stateManager, renderer, screenWidth, screenHeight, music));
			break;
		}
		break;
	}
	return true;
}

/**************************************************************************************************************/

/*handles android inputs*/
bool Game::androidInput(SDL_Event& incomingEvent)
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
	return true;
}

/**************************************************************************************************************/

/*updates the game*/
void Game::update(float dt)
{
	/*if the initial loop*/
	if (initalLoop)
	{
		/*add the pause state*/
		stateManager->addState(new PauseState(stateManager, renderer, screenWidth, screenHeight, music));
		initalLoop = false;
	}

	/*keep the music playing*/
	music->startAudio();

	/*update the backgrounds*/
	starsA->update(dt);
	starsB->update(dt);

	/*update the forceFields*/
	for (auto field : forceFields)
	{
		field->update(dt);
	}

	/*update the player*/
	player->update(dt);

	/*test for the collision*/
	for (auto field : forceFields)
	{
		/*test for intersection*/
		if (JAM_CollisionDetection::collisionRectRectDetection(player->getPosition(), player->getDimensions(),
			field->getPosition(), field->getDimensions()))
		{
			/*add the Game Over state*/
			stateManager->addState(new GameOver(stateManager, renderer, screenWidth, screenHeight, music));
		}
	}

	/*update the particle effect*/
	particleEffects[0]->setEmitter(player->getPosition());
	particleEffects[0]->update(dt);

	/*create an offset for the particle effect*/
	JAM_Vec2 offest = JAM_Vec2(0.0f, player->getDimensions().y);

	/*update the particle effect*/
	particleEffects[1]->setEmitter(player->getPosition() + offest);
	particleEffects[1]->update(dt);

	/*create an offset for the particle effect*/
	offest = JAM_Vec2(player->getDimensions().x, 0.0f);

	/*update the particle effect*/
	particleEffects[2]->setEmitter(player->getPosition() + offest);
	particleEffects[2]->update(dt);

	/*create an offset for the particle effect*/
	offest = JAM_Vec2(player->getDimensions().x, player->getDimensions().y);

	/*update the particle effect*/
	particleEffects[3]->setEmitter(player->getPosition() + offest);
	particleEffects[3]->update(dt);
}

/**************************************************************************************************************/

/*draws the game*/
void Game::draw()
{
	/*draw the backgrounds*/
	starsA->draw(renderer);
	starsB->draw(renderer);

	/*draw the force fields*/
	for (auto field : forceFields)
	{
		field->draw(renderer);
	}

	/*draw the particle effects of the player*/
	for (auto particleEffect : particleEffects)
	{
		particleEffect->draw(renderer);
	}

	/*draw the player*/
	player->draw(renderer);
}