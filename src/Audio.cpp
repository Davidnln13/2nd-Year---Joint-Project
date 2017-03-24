#include "Audio.h"
#include "ScreenManager.h"
#include "Xbox360Controller.h"

Audio::Audio()
{
	//music
	m_menuMusic[0].openFromFile("./resources/Audio/Honom - Purple Sun.ogg");
	m_menuMusic[1].openFromFile("./resources/Audio/Hotline Miami - Perturbator.ogg");
	m_menuMusic[2].openFromFile("./resources/Audio/Lucy In Disguise - Bristol Nights.ogg");
	m_menuMusic[3].openFromFile("./resources/Audio/Makeup And Vanity Set - Implant.ogg");
	m_menuMusic[4].openFromFile("./resources/Audio/Miami Nights 1984 - Ocean Drive.ogg");
	m_menuMusic[5].openFromFile("./resources/Audio/Michael Cassette - Regatta.ogg");
	m_menuMusic[6].openFromFile("./resources/Audio/Nightstop - Dangerous Desires.ogg");
	m_menuMusic[7].openFromFile("./resources/Audio/Robert Parker - Running Wild.ogg");
	m_menuMusic[8].openFromFile("./resources/Audio/A Space Love Adventure - Power Rush.ogg");
	m_menuMusic[9].openFromFile("./resources/Audio/VHS Dreams - R.e.d.m.ogg");

	if (!m_soundBuffer[0].loadFromFile("./resources/Audio/Button.wav"))
	{
		std::cout << "Cant Find File" << std::endl;
	}
	m_soundArray[0].setBuffer(m_soundBuffer[0]);
	if (!m_soundBuffer[1].loadFromFile("./resources/Audio/Upcar.wav"))
	{
		std::cout << "Cant Find File" << std::endl;
	}
	m_soundArray[1].setBuffer(m_soundBuffer[1]);
	if (!m_soundBuffer[2].loadFromFile("./resources/Audio/ReadySetGo.ogg"))
	{
		std::cout << "Cant Find File" << std::endl;
	}
	m_soundArray[2].setBuffer(m_soundBuffer[2]);
	if (!m_soundBuffer[3].loadFromFile("./resources/Audio/Horn.wav"))
	{
		std::cout << "Cant Find File" << std::endl;
	}
	m_soundArray[3].setBuffer(m_soundBuffer[3]);
	if (!m_soundBuffer[4].loadFromFile("./resources/Audio/Alarm.wav"))
	{
		std::cout << "Cant Find File" << std::endl;
	}
	m_soundArray[4].setBuffer(m_soundBuffer[4]);
	if (!m_soundBuffer[5].loadFromFile("./resources/Audio/StartCar.wav"))
	{
		std::cout << "Cant Find File" << std::endl;
	}
	m_soundArray[5].setBuffer(m_soundBuffer[5]);
	if (!m_soundBuffer[6].loadFromFile("./resources/Audio/Caraccelerate.wav"))
	{
		std::cout << "Cant Find File" << std::endl;
	}
	m_soundArray[6].setBuffer(m_soundBuffer[6]);
	if (!m_soundBuffer[7].loadFromFile("./resources/Audio/MoveMenu.wav"))
	{
		std::cout << "Cant Find File" << std::endl;
	}
	m_soundArray[7].setBuffer(m_soundBuffer[7]);
	for (int i = 0; i < 8; i++)
	{
		m_soundArray[i].setVolume(50);
	}
	m_soundArray[1].setPitch(2);
}
void Audio::update(Xbox360Controller& controller, GameState& current)
{
	//if were in the menu and weve pressed a button on the controller
	if (current != GameState::Splash && current != GameState::License && m_startedMoving == true)
	{
		//set the first song to play
		if (m_playFirstSong == false)
		{
			m_menuMusic[musicIndexer].play();
			m_playFirstSong = true;
		}

		//if that song ends play the next in the array


		if (m_menuMusic[musicIndexer].getStatus() == sf::Music::Status::Stopped)
		{
			if (m_songOver == true)
			{
				musicIndexer++;

			}
				if (musicIndexer >= 10)
					musicIndexer = 0;
				if (musicIndexer < 0)
					musicIndexer = 9;
			
			m_menuMusic[musicIndexer].play();

		}


	}
	 
	
}
void Audio::handleInput(Xbox360Controller& controller, GameState& current, GameState& previous)
{
	if (current != GameState::License && current != GameState::Splash)
	{	
		//if we started moving play the music
		m_startedMoving = true;
		//x for previous song
		if (controller.getCurrent().X && controller.getPrevious().X == false)
		{

			m_menuMusic[musicIndexer].stop();
			musicIndexer--;
			if (musicIndexer < 0)
			{
				musicIndexer = 9;
			}
			 
			m_songOver = false;
			
		}
		 
			
			 
		
		//y for next song
		else if (controller.getCurrent().Y && controller.getPrevious().Y == false)
		{
			
			m_menuMusic[musicIndexer].stop();
			musicIndexer++;
			if (musicIndexer > 9)
			{
				musicIndexer = 0;
			}
			 
			m_songOver = false;
		}
		else
		{
			m_songOver = true;
		}
		 
	
	}

	
}