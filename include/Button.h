#pragma once
#include "Widget.h"

//pre reference to gamestate
enum GameState;

/*
Name: David Nolan
Student Number: c00204958
Time Worked: 08/03/2017 11.00 - 11.40  40 mins
Time Worked: 08/03/2017 12.00 - 1.00  1 hour
Time Worked: 09/03/2017 10:30 - 11.30 1 hour
Time Worked: 09/03/2017 12.10 - 1.10 1 hour
Total Time: 3h 40 mins
*/

//class for the buttons used in our menus
class Button : public Widget
{
public:
	Button(sf::Vector2f pos, sf::String name);
	//button has focus or doesnt 
	void getFocus() override;
	void loseFocus() override;
	void focus(sf::String string); 
	//button is clickede or isnt
	void clickedButton() {m_clicked = true;};
	void unClickedButton() {m_clicked = false; };
	//update and render the button
	void update()override;
	void render(sf::RenderWindow& window) override;
	void changeGameState(GameState & current, GameState & previous);
	void setAlpha(int alphaPerc = 100);
	void setFinalAlpha(int alphaPerc = 100);
	void setAnimation();
	void setFont(sf::Font& font);
	void animateButton();

	//handles any input
	void handleInput(Xbox360Controller& controller) override;

	//getter and setter functions for our variables 
	void setFinalPosition(float x, float y) { m_endPosition.x = x; m_endPosition.y = y; };
	void setTexture(sf::Texture &texture);
	void setIconTexture(sf::Texture &iconTexture);
	void setCurrentPosition(sf::Vector2f v1);
	void setFinalPosition(sf::Vector2f v1);
	int getNewAlpha(int newPercentage);

	sf::Vector2f getCurrentPos() const { return m_currentPosition; };
	sf::Vector2f getFinalPos() const { return m_endPosition; };

private:
	bool m_playAnimation;

	//temp label
	Label m_label;

	bool m_clicked = false;
	bool m_hasFocus = false;
	// 2 positions for current and final
	sf::Vector2f m_currentPosition;
	sf::Vector2f m_endPosition;
	//button has a texture and sprite
	sf::String m_buttonName;
	sf::Sprite m_iconSprite;
	sf::Sprite m_sprite;

	//const rectangle, will be the first button sprite in the spritesheet
	const sf::IntRect m_defualtRect = sf::IntRect(0, 0, 423, 98);
	//Animation objects
	//this our holder for our animations
	thor::Animator<sf::Sprite, std::string> m_animator;
	//This is our animation in
	thor::FrameAnimation m_selectedAnimation;
	thor::FrameAnimation m_unselectedAnimation;
	sf::Clock m_clock;
	sf::Time m_timer;

	int m_finalAlpha;
	int m_currentAlpha;

	//Our consts
	const unsigned SCROLL_SPEED = 3;
	const unsigned FADE_SPEED = 3;
};