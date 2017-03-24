#include "Screen.h"
#include "ScreenManager.h"

/// <summary>
/// Our base class constructor
/// </summary>
Screen::Screen(Audio& audio) :
	m_audioP(&audio)
{

}

Screen::Screen()
{

}
/// <summary>
/// our base class destructor
/// </summary>
Screen::~Screen()
{

}

/// <summary>
/// Our pure virtual update method
/// this method needs no code as there is no need for it
/// </summary>
void Screen::update(GameState& current, GameState& previous)
{

}
/// <summary>
/// this pure virtual render method needs no body
/// </summary>
/// <param name="window"></param>
void Screen::render(sf::RenderWindow& window, GameState& current, GameState& previous)
{

}
void Screen::handleInput(Xbox360Controller& controller, GameState& current, GameState& previous)
{

}
