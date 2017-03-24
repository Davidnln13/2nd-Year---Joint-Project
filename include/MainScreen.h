#pragma once
#include "Screen.h"


/// <summary>
/// Our Mainscreen is our main menu, here we will display buttons that the user can use to navigate the
/// game and access different screens.
/// Authors: Daryl Keogh 
/// </summary>
class Audio;

class MainScreen : public Screen
{
public:
	MainScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio);
	~MainScreen();
	 
	void update(GameState& current, GameState& previous) override;
	void render(sf::RenderWindow& window, GameState& current, GameState& previous) override;
	void handleInput(Xbox360Controller& controller, GameState& current, GameState& previous) override;
	void scrollMenu();
private:
	bool m_firstFocused;
	bool m_canScroll;
	bool m_scrollUp;
	bool m_scrollDown;
	bool m_playSong;
	//our background sprite
	sf::Sprite m_sprite;

	//holds the index of the current button that we are selecting
	int m_btnIndex;

	//Our button objects
	Button m_raceBtn;
	Button m_garageBtn;
	Button m_highscoreBtn;
	Button m_helpBtn;
	Button m_optionsBtn;
	Button m_exitbtn;

	//Our array, can use range based loops for invoking methods in all buttons
	Button* m_btnArray[6];
};