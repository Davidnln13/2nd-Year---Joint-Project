#pragma once
#include "Screen.h"
#include "Button.h"

/// <summary>
/// our pause screen is just used to indicate to the player that the game is paused. they can use buttons
/// to go to the main menu or continue playing, they can also access the help & options menus from here.
/// Authors: Daryl Keogh 
/// </summary>

class PauseScreen : public Screen
{
public:
	PauseScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio); //our constructor
	~PauseScreen();

	void update(GameState& current, GameState& previous) override;
	void render(sf::RenderWindow& window, GameState& current, GameState& previous) override;
	void handleInput(Xbox360Controller& controller, GameState& current, GameState& previous) override;

	void setTrackTexture(const sf::Texture* texture);
private:
	bool m_firstFocused; //bool to hold if we have focused on a button when we first enter the screen
	sf::Sprite m_sprite; //our bg sprite, we just draw a black vignette on the screen 
	sf::RenderTexture m_rTexture; //our render texture, we will use this to display a vignette over the game

	//Our button objects
	int m_btnIndex; //holds the index of the button we are selecting
	Button m_continueBtn;
	Button m_helpBtn;
	Button m_optionsBtn;
	Button m_menuBtn;
	Button* m_btnArray[4]; //our btn array, we will use to to easily update and render our buttons

	sf::Sprite m_trackSprite; //we will use this to draw our tracks sprite in the background while the game is paused
};