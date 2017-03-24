#include "Game.h"

//updates per millisecond
static sf::Int32 MS_PER_UPDATE = 10.0;

Game::Game() :
	m_window(sf::VideoMode(1280, 720), "Joint Project"),
	m_isInGameViewSet(false),
	m_isViewReset(false),
	m_resourceManager(),
	m_screenManager(m_resourceManager.getTextureHolder(), m_resourceManager.getFontHolder(), m_audioManager),
	m_controller(),
	m_playScreen(m_screenManager.getPlayScreen()),
	m_hud(m_resourceManager.getTextureHolder(), m_resourceManager.getFontHolder())
{
	//Invoke our init method
	init();
}
void Game::init()
{
	//Can be Used to set the window to fullscreen
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();	

	m_inGameView.setSize(640, 360); //set our in game view to 640x360, we will focus this on the players vehicle during the race screen
	m_originView.setSize(1280, 720); //set our current view to 1280x720
	m_originView.setCenter(640, 360); //set it to focus on the centre of the screen

	m_window.setView(m_originView); //set our windows view to our original view
	m_window.setVerticalSyncEnabled(true);
	m_window.setKeyRepeatEnabled(false); //only creates 1 event during a joystick event (fixes multiple input handles per event)

	
	//loading our level loader data
	if (!LevelLoader::load(1, m_level))
	{
		std::cout << "ERROR ON YAML FILE" << std::endl;
		system("PAUSE");
	}

	m_screenManager.setLevelData(m_level);
}
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;
	while (m_window.isOpen())
	{
		processEvents();
		sf::Time dt = clock.restart();
		lag += dt.asMilliseconds();
		
		while (lag > MS_PER_UPDATE)
		{
			update();
			lag -= MS_PER_UPDATE;
		}                                                                                                                                              
		update();
		render();
	}
}

//Process our events here (input handling)
void Game::processEvents()
{
	sf::Event event;
	bool handledInput = false;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || m_screenManager.getCurrentState() == GameState::Exit)
		{
			m_window.close();
		}
		//If a joystick moved or button pressed event occurs, then handle input on our screens
		if (event.type == sf::Event::JoystickMoved && m_screenManager.getCurrentState() != GameState::Play && handledInput == false 
			|| event.type == sf::Event::JoystickButtonPressed && m_screenManager.getCurrentState() != GameState::Play && handledInput == false)
		{

			m_controller.update(); //update the controller state
			m_controller.handleInput(); //check what buttons/axis have been press/moved on the controller
			m_screenManager.handleInput(m_controller); //pass the controller to our screens and handle input using the controller
			handledInput = true; //set our bool to true so we dont go into this if statement multiple times during an event
			m_audioManager.handleInput(m_controller, m_screenManager.getCurrentState(), m_screenManager.getPreviousState());
		}
		//If we are in the race screen and our controller becomes diconnected, then pause the game and set our gamesatets
		if(event.type == sf::Event::JoystickDisconnected && m_screenManager.getCurrentState() == GameState::Play)
		{
			m_screenManager.getCurrentState() = GameState::Pause;
			m_screenManager.getPreviousState() = GameState::Play;
		}

	}
}
void Game::update()
{
	m_controller.update();
	m_audioManager.update(m_controller,m_screenManager.getCurrentState());
	//If our gamestate is in game, then handle input (we handle input here because we dont want to handle it during an event)
	if (m_screenManager.getCurrentState() == Play)
	{
		m_controller.handleInput();
		m_audioManager.handleInput(m_controller, m_screenManager.getCurrentState(), m_screenManager.getPreviousState());
		m_playScreen.handleInput(m_controller, m_screenManager.getCurrentState(), m_screenManager.getPreviousState());
	}

	//if the sc5reen manager's bool is true, then restrat the race screen
	if (m_screenManager.getRestartRace())
	{
		m_screenManager.resetRace(m_level);
	}

	m_screenManager.update();

	//Changing our view depending on if we are in the pause or game screen
	if (m_screenManager.getCurrentState() == GameState::Play && m_isInGameViewSet == false)
	{
		m_window.setView(m_inGameView); //set our view for the ingame screen
		m_isInGameViewSet = true;
		m_isViewReset = false;
	}
	if (m_screenManager.getCurrentState() != GameState::Play && m_isViewReset == false)
	{
		m_window.setView(m_originView);
		m_isInGameViewSet = false;
		m_isViewReset = true;
	}
}
void Game::render()
{
	//Clear the window
	m_window.clear();

	//render our windows
	m_screenManager.render(m_window);

	//Display anything drawn in the meantime
	m_window.display();
}