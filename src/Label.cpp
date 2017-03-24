#include "Label.h"

Label::Label(sf::String string, int textSize )
{
	m_string = string;
	std::transform(m_string.begin(), m_string.end(), m_string.begin(), ::toupper);
	m_txtSize = textSize;

}
Label::Label()
{

}
void Label::update()
{

}

void Label::render(sf::RenderWindow& window)
{
	window.draw(m_labelText);
}

/// <summary>
/// Author: Daryl Keogh
/// Description: Sets the string of the font, we can also pass in a colour which defualts to white if none is passed over
/// </summary>
/// <param name="string"></param>
/// <param name="aColor"></param>
void Label::setString(std::string string, sf::Color aColor)
{
	m_labelText.setString(string);
	m_labelText.setColor(aColor);
}

void Label::setAlpha(int newAlpha)
{
	auto currentColor = m_labelText.getColor();
	currentColor.a = newAlpha;
	m_labelText.setColor(currentColor);
}

sf::Vector2f Label::getGuiPos()
{
	return m_guiPos;
}

void Label::setString(sf::String string)
{
	m_labelText.setString(string);
}

void Label::setGuiPos(sf::Vector2f &guiPos)
{
	m_guiPos = guiPos;

	m_labelText.setPosition(m_guiPos);
}

void Label::setGuiPos(float x, float y)
{
	m_guiPos.x = x;
	m_guiPos.y = y;

	m_labelText.setPosition(m_guiPos);
}

/// <summary>
/// Resets the origin of the label back to its origin position (0,0)
/// </summary>
/// <param name="origin"></param>
/// <param name="position"></param>
void Label::resetOrigin()
{
	auto rect = m_labelText.getLocalBounds();
	m_labelText.setOrigin(rect.left, rect.top);
}

void Label::setTextSize(int size)
{
	m_labelText.setCharacterSize(size);
}

void Label::setFont(sf::Font& font)
{
	m_labelText.setFont(font);
	m_labelText.setCharacterSize(m_txtSize);
	m_labelText.setString(m_string);
	auto txtBounds = m_labelText.getGlobalBounds();
	m_labelText.setOrigin(txtBounds.width / 2.0f, txtBounds.height / 2.0f);
	m_labelText.setPosition(m_guiPos);
}

/// <summary>
/// Returns the global bounding box of the text
/// </summary>
/// <returns></returns>
sf::FloatRect Label::getGlobalRect()
{
	return m_labelText.getGlobalBounds();
}

sf::Vector2f Label::getPos()
{
	return m_guiPos;
}