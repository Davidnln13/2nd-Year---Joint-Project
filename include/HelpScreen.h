#pragma once
#include "Screen.h"
#include "Label.h"

/// <summary>
/// Our Help screen will be used to display the button bindings on the controller
/// so that our users can easily use this screen if they are unfamilar with the controls.
/// Authors: Daryl Keogh 
/// </summary>
class HelpScreen : public Screen
{
public:
	HelpScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio);
	~HelpScreen();

	void update(GameState& current, GameState& previous) override;
	void render(sf::RenderWindow& window, GameState& current, GameState& previous) override;
	void handleInput(Xbox360Controller& controller, GameState& current, GameState& previous) override;

private:
	//sprites for controller background and b button
	sf::Texture m_texture;
	sf::Sprite m_backgroundSprite;	
	sf::Sprite m_controllerSprite;
	sf::Sprite m_bSprite;
	Label m_backLabel;
};