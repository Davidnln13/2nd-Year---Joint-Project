#include "RadioButton.h"
#include "Xbox360Controller.h"

//constructor for RadioButton
RadioButton::RadioButton(std::string name, sf::Vector2f pos) :
	m_checked(true),
	m_playAnimation(false),
	m_lastTickAnimation("check"),
	m_currentPos(pos),
	m_name(name),
	m_label(name, 55),
	m_isPreRace(false)
{
	setUpAnimation(); //setup our animation
	m_hasIcon = true;
	m_selectedShader.loadFromFile("./resources/Shaders/bounceShader.frag", sf::Shader::Fragment);
}
//overloaded constructor
RadioButton::RadioButton(std::string name, sf::Vector2f pos, bool preRace, bool hasIcon) :
	m_hasIcon(hasIcon),
	m_currentPos(pos),
	m_name(name),
	m_label(name, 55),
	m_isPreRace(preRace)
{
	setUpAnimation(); //setup our animation
	m_selectedShader.loadFromFile("./resources/Shaders/bounceShader.frag", sf::Shader::Fragment);
}
//updates the RadioButton
void RadioButton::update()
{
	//Play our tick animation
	if (m_playTick)
	{
		animateTick();
	}

	//Play our animation
	if(m_playAnimation)
	{
		playAnimation();
	}
}
bool RadioButton::isAnimationPlaying()
{
	return m_buttonAnimator.isPlayingAnimation();
}
//renders the RadioButton 
void RadioButton::render(sf::RenderWindow & window)
{
	//Setting our time parameter in our shader to the time gone since our shader clocks last restart
	m_selectedShader.setUniform("time", m_shaderClock.getElapsedTime().asSeconds());

	//draw our button sprite
	window.draw(m_sprite, &m_selectedShader);

	if(m_hasIcon)
		window.draw(m_iconSprite, &m_selectedShader);

	m_label.render(window);

}

void RadioButton::getFocus()
{
	m_shaderClock.restart();
	focus("selected");
}
void RadioButton::getFocusWithoutSelect()
{
	m_shaderClock.restart();
	focus("selected");
}

void RadioButton::loseFocus()
{
	focus("unselected");
}

void RadioButton::loseFocusWithoutSelect()
{
	focus("unselected");
}

void RadioButton::focus(std::string string)
{
	m_buttonAnimator.stopAnimation(); //stop any animation playing
	m_btnClock.restart(); //restart clock
	m_playAnimation = true;
	m_buttonAnimator.playAnimation(string); //play the animation with the id of (string)
}

void RadioButton::handleInput(Xbox360Controller& controller)
{
	if (controller.getCurrent().A && controller.getPrevious().A == false && m_isPreRace == false)
	{
		if(m_lastTickAnimation ==  "check")
			playTick("uncheck"); //if we have ticked this check box, play our untick animation
		else
			playTick("check"); //else play our tick animation
	}
}

void RadioButton::setTexture(sf::Texture& radioBtnTexture, sf::Texture& iconTexture, sf::Font& font, sf::IntRect aRect)
{
	applyTexture(m_sprite, radioBtnTexture, sf::IntRect(0, 0, 98, 98)); //pass over the first rectangle of our texture
	applyTexture(m_iconSprite, iconTexture, aRect); //pass over the final rectangle of our tick texture

	m_label.setFont(font);
	if (m_name == "Previous")
		m_label.setGuiPos(m_currentPos.x + 10, m_currentPos.y - 150);
	else if (m_name == "Next")
		m_label.setGuiPos(m_currentPos.x + 5, m_currentPos.y - 150);
}
//min and max of one
void RadioButton::setTextureRectCar(sf::IntRect aRect)
{
	if (aRect.left == 80)
	{
		aRect.left = 40;
	}
	if (aRect.left == 0)
	{
		aRect.left = 40;
	}
	m_iconSprite.setTextureRect(aRect);
}
//min and max of 1
void RadioButton::setTextureRectTrack(sf::IntRect aRect)
{
	if (aRect.left == 80)
	{
		aRect.left = 40;
	}
	if (aRect.left == 0)
	{
		aRect.left = 40;
	}
	m_iconSprite.setTextureRect(aRect);
}
//min of 3 max of 9
void RadioButton::setTextureRectLaps(sf::IntRect aRect)
{
	if (aRect.left == 400)
	{
		aRect.left = 40;
	}
	if (aRect.left == 0)
	{
		aRect.left = 360;
	}
	m_iconSprite.setTextureRect(aRect);
}
//min of 1 max of 9
void RadioButton::setTextureRectAi(sf::IntRect aRect)
{
	if (aRect.left == 240)
	{
		aRect.left = 40;
	}
	if (aRect.left == 0)
	{
		aRect.left = 200;
	}
	m_iconSprite.setTextureRect(aRect);
}
void RadioButton::setTextureRectLetters(sf::IntRect aRect)
{
	if (aRect.left == 1040)
	{
		aRect.left = -40;
	}
	if (aRect.left == -80)
	{
		aRect.left = 1000;
	}
	m_iconSprite.setTextureRect(aRect);
}

//sets our textures and sets the font of our label
void RadioButton::setTexture(sf::Texture& radioBtnTexture, sf::Texture& iconTexture, sf::Font& font)
{
	applyTexture(m_sprite, radioBtnTexture, sf::IntRect(0, 0, 98, 98)); //pass over the first rectangle of our texture
	applyTexture(m_iconSprite, iconTexture, sf::IntRect(306, 0, 51, 48)); //pass over the final rectangle of our tick texture

	m_label.setFont(font);

	if (m_name == "Fx Toggle")
		m_label.setGuiPos(m_currentPos.x + 196, m_currentPos.y - 17);
	else if (m_name == "Music Toggle")
		m_label.setGuiPos(m_currentPos.x + 246, m_currentPos.y - 17);

}

//Applies the texture to the passed over sprite and sets the origin and position
void RadioButton::applyTexture(sf::Sprite& aSprite, sf::Texture& texture, sf::IntRect textureRect) const
{
	aSprite.setTexture(texture);
	aSprite.setTextureRect(textureRect);
	auto tempRect = aSprite.getGlobalBounds();
	aSprite.setOrigin(tempRect.width / 2.0f, tempRect.height / 2.0f);
	aSprite.setPosition(m_currentPos);
}

//Plays our animation
void RadioButton::playAnimation()
{
	m_btnTimer = m_btnClock.restart(); //get our time gone since last restart
	m_buttonAnimator.update(m_btnTimer); //update our animation using our timer
	m_buttonAnimator.animate(m_sprite); //animate our sprite

	if (m_buttonAnimator.isPlayingAnimation() == false)
	{
		m_playAnimation = false;
		m_btnClock.restart(); //restart our clock
	}
}

//Plays our tick
void RadioButton::animateTick()
{
	m_tickTimer = m_tickClock.restart(); //get our time gone since last restart
	m_tickAnimator.update(m_tickTimer); //update our animation using our timer
	m_tickAnimator.animate(m_iconSprite); //animate our sprite

	if (m_tickAnimator.isPlayingAnimation() == false)
	{
		if (m_lastTickAnimation == "uncheck")
		{
			m_iconSprite.setTextureRect(sf::IntRect(0,0,0,0));
		}
		m_playTick = false;
		m_tickClock.restart(); //restart our clock
	}
}

//Plays our tick animation
void RadioButton::playTick(std::string string)
{
	m_lastTickAnimation = string;
	m_tickClock.restart(); //restart our clock
	m_tickAnimator.stopAnimation(); //stop any tick animations happening
	m_tickAnimator.playAnimation(string); // play our tick animation with the id of the passed over string
	m_playTick = true;
	animateTick();
}

//Sets up our animation
void RadioButton::setUpAnimation()
{
	sf::IntRect tempArray[8];
	sf::IntRect tempTickArray[7];

	//Settign up our selected animation
	for(int i = 0; i < 8; i++)
	{
		if (i < 7)
		{
			tempTickArray[i] = sf::IntRect(51 * i, 0, 51, 98); //getting each rectangle of our sprite
			m_checkAnimation.addFrame(0.1f, tempTickArray[i]);
		}
		tempArray[i] = sf::IntRect(98 * i,0,98,98);
		m_selectedAnimation.addFrame(0.1f, tempArray[i]); //add a frame to our selected animation
	}

	for(int i = 7; i >= 0; i--)
	{
		m_uncheckAnimation.addFrame(0.1f, tempTickArray[i - 1]);
		m_unselectedAnimation.addFrame(0.1f, tempArray[i]); //add a frame to our unselected animation
	}

	//Add the animations to our animator
	m_buttonAnimator.addAnimation("selected", m_selectedAnimation, sf::seconds(0.3f));
	m_buttonAnimator.addAnimation("unselected", m_unselectedAnimation, sf::seconds(0.3f));
	m_tickAnimator.addAnimation("check", m_checkAnimation, sf::seconds(0.15f));
	m_tickAnimator.addAnimation("uncheck", m_uncheckAnimation, sf::seconds(0.15f));
}