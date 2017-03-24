#include "Paint.h"

Paint::Paint(std::string color, thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder) :
	m_isSelected(false),
	m_playAnimation(false),
	m_priceLabel("PRICE: ", 50)
{
	setTexture(m_bgSprite, resourceHolder["colorSheet"]);
	setTexture(m_colorSprite, resourceHolder["basicPaint"]);
	m_priceLabel.setFont(fontHolder["font"]); //set the font of our label

	//load our fragment shader
	m_shader.loadFromFile("./resources/Shaders/colorChangeShader.frag", sf::Shader::Fragment);

	//sets the colour of the colour sprite depending on the name of the paint object
	if (color == "white")
	{
		setColour(sf::Color(235, 235, 235, 255));
		m_paintPrice = 5;
	}
	else if (color == "blue")
	{
		setColour(sf::Color(102, 255, 255, 255));
		m_paintPrice = 15;
	}
		
	else if (color == "red")
	{
		setColour(sf::Color(200, 0, 0, 255));
		m_paintPrice = 15;
	}
		
	else if (color == "orange")
	{
		setColour(sf::Color(255, 100, 0, 255));
		m_paintPrice = 10;
	}
		
	else if (color == "purple")
	{
		setColour(sf::Color(102, 0, 102, 255));
		m_paintPrice = 20;
	}
		
		
	else if (color == "black")
	{
		setColour(sf::Color(40, 40, 40, 255));
		m_paintPrice = 10;
	}

	m_priceLabel.setString("PRICE $" + std::to_string(m_paintPrice));

	//setup our animation
	setupAnimation();
}

void Paint::update()
{
	//if our position is not equal to the next position we should be at, then adjust the paint object's position
	if (m_position != m_nextPos)
	{
		if (m_position.x > m_nextPos.x)
		{
			m_position.x -= MOVE_SPEED;
			if (m_position.x < m_nextPos.x)
				m_position.x = m_nextPos.x;
			 //if we have gone beyond our left hand bounds then set our position to the right hand side of the screen
			if (m_position == m_nextPos && m_position.x <= -480)
			{
				m_position.x = 1200;
				m_nextPos.x = 1200;
			}
		}
		else if (m_position.x < m_nextPos.x)
		{
			m_position.x += MOVE_SPEED;
			if (m_position.x > m_nextPos.x)
				m_position.x = m_nextPos.x;

			//if we have gone beyond our right hand bounds then set our position to the left hand side of the screen
			if (m_position == m_nextPos && m_position.x >= 1480)
			{
				m_position.x = -200;
				m_nextPos.x = -200;
			}
		}

		//sets the position of our sprites and our label
		m_bgSprite.setPosition(m_position);
		m_colorSprite.setPosition(m_position);
		m_priceLabel.setGuiPos(m_position.x - 35, m_position.y + 75);
	}
	//changing our alpha to our new alpha value
	if (m_alpha != m_nextAlpha)
	{
		if (m_alpha > m_nextAlpha)
		{
			m_alpha -= ALPHA_CHANGE;
			if (m_alpha < m_nextAlpha)
				m_alpha = m_nextAlpha;
		}
		else
		{
			m_alpha += ALPHA_CHANGE;
			if (m_alpha > m_nextAlpha)
				m_alpha = m_nextAlpha;
		}

		auto bgColor = m_bgSprite.getColor();
		bgColor.a = m_alpha;
		m_color.a = m_alpha;
		m_bgSprite.setColor(bgColor);
		m_colorSprite.setColor(bgColor);
		setColour(m_color); //set the colour of our shader
		m_priceLabel.setAlpha(m_alpha);
	}

	//if our playAnimation bool is true then animate our paint select/unselect
	if (m_playAnimation)
	{
		animate();
	}
}

void Paint::render(sf::RenderWindow& window)
{
	window.draw(m_bgSprite);
	//draw our color sprite using the re-colour shader
	window.draw(m_colorSprite, &m_shader);

	m_priceLabel.render(window);
}

//Animates our spritesheet
void Paint::animate()
{
	m_timer = m_clock.restart(); //get our time gone since last restart
	m_animator.update(m_timer); //update our animation using our timer
	m_animator.animate(m_bgSprite); //animate our sprite

	if (m_animator.isPlayingAnimation() == false)
	{
		m_playAnimation = false;
		m_clock.restart(); //restart our clock
	}
}

//setsup our selected and unselected animations
void Paint::setupAnimation()
{
	sf::IntRect tempArray[8];

	//Creates our selected animation
	for (int i = 0; i < 8; i++)
	{
		auto tempRect = sf::IntRect(112 * i, 0, 112, 112);
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

void Paint::setNextAlpha(int val)
{
	double alphaPercentage = val / 100.0;
	int newAlpha = MAX_ALPHA * alphaPercentage;

	m_nextAlpha = newAlpha;
}

void Paint::selected(bool aBool)
{
	m_isSelected = aBool;
}

bool& Paint::isSelected()
{
	return m_isSelected;
}

void Paint::setNextPos(float x, float y)
{
	m_nextPos.x = x;
	m_nextPos.y = y;
}

void Paint::setNextPos(sf::Vector2f pos)
{
	m_nextPos = pos;
}

//Sets the parameters of our shader so we can recolour the paint
//We us ethe RBG & A value sof the sf::Color parameter passed over to it
void Paint::setColour(sf::Color color)
{
	//Set our color variable to the passed over color
	m_color = color;

	//Reset our shader variables
	m_shader.setParameter("newR", 0);
	m_shader.setParameter("newG", 0);
	m_shader.setParameter("newB", 0);
	m_shader.setParameter("newA", 0);

	//Calculate our new colours
	float newR = color.r / 255.0;
	float newG = color.g / 255.0;
	float newB = color.b / 255.0;
	float newA = color.a / 255.0;

	//Set our shade runiform variables to our new calculated colour
	m_shader.setParameter("newR", newR);
	m_shader.setParameter("newG", newG);
	m_shader.setParameter("newB", newB);
	m_shader.setParameter("newA", newA);
}


void Paint::getFocus()
{
	focus("selected");
}

void Paint::loseFocus()
{
	focus("unselected"); //play our unselected animation
}

sf::Vector2f Paint::getPos()
{
	return m_position;
}

sf::Vector2f Paint::getNextPos()
{
	return m_nextPos;
}

sf::Color Paint::getColour()
{
	return m_color;
}

void Paint::focus(std::string string)
{
	m_animator.stopAnimation(); //stop any animation playing
	m_clock.restart(); //restart clock
	m_playAnimation = true;
	m_animator.playAnimation(string); //play the animation with the id of (string)
}

void Paint::setPos(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
	m_nextPos = m_position;
	m_bgSprite.setPosition(x, y);
	m_colorSprite.setPosition(x, y);
	m_priceLabel.setGuiPos(m_position.x - 35, m_position.y + 75);
}

void Paint::setPos(sf::Vector2f pos)
{
	m_position = pos;
	m_nextPos = pos;
	m_bgSprite.setPosition(pos);
	m_colorSprite.setPosition(pos);
	m_priceLabel.setGuiPos(m_position.x - 35, m_position.y + 75);
}

void Paint::setTexture(sf::Sprite& sprite, sf::Texture& texture, sf::IntRect textRect)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(textRect);
	sprite.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
}

int Paint::getPrice()
{
	return m_paintPrice;
}

void Paint::setAlpha(int val)
{
	auto bgColor = m_bgSprite.getColor();
	bgColor.a = val;
	m_color.a = val;
	m_bgSprite.setColor(bgColor);
	m_colorSprite.setColor(bgColor);
	m_priceLabel.setAlpha(val);
	setColour(m_color);
}