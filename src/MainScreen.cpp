#include "MainScreen.h"
#include "ScreenManager.h"
#include "Audio.h"

MainScreen::MainScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio) :
	Screen(audio),
	m_firstFocused(false),
	m_canScroll(true),
	m_playSong(true),
	m_btnIndex(2),
	m_raceBtn(sf::Vector2f(640, 80), "Race"),
	m_garageBtn(sf::Vector2f(640, 220), "Garage"),
	m_highscoreBtn(sf::Vector2f(640, 360), "HighScore"),
	m_helpBtn(sf::Vector2f(640, 500), "Help"),
	m_optionsBtn(sf::Vector2f(640, 640), "Options"),
	m_exitbtn(sf::Vector2f(640, -60), "Exit")
{
	//Setting up our bg
	m_sprite.setTexture(resourceHolder["mainMenuBg"]);
	m_sprite.setPosition(0, 0);
	
	

	//Adding our buttons to our button array
	m_btnArray[0] = &m_raceBtn;
	m_btnArray[1] = &m_garageBtn;
	m_btnArray[2] = &m_highscoreBtn;
	m_btnArray[3] = &m_helpBtn;
	m_btnArray[4] = &m_optionsBtn;
	m_btnArray[5] = &m_exitbtn;

	//setting the icons of the buttons
	m_raceBtn.setIconTexture(resourceHolder["raceIcon"]);
	m_garageBtn.setIconTexture(resourceHolder["garageIcon"]);
	m_highscoreBtn.setIconTexture(resourceHolder["menuIcon"]);
	m_helpBtn.setIconTexture(resourceHolder["helpIcon"]);
	m_optionsBtn.setIconTexture(resourceHolder["settingsIcon"]);
	m_exitbtn.setIconTexture(resourceHolder["exitIcon"]);

	//Loop through our buttons and set the texture and icon texture. 
	//then set the alpha depending on what the ndex is
	for (int i = 0; i < 6; i++)
	{
		m_btnArray[i]->setTexture(resourceHolder["buttonSheet"]);
		m_btnArray[i]->setFont(fontHolder["font"]);

		if (i == 0 || i == 4)
			m_btnArray[i]->setAlpha(10); //setting the alpha of the top and bottom buttons to 10 percent
		else if (i == 3 || i == 1)
			m_btnArray[i]->setAlpha(35); //setting the alpha of the buttons just above and below the centre to 35 percent
		else if (i == 5)
			m_btnArray[i]->setAlpha(0); //setting the alpha of the button offscreen to 0
		else
			m_btnArray[i]->setAlpha(); //setting the alpha of the button in the centr eof the screen to 100 percent
	}
}

MainScreen::~MainScreen()
{

}

void MainScreen::update(GameState& current, GameState& previous)
{	
	 
	if (current == GameState::MainMenu)
	{
		 
		//if we have no button focused, then focus on th ehighscores button
		if (!m_firstFocused)
		{
			m_highscoreBtn.getFocus();
			m_firstFocused = true;
		}


		for (auto& button : m_btnArray)
		{
			button->update() ;
		}

		//Checking if our buttons are in place so we can handle input again
		if (m_btnArray[m_btnIndex]->getCurrentPos().y == 360)
			m_canScroll = true;


		//If our menu has scrolled up or down then scroll our menu
		if (m_scrollDown || m_scrollUp)
		{
			scrollMenu();
		}
		
	}
}

void MainScreen::render(sf::RenderWindow& window, GameState& current, GameState& previous)
{
	if (current == GameState::MainMenu)
	{
		window.draw(m_sprite);
		for (auto& button : m_btnArray)
		{
			button->render(window);
		}
	}
}

void MainScreen::handleInput(Xbox360Controller& controller, GameState& current, GameState& previous)
{
	
	if (current == GameState::MainMenu && m_canScroll)
	{
		//give our temporary index our current index
		int tempIndex = m_btnIndex;
		bool buttonMoved = false;

		if (controller.getCurrent().A && controller.getPrevious().A == false)
		{
			
			m_btnArray[m_btnIndex]->changeGameState(current, previous);
			
			m_handledInput = true;
			m_audioP->m_soundArray[0].play();
		}


		if (controller.getCurrent().DpadDown && controller.getPrevious().DpadDown == false
			|| controller.getCurrent().LeftThumbStickDown && controller.getPrevious().LeftThumbStickDown == false)
		{
			//because we moved up on the menu, the menu has scrolled down
			m_scrollDown = true;
			buttonMoved = true;
			tempIndex++;
			m_audioP->m_soundArray[7].play();
			
		}
		 
		if (controller.getCurrent().DpadUp && controller.getPrevious().DpadUp == false
			|| controller.getCurrent().LeftThumbStickUp && controller.getPrevious().LeftThumbStickUp == false)
		{
			m_scrollUp = true;
			buttonMoved = true;
			tempIndex--;
			m_audioP->m_soundArray[7].play();
		}
		 
		//If a button has been moved (shifted up or Down)
		if (buttonMoved)
		{
			//loose focus on the current button
			m_btnArray[m_btnIndex]->loseFocus();

			//Check our bounds of our array
			if (tempIndex < 0)
				tempIndex = 5;
			else if (tempIndex > 5)
				tempIndex = 0;

			//Set our current btn array to the new index
			m_btnIndex = tempIndex;
			//get focus on the newly indexed button
			m_btnArray[m_btnIndex]->getFocus();
		}
	}
	else
		m_handledInput = false;
}

//Scrolls our menu up
void MainScreen::scrollMenu()
{
	//gives our index to a temporary index
	int index = m_btnIndex;

	for (int i = 0; i < 6; i++)
	{
		//if we are scrolling up
		if (m_scrollUp)
		{
			//If we are off screen and below the window// set our position to above our window 
			if (m_btnArray[i]->getFinalPos() == sf::Vector2f(640, 780))
			{
				m_btnArray[i]->setCurrentPosition(sf::Vector2f(640, -60));
				m_btnArray[i]->setFinalPosition(sf::Vector2f(640, -60));
			}
			//Add 140 pixels to the y of the button
			m_btnArray[i]->setFinalPosition(sf::Vector2f(m_btnArray[i]->getFinalPos().x, m_btnArray[i]->getFinalPos().y + 140));
			
		}
		//same as above but moving up
		if (m_scrollDown)
		{
			if (m_btnArray[i]->getFinalPos() == sf::Vector2f(640, -60))
			{
				m_btnArray[i]->setCurrentPosition(sf::Vector2f(640, 780));
				m_btnArray[i]->setFinalPosition(sf::Vector2f(640, 780));
			}
				
			m_btnArray[i]->setFinalPosition(sf::Vector2f(m_btnArray[i]->getFinalPos().x, m_btnArray[i]->getFinalPos().y - 140));
		}

		//Setting the alpha of each button depending on thei rposition on the screen
		if (m_btnArray[i]->getFinalPos() == sf::Vector2f(640, 80) || m_btnArray[i]->getFinalPos() == sf::Vector2f(640, 640))
			m_btnArray[i]->setFinalAlpha(10);
		else if (m_btnArray[i]->getFinalPos() == sf::Vector2f(640, 220) || m_btnArray[i]->getFinalPos() == sf::Vector2f(640, 500)) //set the alpha to 50 if we are just below/above the centre button
			m_btnArray[i]->setFinalAlpha(35);
		else if (m_btnArray[i]->getFinalPos() == sf::Vector2f(640, 360)) //set the alpha to 100 percent if we are centre on the screen
			m_btnArray[i]->setFinalAlpha(100);
		else
			m_btnArray[i]->setFinalAlpha(0); //set the alpha to 0 if we are off screen
	}

	//reset our bools
	m_scrollDown = false;
	m_scrollUp = false;
	m_canScroll = false;
}
