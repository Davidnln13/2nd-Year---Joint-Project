#pragma once
#include "SFML\Graphics.hpp"
#include "Thor\Resources.hpp"
#include "LevelLoader.h"
#include "Button.h"
#include "RadioButton.h"
#include "Xbox360Controller.h"
#include "SFML\Audio.hpp"
#include "Audio.h"

enum GameState;

/// <summary>
/// base class in our screen Heirarchy
/// Authors: Eoghan McGrath & Daryl Keogh
/// </summary>
class Screen
{
public:
	Screen();
	Screen(Audio& audio);
	virtual void update(GameState& current, GameState& previous) = 0;
	virtual void render(sf::RenderWindow& window, GameState& current, GameState& previous) = 0;
	virtual void handleInput(Xbox360Controller& controller, GameState& current, GameState& previous) = 0;
	virtual ~Screen() = 0;

	bool m_handledInput; //bool to determine if the screen has handled input, we will use this to stop events from doubling up on input events generated

	//Our audio reference object, each class will have a reference to our audio so they can invoke all the methods of the sf::Music class 
	Audio* m_audioP;
};

