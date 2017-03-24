#pragma once
#include "SFML\Graphics.hpp"
#include "Thor\Animations.hpp"
#include "Label.h"
#include <iostream>

//forward reference to our controller
class Xbox360Controller;

/// <summary>
/// Author: Daryl Keogh
/// Date: 13/03/2017
/// Description: The widget class serves as a base class for our gui objects such as sliders, radio buttons, menu buttons.
/// Time Spent: 10 minutes
/// </summary>
class Widget
{
public:
	Widget();
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void handleInput(Xbox360Controller& controller) = 0;
	virtual void getFocus() = 0;
	
	virtual void loseFocus() = 0;
	
};