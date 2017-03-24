#pragma once
#include "SFML\Graphics.hpp"
#include "Thor\Animations.hpp"
#include "Thor\Resources.hpp"
#include "Label.h"

/// <summary>
/// The paint class contains a sprite which is a white block, the sprite is recoloure dusing a shader
/// Author: Daryl Keogh
/// Time Spent: 20 minutes
/// Date: 22/03/2017
/// </summary>
class Paint
{
public:
	Paint(std::string color, thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder);

	void update();

	void render(sf::RenderWindow& window);

	void setupAnimation();

	void animate();

	void setTexture(sf::Sprite& sprite, sf::Texture& texture, sf::IntRect textRect = sf::IntRect(0,0, 112, 112));
	void setPos(float x, float y);
	void setPos(sf::Vector2f pos);
	void setNextPos(float x, float y);
	void setNextPos(sf::Vector2f pos);
	void setColour(sf::Color color);
	void setNextAlpha(int val);
	void selected(bool aBool);
	void setAlpha(int val = 255);

	//Our when we get or lose focus we call the focus method which plays an animation depending on if we lost or gained focus
	void getFocus();
	void loseFocus();
	void focus(std::string string);

	//getters
	bool& isSelected();
	sf::Vector2f getPos();
	sf::Vector2f getNextPos();
	sf::Color getColour();
	int getPrice();
private:
	int m_nextAlpha; //the alpha our object should go to
	bool m_isSelected;
	bool m_playAnimation; //bool to hold if we play our animation or not
	float m_alpha; //the alpha our button will be at

	sf::Sprite m_bgSprite; //our bgSprite object
	sf::Sprite m_colorSprite; //our colour sprite
	sf::Color m_color; //the colour of our sprite sheet
	sf::Vector2f m_position; //current position of the color picker
	sf::Vector2f m_nextPos; //the position or colour should be positioned at
	sf::Shader m_shader; // our recolour shader


	 //this our holder for our animations
	thor::Animator<sf::Sprite, std::string> m_animator;
	//This is our animation in
	thor::FrameAnimation m_selectedAnimation;
	thor::FrameAnimation m_unselectedAnimation;
	sf::Clock m_clock;
	sf::Time m_timer;


	Label m_priceLabel;

	int const MOVE_SPEED = 5;
	int const ALPHA_CHANGE = 3;

	int const MIN_POS = 80;
	int const MAX_POS = 1200;
	int const MAX_ALPHA = 255;

	int m_paintPrice; //the pric eof the paint 
};