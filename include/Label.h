#pragma once
#include "SFML\Graphics.hpp"
#include <algorithm>


/// <summary>
/// Label Class for handling all of the labels
/// Authors: Eoghan, David.
/// </summary>

//class for the labels used in our game
class Label
{
public:
	Label(sf::String string, int textSize = 25);
	Label();
	void update();
	void render(sf::RenderWindow& window);

	//setters
	void setGuiPos(sf::Vector2f &guiPos);
	void setGuiPos(float x, float y);
	void setAlpha(int newAlpha);
	void setFont(sf::Font& font);
	void setString(std::string string, sf::Color aColor = sf::Color::White);
	void resetOrigin();
	void setTextSize(int size);

	//Getters
	sf::Vector2f getPos();
	sf::Vector2f getGuiPos();
	sf::FloatRect getGlobalRect();
	void setString(sf::String string);
private:
	sf::Vector2f m_position;
	std::string m_string;
	int m_txtSize;
	sf::Text m_labelText;
	sf::IntRect m_guiRect; //GUI Rectangle to place the label around the rectangle
	sf::Vector2f m_guiPos; //Position of the gui to place the label

	//the offset the label will be set to from the button
	const int XOFFSET = 98;

};