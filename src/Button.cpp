#include "Button.h"
#include <iostream>
#include "ScreenManager.h"

//constructor for button
Button::Button(sf::Vector2f pos, sf::String name) :
	Widget(),
	m_playAnimation(false),
	m_label(name, 50),
	m_hasFocus(false),
	m_currentPosition(640, pos.y),
	m_endPosition(m_currentPosition),
	m_buttonName(name),
	m_finalAlpha(100),
	m_currentAlpha(100)
{
}

//updates the button
void Button::update()
{
	//Moving our button (up or down)
	if (m_currentPosition.y != m_endPosition.y)
	{
		if (m_currentPosition.y >= m_endPosition.y)
		{
			m_currentPosition.y -= SCROLL_SPEED;
			if (m_currentPosition.y < m_endPosition.y)
				m_currentPosition.y = m_endPosition.y;
		}

		else if (m_currentPosition.y <= m_endPosition.y)
		{
			m_currentPosition.y += SCROLL_SPEED;
			if (m_currentPosition.y >= m_endPosition.y)
				m_currentPosition.y = m_endPosition.y;
		}

		m_sprite.setPosition(m_currentPosition); //set the position of button
		m_iconSprite.setPosition(m_iconSprite.getPosition().x, m_currentPosition.y); //set the position of our icon texture
		m_label.setGuiPos(m_currentPosition.x + 49, m_currentPosition.y - 17); //setting the position of the label
	}

	//Setting the alpha of our button
	if(m_currentAlpha != m_finalAlpha)
	{
		if (m_currentAlpha >= m_finalAlpha)
		{
			m_currentAlpha -= FADE_SPEED;
			if (m_currentAlpha <= m_finalAlpha)
				m_currentAlpha = m_finalAlpha;
		}

		else if (m_currentAlpha <= m_finalAlpha)
		{
			m_currentAlpha += FADE_SPEED;
			if (m_currentAlpha >= m_finalAlpha)
				m_currentAlpha = m_finalAlpha;
		}

		auto tempColor = m_sprite.getColor();
		tempColor.a = m_currentAlpha;

		//Set the alpha of our sprites and label
		m_sprite.setColor(tempColor);
		m_iconSprite.setColor(tempColor);
		m_label.setAlpha(m_currentAlpha);
	}


	//if our playAnimation bool is true then animate our button
	if (m_playAnimation)
	{
		animateButton();
	}
}
//renders the button 
void Button::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
	window.draw(m_iconSprite);
	m_label.render(window);
}
//method to change to different menus using buttons
void Button::changeGameState(GameState & current, GameState & previous)
{
	GameState temp = current;

	if (m_buttonName == "Race")
	{
		current = GameState::PreRace;
	}
	else if (m_buttonName == "Play" || m_buttonName == "Continue")
	{
		
		current = GameState::Play;
	}
	else if (m_buttonName == "Options")
	{
		current = GameState::Options;
	}
	else if (m_buttonName == "Help")
	{
		current = GameState::Help;
	}
	else if (m_buttonName == "Pause")
	{
		current = GameState::Pause;
	}
	else if (m_buttonName == "Garage")
	{
		current = GameState::Garage;
	}
	else if (m_buttonName == "Main Menu")
	{
		current = GameState::MainMenu;
	}
	else if (m_buttonName == "HighScore")
	{
		current = GameState::Highscore;
	}
	else if (m_buttonName == "Exit")
	{
		current = GameState::Exit;
	}

	previous = temp;
}

void  Button::handleInput(Xbox360Controller& controller)
{

}

void Button::setTexture(sf::Texture &texture) 
{
	m_sprite.setTexture(texture); 
	m_sprite.setTextureRect(m_defualtRect);
	m_sprite.setOrigin(m_defualtRect.width / 2.0f, m_defualtRect.height /2.0f);
	m_sprite.setPosition(m_currentPosition);

	setAnimation();
};
void Button::setIconTexture(sf::Texture &iconTexture) 
{ 
	m_iconSprite.setTexture(iconTexture);
	auto tempRect = m_iconSprite.getTextureRect();
	m_iconSprite.setOrigin(tempRect.width / 2.0f, tempRect.height / 2.0f);
	m_iconSprite.setPosition(m_currentPosition.x - m_defualtRect.width / 2.0f + 49, m_currentPosition.y);
};
void Button::setCurrentPosition(sf::Vector2f v1)
{
	m_currentPosition.x = v1.x;
	m_currentPosition.y = v1.y;
	m_sprite.setPosition(m_currentPosition);

	m_iconSprite.setPosition(m_currentPosition.x - m_defualtRect.width / 2.0f + 49, m_currentPosition.y);

	//Sets the labels position
	m_label.setGuiPos(m_currentPosition.x + 49, m_currentPosition.y - 17);
}

void Button::setFinalPosition(sf::Vector2f v1)
{
	m_endPosition = v1;
}

int Button::getNewAlpha(int newPercentage)
{
	double maxAlpha = 255.0f; //our max alpha values
	double percentage = newPercentage / 100.0; //gets us a decimal (0.0 - 1)
	int newAlpha = maxAlpha * percentage; //multiply our decimal by our max alpha value to get our new alpha value

	return newAlpha;
};
void Button::setAlpha(int alphaPerct)
{
	auto tempSpriteColor = m_sprite.getColor(); //gets the colour(alpha) of the button sprite
	
	tempSpriteColor.a = getNewAlpha(alphaPerct); //assign our colours alpha value to the newly calculated one

	m_sprite.setColor(tempSpriteColor);
	m_iconSprite.setColor(tempSpriteColor);
	//set label alpha
	m_label.setAlpha(tempSpriteColor.a);

	m_currentAlpha = tempSpriteColor.a;
	m_finalAlpha = m_currentAlpha;
}

void Button::setFinalAlpha(int alphaPerc)
{
	m_finalAlpha = getNewAlpha(alphaPerc);
}

void Button::setAnimation()
{
	sf::IntRect tempArray[8];

	//Creates our selected animation
	for (int i = 0; i < 8; i++)
	{
		auto tempRect = sf::IntRect(423 * i, 0, 423, 98);
		tempArray[i] = tempRect;
		m_selectedAnimation.addFrame(0.1f, tempRect);
	}

	//Creates our unselected animation
	for (int i = 7; i >= 0; i--)
	{
		auto tempRect = tempArray[i];
		m_unselectedAnimation.addFrame(0.1f, tempRect);
	}

	m_animator.addAnimation("unselected", m_unselectedAnimation, sf::seconds(0.3f));
	m_animator.addAnimation("selected", m_selectedAnimation, sf::seconds(0.3f));
}


void Button::getFocus() 
{
	focus("selected");
	m_hasFocus = true; 
}
void Button::loseFocus() 
{
	focus("unselected");
	m_hasFocus = false; 
}

//method to determine which animation to play
void Button::focus(sf::String string)
{
	m_animator.stopAnimation(); //stop any animation playing
	m_clock.restart(); //restart clock
	m_playAnimation = true;
	m_animator.playAnimation(string); //play the animation with the id of (string)
}

void Button::animateButton()
{
	m_timer = m_clock.restart(); //get our time gone since last restart
	m_animator.update(m_timer); //update our animation using our timer
	m_animator.animate(m_sprite); //animate our sprite

	if (m_animator.isPlayingAnimation() == false)
	{
		m_playAnimation = false;
		m_clock.restart(); //restart our clock
	}
}

void Button::setFont(sf::Font& font)
{
	//Sets the labels position
	m_label.setGuiPos(m_currentPosition.x + 49, m_currentPosition.y - 17);

	m_label.setFont(font);
}