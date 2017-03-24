#include "SplashScreen.h"
#include "ScreenManager.h"

SplashScreen::SplashScreen() :
	Screen(),
	m_skip(false),
	m_playMovie(false),
	m_SplashMovie(),
	easeOut(false)
	 
{
	//Set up the parameters for the video
	m_SplashMovie.openFromFile("./resources/Animations/Splash Screen.mov"); 
	m_SplashMovie.fit(0, 0, 1280, 720, false); //Fit the movie to the screen
	m_hellRaiser.openFromFile("./resources/Audio/HellRaiser.wav");
	
}

SplashScreen::~SplashScreen()
{

}
//Used to update the splash screen
void SplashScreen::update(GameState& current, GameState& previous)
{
	//Check if the current gamestate is Splash
	if (current == GameState::Splash)
	{
		//If the movie hasn't played yet, play it and set the playMovie bool to true to prevent it from playing again.
		if (m_playMovie == false)
		{
			
			m_hellRaiser.setVolume(50);
			m_hellRaiser.play();
			m_hellRaiser.setPlayingOffset(sf::seconds(1.70));
			m_SplashMovie.play();
			m_playMovie = true;
		}

		m_SplashMovie.update();


		//Check to see if the movie has stopped
		if (m_SplashMovie.getStatus() == sfe::Status::Stopped)
		{
			//Set the gamestate to the next menu but save the current gamestate
			auto tempState = current;
			 
			m_hellRaiser.stop();
			 
			current = GameState::MainMenu;
			previous = tempState;
			system("CLS");
		}
		//Used to skip the movie towards the end if it's not already passed that point
		if (m_skip && m_SplashMovie.getPlayingOffset() < sf::seconds(9))
		{
			m_SplashMovie.setPlayingOffset(sf::seconds(9));
		}
	}
}
//Used to draw the movie to the screen

void SplashScreen::render(sf::RenderWindow& window, GameState& current, GameState& previous)
{
	if (current == GameState::Splash)
	{
		window.draw(m_SplashMovie);
	}
}

void SplashScreen::handleInput(Xbox360Controller& controller, GameState& current, GameState& previous)
{
	//Checks if the start button has been pressed and hasnt been pressed before, if so set skip to true.
	if (current == GameState::Splash)
	{
		if (controller.getCurrent().Start && controller.getPrevious().Start == false)
		{
			m_hellRaiser.stop();
			m_skip = true;
		}
		m_handledInput = true;
	}
	else
		m_handledInput = false;
}