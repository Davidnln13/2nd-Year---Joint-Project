#pragma once
#include "Widget.h"

//Authors: David Nolan, Daryl Keogh
//Time Worked:
//David: 08/03/2017 15:10 - 15:15
//Daryl: 12/03/2017 09:00 - 10:00
//Description: Radio button determines wheter a particular sound is muted or not (on or off)

class RadioButton : public Widget
{
public:
	RadioButton(std::string name, sf::Vector2f pos);
	RadioButton(std::string name, sf::Vector2f pos, bool preRace, bool hasIcon = true);
	//RadioButton has focus or doesnt 
	void getFocus();
	void getFocusWithoutSelect();
	void loseFocus();
	void loseFocusWithoutSelect();
	void focus(std::string string);

	//update and render the button
	void update() override;
	void render(sf::RenderWindow& window) override;

	void handleInput(Xbox360Controller& controller) override;

	//sets up our animation
	void setUpAnimation();
	void playAnimation();
	void playTick(std::string string);
	void animateTick();
	//Sets our textures
	sf::IntRect getTextureRect() { return m_iconSprite.getTextureRect(); };
	void setTexture(sf::Texture& radioBtnTexture, sf::Texture& iconTexture, sf::Font& font, sf::IntRect iconRect);
	void setTexture(sf::Texture& radioBtnTexture, sf::Texture& iconTexture, sf::Font& font);
	//methods to set the range of the sprite sheet the variables can use
	void setTextureRectCar(sf::IntRect aRect);
	void setTextureRectTrack(sf::IntRect aRect);
	void setTextureRectLaps(sf::IntRect aRect);
	void setTextureRectAi(sf::IntRect aRect);
	void setTextureRectLetters(sf::IntRect aRect);
	bool isAnimationPlaying();
	void applyTexture(sf::Sprite& aSprite, sf::Texture& texture, sf::IntRect textureRect) const;
private:
	bool m_hasIcon;
	bool m_checked;
	bool m_playAnimation;
	bool m_playTick;
	bool m_isPreRace; //bool to hold whete rthis radio button belongs in the pre race screen

	sf::Vector2f m_currentPos;
	sf::Sprite m_sprite;
	sf::Sprite m_iconSprite;

	std::string m_name;
	std::string m_lastTickAnimation; //hold sthe neame of our last tick animation

	Label m_label;

	//Our shader
	sf::Shader m_selectedShader;
	sf::Clock m_shaderClock; //clock will be used to update our shader

	//Animation objects
	thor::Animator<sf::Sprite, std::string> m_buttonAnimator;
	thor::Animator<sf::Sprite, std::string> m_tickAnimator;
	thor::FrameAnimation m_selectedAnimation;
	thor::FrameAnimation m_unselectedAnimation;
	thor::FrameAnimation m_checkAnimation;
	thor::FrameAnimation m_uncheckAnimation;
	sf::Clock m_tickClock;
	sf::Clock m_btnClock;
	sf::Time m_tickTimer;;
	sf::Time m_btnTimer;
};