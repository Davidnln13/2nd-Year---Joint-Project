#pragma once
#include "Thor/Resources.hpp"
#include "Label.h"
#include "Screen.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

/// <summary>
/// Our Highscore screen will be used to display the top 10 highscores achieved in the game
/// Authors: Daryl Keogh, David Nolan
/// </summary>
/// 
class HighscoreScreen : public Screen
{
public:
	HighscoreScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio);
	~HighscoreScreen();
	//all of the variables to be displayed on the  highscore from play
	void updateFile(std::string playerName, float playerBestLapTime, float playerOverallTime, int playerLapNumber);
	void update(GameState& current, GameState& previous) override;

	void render(sf::RenderWindow& window, GameState& current, GameState& previous) override;

	void handleInput(Xbox360Controller& controller, GameState& current, GameState& previous) override;
private:
	sf::Sprite m_bgSprite;
	Label m_backLabel;
	sf::Sprite m_bSprite;

	//highscore label
	Label m_highscore;
	Label m_identifiers;
	Label m_minutesSeconds;
	//label array for each section so different sized strings dont distort the screen
	Label m_highscoreLabelsName[10];
	Label m_highscoreLabelsLap[10];
	Label m_highscoreLabelsOverall[10];
	Label m_highscoreLabelsLapNo[10];
	//file
	 
 
	 
 
	//the 10 names
	std::string m_names[10];
	//the 10 best lap times
	float m_bestLapTimes[10];
	//the ten overall laptimes
	float m_overallTimes[10];
	//the ten number of laps
	int m_numberOfLaps[10];
	std::string m_backToFile[10];
	//labels positions
	//names pos
	int posXName;
	int posYName;
	//laps pos
	int posXLaps;
	int posYLaps;
	//overall pos
	int posXOverall;
	int posYOverall;
	//lap no
	int posXLapNo;
	int posYLapNo;

	//string arrays from string stream
	std::string convertOverallTime[10];
	std::string convertBestTime[10];
	//string streams
	std::stringstream sstream[10];
	std::stringstream sstream2[10];
	//draw initially
	bool once = false;
	bool showOnce = false;
 
};