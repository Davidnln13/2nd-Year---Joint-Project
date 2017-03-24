#include "HelpScreen.h"
#include "ScreenManager.h"

//constructor for help sets each of the 3 sprites and the label
HelpScreen::HelpScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio) :
	Screen(audio),
	m_backLabel("Back", 50)
{
	m_backgroundSprite.setTexture(resourceHolder["mainMenuBg"]);
	m_backgroundSprite.setPosition(0, 0);

	m_controllerSprite.setTexture(resourceHolder["controller"]);
	m_controllerSprite.setPosition(0, 0);
	//b button
	m_bSprite.setTexture(resourceHolder["Bbutton"]);
	m_bSprite.setPosition(1120, 660);
	m_bSprite.setScale(0.023f, 0.023f);

	m_backLabel.setFont(fontHolder["font"]);
	m_backLabel.setGuiPos(sf::Vector2f(1220, 665));
	
}

HelpScreen::~HelpScreen()
{

}

void HelpScreen::update(GameState& current, GameState& previous)
{

}
//only render when gamestate is help 
void HelpScreen::render(sf::RenderWindow& window, GameState& current, GameState& previous)
{
	if (current == GameState::Help)
	{
		window.draw(m_backgroundSprite);
		window.draw(m_bSprite);
		m_backLabel.render(window);
		window.draw(m_controllerSprite);
	}
	
}
//handle input only when gamestate is help
void HelpScreen::handleInput(Xbox360Controller& controller, GameState& current, GameState& previous)
{
	if (current == GameState::Help)
	{
		if (controller.getCurrent().B && controller.getPrevious().B == false)
		{
			m_audioP->m_soundArray[0].play();
			auto tempState = current;
			current = previous;
			previous = tempState;
		}

		m_handledInput = true; //sets our bool to true so we can stop handling input on the screen
	}
	else
		m_handledInput = false;
}