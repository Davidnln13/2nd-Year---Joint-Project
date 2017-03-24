#pragma once
#include "Screen.h"
#include "sfeMovie\Movie.hpp" //lets us play video files

/// <summary>
/// Our License screen will display the members of the team that worked on the game by playing a very simple animation(video)
/// Authors: Daryl Keogh
/// </summary>
class LicenseScreen : public Screen
{
public:
	LicenseScreen();
	~LicenseScreen();

	void update(GameState& current, GameState& previous) override;
	void render(sf::RenderWindow& window, GameState& current, GameState& previous) override;
	void handleInput(Xbox360Controller& controller, GameState& current, GameState& previous) override;
private:
	bool m_playVideo; //bool to show wheter to play the video or not
	bool m_skip; //bool to hold if we have skipped the screen or not

	sfe::Movie m_licenseMovie; //our movie object, will be used to play a video
};