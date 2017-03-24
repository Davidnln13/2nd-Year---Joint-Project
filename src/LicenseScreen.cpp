#include "LicenseScreen.h"
#include "ScreenManager.h"

LicenseScreen::LicenseScreen() :
	Screen(),
	m_playVideo(false),
	m_skip(false),
	m_licenseMovie()
{
	m_licenseMovie.openFromFile("./resources/Animations/License Screen.mov");
	m_licenseMovie.fit(0, 0, 1280, 720);
}

LicenseScreen::~LicenseScreen()
{

}

void LicenseScreen::update(GameState& current, GameState& previous)
{
	if (current == GameState::License)
	{
		//If we arent playing our video then play it, and set our bool to true
		if(m_playVideo == false)
		{
			m_licenseMovie.play();
			m_playVideo = true;
		}

		m_licenseMovie.update(); //update our movie

		if (m_licenseMovie.getStatus() == sfe::Status::Stopped) //if the movie is over
		{
			m_skip = false;
			auto tempState = current;
			current = GameState::Splash;
			previous = tempState;
			system("CLS");
		}

		//if we have skipped and our video is noit at the 3 second mark
		if (m_skip && m_licenseMovie.getPlayingOffset() < sf::seconds(3))
		{
			//then set the video to the 3 second mark
			m_licenseMovie.setPlayingOffset(sf::seconds(3));
		}
	}
}

void LicenseScreen::render(sf::RenderWindow& window, GameState& current, GameState& previous)
{
	if(current == GameState::License)
		window.draw(m_licenseMovie);
}	
void LicenseScreen::handleInput(Xbox360Controller& controller, GameState& current, GameState& previous)
{
	if (current == GameState::License)
	{
		if (controller.getCurrent().Start && controller.getPrevious().Start == false)
		{
			m_skip = true;
		}
		m_handledInput = true;
	}
	else
		m_handledInput = false;
}
