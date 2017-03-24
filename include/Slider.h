#pragma once
#include "Widget.h"

//Description:	The slider is used as a visual indicator that the user can adjust the volume of an assigned sound to it.
//Date worked on: 08/03/17, 12/03/2017, 13/03/2017
//Authors: Daryl Keogh & Brian Leigh

class Slider : public Widget
{
public:
	Slider(std::string name, sf::Vector2f pos);
	void update() override;
	void render(sf::RenderWindow& window) override;
	void getFocus() override;
	void loseFocus() override;
	void playAnimation();
	void focus(std::string string);
	void handleInput(Xbox360Controller& controller) override;

	void setIndicator();
	void increaseGarageIndicator();
	void decreaseGarageIndicator();
	void setupAnimation();

	void setGarageTexture(sf::Texture& sliderTexture, sf::Texture& sliderPosTexture, sf::Font& font);
	void setTexture(sf::Texture& sliderTexture, sf::Texture& sliderPosTexture, sf::Font& font);
	void applyTexture(sf::Sprite& aSprite, sf::Texture& texture, sf::IntRect textureRect) const;

	void setSliderLevel(int level);

	//Getter
	int& getLevel();
private:
	bool m_firstSelected;
	bool m_playAnimation;
	bool m_drawIndicator;

	sf::IntRect m_indicatorRectArray[10];
	int m_indicatorIndex;

	sf::Vector2f m_position; //the position of our slider

	sf::Sprite m_sprite;
	sf::Sprite m_positionSprite;

	std::string m_name; //the name of our slider

	//The current value of our slider
	int m_currentVal;

	//Our animation objects
	thor::Animator<sf::Sprite, std::string> m_sliderAnimator;
	thor::Animator<sf::Sprite, std::string> m_tickAnimator;
	thor::FrameAnimation m_selectedAnimation;
	thor::FrameAnimation m_unselectedAnimation;
	sf::Clock m_clock;
	sf::Time m_timer;

	//Our Label
	Label m_label;

	//Our shader
	sf::Shader m_selectedShader;
	sf::Clock m_shaderClock; //clock will be used to update our shader

	//Our consts
	const float MIN_VAL = 0;
	const float MAX_VAL = 100;
	const float DEF_VAL = 50;
	const float VAL_CHANGE = 10;

	//For our garage screen
	int m_sliderLevel; //hold sthe current level of our slider which corresponds to an engine level
};