#pragma once
#include <SFML\Graphics.hpp>
#include "Button.h"
#include "ResourceManager.h"
#include "ScreenManager.h"
#include "LevelLoader.h"
#include "Xbox360Controller.h"
#include "Audio.h"

//Game loop
class Game
{
public:
	Game();
	void run();
	void init();
	void processEvents();
private:
	void update();
	void render();
 
	sf::RenderWindow m_window;
	sf::View m_inGameView; //our game view, we will change this during the game, while we are in race we will follow the player using this view
	sf::View m_originView; //when we leave the race screen we need to reset our view
	bool m_isInGameViewSet; //bool to hold if we have set our ingame view or not
	bool m_isViewReset; //bool to hold if we reset our view or not

	ResourceManager m_resourceManager; //our resource manager object
	ScreenManager m_screenManager; //our screen manager, will handle all of our screen objects
	Xbox360Controller m_controller; //our controller object, will be used to handle input
	//A reference to our gamescreen (this will be used so we can call our handle update each frame instead of during an event)
	PlayScreen& m_playScreen;
	Audio m_audioManager;
	HUD m_hud;
	//Our level loader data 
	LevelData m_level;
};