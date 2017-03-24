#include "PauseScreen.h"
#include "ScreenManager.h"

PauseScreen::PauseScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio) :
	Screen(audio),
	m_btnIndex(0),
	m_continueBtn(sf::Vector2f(640, 120), "Continue"),
	m_helpBtn(sf::Vector2f(640, 280), "Help"),
	m_optionsBtn(sf::Vector2f(640, 440), "Options"),
	m_menuBtn(sf::Vector2f(640, 600), "Main Menu")
{
	//adding our buttons to our button array
	m_btnArray[0] = &m_continueBtn;
	m_btnArray[1] = &m_helpBtn;
	m_btnArray[2] = &m_optionsBtn;
	m_btnArray[3] = &m_menuBtn;

	//Assigning our buttons textures and setting their text fonts
	for (auto& btn : m_btnArray)
	{
		btn->setTexture(resourceHolder["buttonSheet"]);
		btn->setFont(fontHolder["font"]);
	}

	//Assigning icons to each of our buttons
	m_continueBtn.setIconTexture(resourceHolder["raceIcon"]);
	m_helpBtn.setIconTexture(resourceHolder["helpIcon"]);
	m_optionsBtn.setIconTexture(resourceHolder["settingsIcon"]);
	m_menuBtn.setIconTexture(resourceHolder["menuIcon"]);

	//Creates our render texture the size of our window
	m_rTexture.create(1280, 720);
	m_sprite.setTexture(m_rTexture.getTexture()); //set our sprite the texture of our renderTexture
}

PauseScreen::~PauseScreen()
{

}

void PauseScreen::update(GameState& current, GameState& previous)
{
	if (current == Pause)
	{
		if(!m_firstFocused)
		{
			m_continueBtn.getFocus();
			m_firstFocused = true;
		}


		//updates our buttons
		for (auto& btn : m_btnArray)
			btn->update();
	}
}

void PauseScreen::render(sf::RenderWindow& window, GameState& current, GameState& previous)
{
	if(current == Pause)
	{
		m_rTexture.clear(sf::Color(0, 0, 0, 175));//clear the texture with faded black
		m_rTexture.display(); //update our texture

		window.draw(m_trackSprite);

		window.draw(m_sprite); //draw our black texture

		//renders our buttons
		for (auto& btn : m_btnArray)
			btn->render(window);
	}
}
void PauseScreen::handleInput(Xbox360Controller& controller, GameState& current, GameState& previous)
{
	if (current == Pause)
	{
		int newIndex = m_btnIndex;

		//If the use rpresses the A button
		if (controller.getCurrent().A && controller.getPrevious().A == false)
		{
			m_btnArray[m_btnIndex]->changeGameState(current, previous); //invoke our clicked button method
			m_audioP->m_soundArray[0].play();
		}

		//if the player has pressed the B button
		if (controller.getCurrent().B && controller.getPrevious().B == false
			|| controller.getCurrent().Start && controller.getPrevious().Start == false)
		{
			m_audioP->m_soundArray[0].play();
			auto tempState = current; //assign our current state to a tempState
			current = previous; //make our current state our previous state
			previous = tempState; //make our previous state the tempstate (pause)
		}

		//If we navigate down/up through the buttons using the dpad or left thumbstick
		if (controller.getCurrent().DpadDown && controller.getPrevious().DpadDown == false
			|| controller.getCurrent().LeftThumbStickDown && controller.getPrevious().LeftThumbStickDown == false)
		{
			m_audioP->m_soundArray[7].play();
			//decrease our index
			newIndex++;
		}
		if (controller.getCurrent().DpadUp && controller.getPrevious().DpadUp == false
			|| controller.getCurrent().LeftThumbStickUp && controller.getPrevious().LeftThumbStickUp == false)
		{
			m_audioP->m_soundArray[7].play();
			//decrease our index
			newIndex--;
		}

		//If we have selected a new btn on the menu
		if (newIndex != m_btnIndex)
		{
			if (newIndex == 4) //if our new index has gone past 3(max size of our array)
				newIndex = 0;
			if (newIndex == -1)
				newIndex = 3;

			m_btnArray[m_btnIndex]->loseFocus(); //loseFocus on the previous selected button
			m_btnIndex = newIndex; //assign our new index to our menu index
			m_btnArray[m_btnIndex]->getFocus(); //get focus on our newly selected button
		}

		m_handledInput = true;
	}
	else
		m_handledInput = false;
}

void PauseScreen::setTrackTexture(const sf::Texture* texture)
{
	m_trackSprite.setTexture(*texture);
	m_trackSprite.setOrigin(960, 960);
	m_trackSprite.setPosition(640, 360);
}
