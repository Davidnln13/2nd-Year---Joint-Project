#pragma once
#include "Screen.h"
#include "sfeMovie\Movie.hpp" //lets us play video files
#include "SFML\Audio.hpp"

/// <summary>
/// Our splash screen, this will be used to display some sort of animation (video or thor)
/// Authors: Brian Leigh
/// </summary>
class SplashScreen : public Screen
{
public:
	SplashScreen();
	~SplashScreen();

	void update(GameState& current, GameState& previous) override;
	void render(sf::RenderWindow& window, GameState& current, GameState& previous) override;
	void handleInput(Xbox360Controller& controller, GameState& current, GameState& previous) override;

private:
	bool m_skip;
	bool m_playMovie;
	sfe::Movie m_SplashMovie;
	sf::Music m_hellRaiser;
	bool easeOut;
	 

};