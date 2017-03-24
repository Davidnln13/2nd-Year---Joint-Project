#include "ScreenManager.h"

ScreenManager::ScreenManager(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio) :
	m_inputHandled(false),
	m_license(),
	m_splash(),
	m_mainMenu(resourceHolder, fontHolder, audio),
	m_help(resourceHolder, fontHolder, audio),
	m_options(resourceHolder, fontHolder, audio),
	m_preRace(resourceHolder, fontHolder, audio),
	m_postRace(resourceHolder, fontHolder, audio),
	m_highscore(resourceHolder, fontHolder, audio),
	m_pause(resourceHolder, fontHolder, audio),
	m_play(resourceHolder, fontHolder, audio),
	m_garage(resourceHolder, fontHolder, m_play.getPlayer(), audio)
{

	//Adding our screens into our screen array
	m_screens[0] = &m_license;
	m_screens[1] = &m_splash;
	m_screens[2] = &m_mainMenu;
	m_screens[3] = &m_help;
	m_screens[4] = &m_options;
	m_screens[5] = &m_garage;
	m_screens[6] = &m_preRace;
	m_screens[7] = &m_postRace;
	m_screens[8] = &m_highscore;
	m_screens[9] = &m_play;
	m_screens[10] = &m_pause;
}

void ScreenManager::update()
{
	//if we have entered the race creen and the game is not ready, set the ai amount on the race and set the game as ready
	if (m_currentState == Play && m_play.isGameReady() == false)
	{
		m_play.setRaceProperties(m_preRace.getLapAmount(),m_preRace.getAiAmount());
		
		m_play.setGameReady(true);
		toWriteOnce = true;
	}

	//if we are now in th emain menu and we were on post race then update our highscore tabel
	if (m_currentState == MainMenu && m_previousState == PostRace)
	{ 
		if (toWriteOnce == true)
		{
			m_highscore.updateFile(m_postRace.getName(),m_play.getPlayer().getBestlapTime(), m_play.getPlayer().getOverallTime() - takeAway, m_play.getNoOfLaps());
			takeAway += m_play.getPlayer().getOverallTime();

			toWriteOnce = false;
		}
		
		 
	}

	//if we are now in the main menu and our previous was pause, then we restart our race variables!
	if (m_currentState == MainMenu || m_currentState == PostRace && m_previousState == Play)
	{
		m_restartRace = true;
	}

	//if our handledInput bool is true then set it to false
	if(m_inputHandled == true)
		m_inputHandled = false;

	//range based loop to update our screens
	for (auto &screen : m_screens)
	{
		screen->update(m_currentState, m_previousState);
	}
}

void ScreenManager::render(sf::RenderWindow& window)
{
	//range based loop to draw our screens
	for (auto &screen : m_screens)
	{
		screen->render(window, m_currentState, m_previousState);
	}
}

void ScreenManager::handleInput(Xbox360Controller& controller)
{
	//only handle input while our bool is false
	if (m_inputHandled == false)
	{
		//loop through each of our screens and invoke the handleInput method
		for (auto& screen : m_screens)
		{
			screen->handleInput(controller, m_currentState, m_previousState);
			if (screen->m_handledInput) //if the screen has handled input then return from input handling
			{
				//If we have gone to the game screen, then set our pause screen sprite the track sprite
				if(m_currentState == Play)
					m_pause.setTrackTexture(m_play.getTrack().getSprite().getTexture());

				m_inputHandled = true;
				break; //break out of our range loop
			}
		}
	}
}

void ScreenManager::resetRace(LevelData& level)
{
	m_play.reset(level);
	m_restartRace = false;
}

void ScreenManager::setLevelData(LevelData& level)
{
	m_play.setLevelData(level);
}

GameState& ScreenManager::getCurrentState()
{
	return m_currentState;
}
GameState& ScreenManager::getPreviousState()
{
	return m_previousState;
}

PlayScreen& ScreenManager::getPlayScreen()
{
	return m_play;
}

bool ScreenManager::getRestartRace()
{
	return m_restartRace;
}