#pragma once
#include "LevelLoader.h"
#include "ResourceManager.h"
#include "Screen.h"
#include "GarageScreen.h"
#include "HelpScreen.h"
#include "HighscoreScreen.h"
#include "LicenseScreen.h"
#include "MainScreen.h"
#include "OptionsScreen.h"
#include "PauseScreen.h"
#include "PlayScreen.h"
#include "PostRaceScreen.h"
#include "PreRaceScreen.h"
#include "SplashScreen.h"
#include "Xbox360Controller.h"
#include "Audio.h"
enum GameState
{
	License,
	Splash,
	Help,
	Options,
	MainMenu,
	Garage,
	PreRace,
	Highscore,
	Pause,
	PostRace,
	Play,
	Exit
};

class ScreenManager
{
public: 
	ScreenManager(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& music);
	void update();
	void render(sf::RenderWindow& window);
	void handleInput(Xbox360Controller& controller);
	void resetRace(LevelData& level);


	//Setters
	void setLevelData(LevelData& level);

	//getters
	GameState& getCurrentState();
	GameState& getPreviousState();
	PlayScreen& getPlayScreen();
	bool getRestartRace();
private:
	bool m_restartRace; //bool to show whteer to restart the play/race screen or not
	bool m_inputHandled;

	//Our gamestates
	GameState m_currentState;
	GameState m_previousState;

	//Our screen array
	Screen* m_screens[11];

	//Our screen Objects
	LicenseScreen m_license;
	SplashScreen m_splash;
	MainScreen m_mainMenu;
	HelpScreen m_help;
	OptionsScreen m_options;
	PlayScreen m_play;
	GarageScreen m_garage;
	PreRaceScreen m_preRace;
	PostRaceScreen m_postRace;
	HighscoreScreen m_highscore;
	PauseScreen m_pause;
	float takeAway = 0;
	bool toWriteOnce = false;
};