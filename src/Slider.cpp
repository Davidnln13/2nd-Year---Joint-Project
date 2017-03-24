#include "Slider.h"
#include "Xbox360Controller.h"
#include <iostream>

//Description:	The slider is used as a visual indicator that the user can adjust the volume of an assigned sound to it.
//Date worked on: 08/03/17, 12/03/2017
//Authors: Daryl Keogh & Brian Leigh

//Default constructor
Slider::Slider(std::string name, sf::Vector2f pos) :
	m_firstSelected(false),
	m_playAnimation(false),
	m_drawIndicator(true),
	m_indicatorIndex(0),
	m_position(pos),
	m_name(name),
	m_currentVal(50),
	m_sliderAnimator(),
	m_label(name, 65),
	m_sliderLevel(0)
{
	for(int i = 0; i < 10; i ++)
		m_indicatorRectArray[i] = sf::IntRect(355 * i, 0, 355, 54);

	setupAnimation(); //set up our animations

	m_selectedShader.loadFromFile("./resources/Shaders/bounceShader.frag", sf::Shader::Fragment);
}

//Used to update the slider values
void Slider::update()
{
	if(m_firstSelected == false && m_name == "Fx Volume")
	{
		getFocus();
		m_firstSelected = true;
	}

	//Play our animation
	if(m_playAnimation)
		playAnimation();
}
//Used to give focus to the slider so that it can be interacted with
void Slider::getFocus()
{
	//if we get focus, restart our shader clock so it can be update
	m_shaderClock.restart();
	focus("selected");
}
//Used when the slider loses focus.
void Slider::loseFocus()
{
	focus("unselected");
}

//Animates our slider
void Slider::playAnimation()
{
	m_timer = m_clock.restart(); //get our time gone since last restart
	m_sliderAnimator.update(m_timer); //update our animation using our timer
	m_sliderAnimator.animate(m_sprite); //animate our sprite

	if (m_sliderAnimator.isPlayingAnimation() == false)
	{
		m_playAnimation = false;
		m_clock.restart(); //restart our clock
	}
}

void Slider::focus(std::string string)
{
	m_sliderAnimator.stopAnimation(); //stop any animation playing
	m_clock.restart(); //restart clock
	m_playAnimation = true;
	m_sliderAnimator.playAnimation(string); //play the animation with the id of (string)
}

//Used to draw the slider.
void Slider::render(sf::RenderWindow& window)
{
	//Setting our time parameter in our shader to the time gone since our shader clocks last restart
	m_selectedShader.setParameter("time", m_shaderClock.getElapsedTime().asSeconds());

	//draw our slider bg with the applied shader
	window.draw(m_sprite, &m_selectedShader);

	//If our bool is true we draw our indicator sprite
	if(m_drawIndicator)
		window.draw(m_positionSprite, &m_selectedShader);

	//Render our label
	m_label.render(window);

}

//Ste sup the animation of the slider
void Slider::setupAnimation()
{
	sf::IntRect tempArray[8]; //creating a temporary array 

	//Creating our selected animation
	for(int i = 0; i < 8; i++)
	{
		tempArray[i] = sf::IntRect(400 * i, 0, 400, 98);
		m_selectedAnimation.addFrame(0.1f, tempArray[i]);
	}

	//creating our unselected animation
	for (int i = 7; i >= 0; i--)
		m_unselectedAnimation.addFrame(0.1f, tempArray[i]);

	//Adding our frame animations to our animator
	m_sliderAnimator.addAnimation("unselected", m_unselectedAnimation, sf::seconds(0.3f));
	m_sliderAnimator.addAnimation("selected", m_selectedAnimation, sf::seconds(0.3f));
}


void Slider::handleInput(Xbox360Controller& controller)
{
	int tempVolume = m_currentVal; 

	//If we press left on the dpad or push left on the Leftthumbstick
	if(controller.getCurrent().DpadLeft && controller.getPrevious().DpadLeft == false
		|| controller.getCurrent().LeftThumbStickLeft && controller.getPrevious().LeftThumbStickLeft == false)
	{
		tempVolume -= VAL_CHANGE;
	}
	//If we press right on the dpad or push right on the Leftthumbstick
	else if (controller.getCurrent().DpadRight && controller.getPrevious().DpadRight == false
		|| controller.getCurrent().LeftThumbStickRight && controller.getPrevious().LeftThumbStickRight == false)
	{
		tempVolume += VAL_CHANGE;
	}

	//If our temp volume is not equal to our current volume 
	if (tempVolume != m_currentVal)
	{
		if (tempVolume > MAX_VAL)
			tempVolume = MAX_VAL;
		else if (tempVolume < MIN_VAL)
			tempVolume = MIN_VAL;

		m_currentVal = tempVolume; //set our current volume our temp volume

		setIndicator();
	}
}

//Increases the level of the slider so it shows the next part of the spritesheet
void Slider::increaseGarageIndicator()
{
	int currentLevel = m_sliderLevel;
	currentLevel++;

	if (currentLevel > 5)
		currentLevel = 5;

	if (currentLevel > 0)
		m_drawIndicator = true;

	m_sliderLevel = currentLevel;

	//set our sprite position
	m_positionSprite.setTextureRect(sf::IntRect((currentLevel - 1)* 357, 0, 357, 54));
}

//decrease the level of the slider so it shows the previous part of the spritesheet
void Slider::decreaseGarageIndicator()
{
	int currentLevel = m_sliderLevel;
	currentLevel--;
	 
	if (currentLevel <= 0)
	{
		currentLevel = 0;
		m_drawIndicator = false;
	}
	m_sliderLevel = currentLevel;

	if (currentLevel > 0)
	{
		//set our sprite position
		m_positionSprite.setTextureRect(sf::IntRect((currentLevel - 1) * 357, 0, 357, 54));
	}
}

//Sets the next rectangle to set on our indicator sprite
void Slider::setIndicator()
{
	int newIndex = m_currentVal / 10.0f; //get an index of (0-10)
	newIndex--;

	if(newIndex < 0)
	{
		m_drawIndicator = false;
	}
	else
	{
		m_indicatorIndex = newIndex;
		m_drawIndicator = true;
		m_positionSprite.setTextureRect(m_indicatorRectArray[m_indicatorIndex]);
	}

}

//Sets the textures of our sprite fo rour garage screen
void Slider::setGarageTexture(sf::Texture& sliderTexture, sf::Texture& sliderPosTexture, sf::Font& font)
{
	applyTexture(m_sprite, sliderTexture, sf::IntRect(0, 0, 400, 98));
	applyTexture(m_positionSprite, sliderPosTexture, sf::IntRect(0, 0, 357, 54));

	m_label.setFont(font);
	m_label.setGuiPos(m_position.x, m_position.y - 98);
	m_drawIndicator = false; //we dont draw our indicator when the player has no garage level
}

//Used for setting the texture of our sprites
void Slider::setTexture(sf::Texture& sliderTexture, sf::Texture& sliderPosTexture, sf::Font& font)
{
	applyTexture(m_sprite, sliderTexture, sf::IntRect(0, 0, 400, 98));
	applyTexture(m_positionSprite, sliderPosTexture, sf::IntRect(0, 0, 355, 54));

	m_label.setFont(font);
	m_label.setGuiPos(m_position.x, m_position.y - 98);

	setIndicator();
}

//Applys a texture and position and also sets the origin of the passed over sprite
void Slider::applyTexture(sf::Sprite& aSprite, sf::Texture& texture, sf::IntRect textureRect) const
{
	aSprite.setTexture(texture);
	aSprite.setTextureRect(textureRect);
	aSprite.setOrigin(textureRect.width / 2.0f, textureRect.height / 2.0f);
	aSprite.setPosition(m_position);
}

int& Slider::getLevel()
{
	return m_sliderLevel;
}

void Slider::setSliderLevel(int level)
{
	m_sliderLevel = level;
	m_positionSprite.setTextureRect(sf::IntRect((level - 1) * 357, 0, 357, 54));

	if (level == 0)
		m_drawIndicator = false;
	else
		m_drawIndicator = true;
}