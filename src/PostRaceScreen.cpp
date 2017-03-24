#include "PostRaceScreen.h"
#include "ScreenManager.h"

PostRaceScreen::PostRaceScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio) :
	//initialiser list
	Screen(audio),
	m_raceOver("RACE OVER", 50),
	m_totalTime("Total Time:", 50),
	m_bestLap("Best Lap:", 50),
	m_cashEarned("Cash Earned:", 50),
	m_congratulations("CONGRATULATIONS", 50),
	m_newHighscore("NEW HIGH SCORE", 50),
	m_enterName("Enter Your Name", 50),
	m_confirm("Press A to confirm", 50),
	m_canScroll(true),
	m_firstLetter("", sf::Vector2f(800, 500), m_postRaceBool),
	m_secondLetter("", sf::Vector2f(900, 500), m_postRaceBool),
	m_thirdLetter("", sf::Vector2f(1000, 500), m_postRaceBool),
	m_fourthLetter("", sf::Vector2f(1100, 500), m_postRaceBool),
	m_upFirst("", sf::Vector2f(800,400),m_postRaceBool),
	m_downFirst("", sf::Vector2f(800,600), m_postRaceBool),
	m_upSecond("", sf::Vector2f(900, 400), m_postRaceBool),
	m_downSecond("", sf::Vector2f(900, 600), m_postRaceBool),
	m_upThird("", sf::Vector2f(1000, 400), m_postRaceBool),
	m_downThird("", sf::Vector2f(1000, 600), m_postRaceBool),
	m_upFourth("", sf::Vector2f(1100,400), m_postRaceBool),
	m_downFourth("", sf::Vector2f(1100,600), m_postRaceBool),
	m_menuIndex(0)
{
	//holds all labels to condense code
	m_labels[0] = &m_raceOver;
	m_labels[1] = &m_totalTime;
	m_labels[2] = &m_bestLap;
	m_labels[3] = &m_cashEarned;
	m_labels[4] = &m_confirm;
	m_labels[5] = &m_congratulations;
	m_labels[6] = &m_newHighscore;
	m_labels[7] = &m_enterName;

	//holds all radio buttons
	m_radiobuttons[0] = &m_firstLetter;
	m_radiobuttons[1] = &m_secondLetter;
	m_radiobuttons[2] = &m_thirdLetter;
	m_radiobuttons[3] = &m_fourthLetter;
	m_radiobuttons[4] = &m_upFirst;
	m_radiobuttons[5] = &m_downFirst;
	m_radiobuttons[6] = &m_upSecond;
	m_radiobuttons[7] = &m_downSecond;
	m_radiobuttons[8] = &m_upThird;
	m_radiobuttons[9] = &m_downThird;
	m_radiobuttons[10] = &m_upFourth;
	m_radiobuttons[11] = &m_downFourth;
	
	//sets background image
	m_bgSprite.setTexture(resourceHolder["mainMenuBg"]);
	//sets all labels fonts to the same
	for (int i = 0; i < 8; i++)
	{
		m_labels[i]->setFont(fontHolder["font"]);
	}
	//sets the different labels positions
	m_labels[0]->setGuiPos(640, 0);
	m_labels[1]->setGuiPos(250, 100);
	m_labels[2]->setGuiPos(250, 200);
	m_labels[3]->setGuiPos(250, 300);
	m_labels[4]->setGuiPos(300, 500);
	m_labels[5]->setGuiPos(950, 100);
	m_labels[6]->setGuiPos(950, 200);
	m_labels[7]->setGuiPos(950, 300);

	//sets the textures for all the radio buttons 
	m_upFirst.setTexture(resourceHolder["radioSheet"], resourceHolder["up"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_downFirst.setTexture(resourceHolder["radioSheet"], resourceHolder["down"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_upSecond.setTexture(resourceHolder["radioSheet"], resourceHolder["up"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_downSecond.setTexture(resourceHolder["radioSheet"], resourceHolder["down"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_upThird.setTexture(resourceHolder["radioSheet"], resourceHolder["up"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_downThird.setTexture(resourceHolder["radioSheet"], resourceHolder["down"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_upFourth.setTexture(resourceHolder["radioSheet"], resourceHolder["up"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_downFourth.setTexture(resourceHolder["radioSheet"], resourceHolder["down"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_firstLetter.setTexture(resourceHolder["radioSheet"], resourceHolder["letterSpriteSheet"], fontHolder["font"], sf::IntRect(-40, 0, 40, 48));
	m_secondLetter.setTexture(resourceHolder["radioSheet"], resourceHolder["letterSpriteSheet"], fontHolder["font"], sf::IntRect(-40, 0, 40, 48));
	m_thirdLetter.setTexture(resourceHolder["radioSheet"], resourceHolder["letterSpriteSheet"], fontHolder["font"], sf::IntRect(-40, 0, 40, 48));
	m_fourthLetter.setTexture(resourceHolder["radioSheet"], resourceHolder["letterSpriteSheet"], fontHolder["font"], sf::IntRect(-40, 0, 40, 48));
	//set our index to the menu index
	newIndex = m_menuIndex;
	
	//starting character array values
	m_nameInput[0] = 26;
	m_nameInput[1] = 26;
	m_nameInput[2] = 26;
	m_nameInput[3] = 26;
}

PostRaceScreen::~PostRaceScreen()
{

}

void PostRaceScreen::update(GameState& current, GameState& previous)
{
	if (current == GameState::PostRace)
	{
		//update radio buttons
		for (auto widget : m_radiobuttons)
			widget->update();
		//initialises focus on the first radio buttons
		if (once == false)
		{
			m_radiobuttons[m_menuIndex]->getFocus();
			m_radiobuttons[4]->getFocus();
			m_radiobuttons[5]->getFocus();
			system("CLS");
			once = true;
		}
		//used to flip the letters when it goes out of range
		for (int i = 0; i < 3; i++)
		{
			if (m_nameInput[i] == -1)
			{
				m_nameInput[i] = 26;
			}
			if (m_nameInput[i] > 26)
			{
				m_nameInput[i] = 0;
			}
		}
		//puts timer on scrolling
		if (m_canScroll == false)
		{
			//Checking if we can scroll again
			float timeGone = m_scrollClock.getElapsedTime().asSeconds();
			if (timeGone > 0.35f)
				m_canScroll = true;

		}
		
	}
}

void PostRaceScreen::render(sf::RenderWindow& window, GameState& current, GameState& previous)
{
	if (current == GameState::PostRace && previous == GameState::Play)
	{ 
		window.draw(m_bgSprite);
		//only draw the congrats new high score if it is a new highscore
		if (isHighscore == true)
		{
			//draw all labels and radiobuttons
			for (auto* l : m_labels)
				l->render(window);
			for (auto widget : m_radiobuttons)
				widget->render(window);
		}
		else
		{	//if its not a highscore only draw the labels not relating to highscore
			for (int i = 0; i < 5; i++)
			{
				m_labels[i]->render(window);
			}
		}
		
	
	}
}

void PostRaceScreen::handleInput(Xbox360Controller& controller, GameState& current, GameState& previous)
{
	if (current == GameState::PostRace && previous == GameState::Play && m_canScroll)
	{
		
		//used for menu selection
		newIndex = m_menuIndex;
		//handle input for all radiobuttons
		m_radiobuttons[m_menuIndex]->handleInput(controller);
		//b to go back
		if (controller.getCurrent().B && controller.getPrevious().B == false)
		{
			auto tempState = current;
			current = previous;
			previous = tempState;
			m_audioP->m_soundArray[0].play();
		}
		//down changes letter in button
		if (controller.getCurrent().DpadDown && controller.getPrevious().DpadDown == false
			|| controller.getCurrent().LeftThumbStickDown && controller.getPrevious().LeftThumbStickDown == false)
		{
			m_audioP->m_soundArray[7].play();
			//if we are on the first button and press down change the texture rect to the next section on the sprite sheet
			if (newIndex == 0)
			{
				m_nameInput[0] += 1;
				auto rect = m_firstLetter.getTextureRect();
				m_firstLetter.setTextureRectLetters(sf::IntRect(rect.left + 40, 0, 40, 48));
				m_radiobuttons[0] = &m_firstLetter;
				//used to flip the letters when it goes out of range
				for (int i = 0; i < 4; i++)
				{
					if (m_nameInput[i] == -1)
					{
						m_nameInput[i] = 26;
					}
					if (m_nameInput[i] > 26)
					{
						m_nameInput[i] = 0;
					}
				}
			}
			if (newIndex == 1)
			{
				m_nameInput[1] += 1;
				auto rect = m_secondLetter.getTextureRect();
				m_secondLetter.setTextureRectLetters(sf::IntRect(rect.left + 40, 0, 40, 48));
				m_radiobuttons[1] = &m_secondLetter;
				//used to flip the letters when it goes out of range
				for (int i = 0; i < 4; i++)
				{
					if (m_nameInput[i] == -1)
					{
						m_nameInput[i] = 26;
					}
					if (m_nameInput[i] > 26)
					{
						m_nameInput[i] = 0;
					}
				}
			}
			if (newIndex == 2)
			{
				m_nameInput[2] += 1;
				auto rect = m_thirdLetter.getTextureRect();
				m_thirdLetter.setTextureRectLetters(sf::IntRect(rect.left + 40, 0, 40, 48));
				m_radiobuttons[2] = &m_thirdLetter;
				//used to flip the letters when it goes out of range
				for (int i = 0; i < 4; i++)
				{
					if (m_nameInput[i] == -1)
					{
						m_nameInput[i] = 26;
					}
					if (m_nameInput[i] > 26)
					{
						m_nameInput[i] = 0;
					}
				}
			}
			if (newIndex == 3)
			{
				m_nameInput[3] += 1;
				auto rect = m_fourthLetter.getTextureRect();
				m_fourthLetter.setTextureRectLetters(sf::IntRect(rect.left + 40, 0, 40, 48));
				m_radiobuttons[3] = &m_fourthLetter;
				//used to flip the letters when it goes out of range
				for (int i = 0; i < 4; i++)
				{
					if (m_nameInput[i] == -1)
					{
						m_nameInput[i] = 26;
					}
					if (m_nameInput[i] > 26)
					{
						m_nameInput[i] = 0;
					}
				}
			}
		}
		//up changes letter in button
		if (controller.getCurrent().DpadUp && controller.getPrevious().DpadUp == false
			|| controller.getCurrent().LeftThumbStickUp && controller.getPrevious().LeftThumbStickUp == false)
		{
			m_audioP->m_soundArray[7].play();
			if (newIndex == 0)
			{
				m_nameInput[0] -= 1;
				auto rect = m_firstLetter.getTextureRect();
				m_firstLetter.setTextureRectLetters(sf::IntRect(rect.left - 40, 0, 40, 48));
				m_radiobuttons[0] = &m_firstLetter;
				//used to flip the letters when it goes out of range
				for (int i = 0; i < 4; i++)
				{
					if (m_nameInput[i] == -1)
					{
						m_nameInput[i] = 26;
					}
					if (m_nameInput[i] > 26)
					{
						m_nameInput[i] = 0;
					}
				}
			}
			if (newIndex == 1)
			{
				m_nameInput[1] -= 1;
				auto rect = m_secondLetter.getTextureRect();
				m_secondLetter.setTextureRectLetters(sf::IntRect(rect.left - 40, 0, 40, 48));
				m_radiobuttons[1] = &m_secondLetter;
				//used to flip the letters when it goes out of range
				for (int i = 0; i < 4; i++)
				{
					if (m_nameInput[i] == -1)
					{
						m_nameInput[i] = 26;
					}
					if (m_nameInput[i] > 26)
					{
						m_nameInput[i] = 0;
					}
				}
			}
			if (newIndex == 2)
			{
				m_nameInput[2] -= 1;
				auto rect = m_thirdLetter.getTextureRect();
				m_thirdLetter.setTextureRectLetters(sf::IntRect(rect.left - 40, 0, 40, 48));
				m_radiobuttons[2] = &m_thirdLetter;
				//used to flip the letters when it goes out of range
				for (int i = 0; i < 4; i++)
				{
					if (m_nameInput[i] == -1)
					{
						m_nameInput[i] = 26;
					}
					if (m_nameInput[i] > 26)
					{
						m_nameInput[i] = 0;
					}
				}
			}
			if (newIndex == 3)
			{
				m_nameInput[3] -= 1;
				auto rect = m_fourthLetter.getTextureRect();
				m_fourthLetter.setTextureRectLetters(sf::IntRect(rect.left - 40, 0, 40, 48));
				m_radiobuttons[3] = &m_fourthLetter;
				//used to flip the letters when it goes out of range
				for (int i = 0; i < 4; i++)
				{
					if (m_nameInput[i] == -1)
					{
						m_nameInput[i] = 26;
					}
					if (m_nameInput[i] > 26)
					{
						m_nameInput[i] = 0;
					}
				}
			}
		}
		//left and right to switch to different button
		if (controller.getCurrent().DpadRight && controller.getPrevious().DpadRight == false || controller.getCurrent().LeftThumbStickRight && controller.getPrevious().LeftThumbStickRight == false)
		{
			m_audioP->m_soundArray[7].play();
			m_canScroll = false;
			newIndex++;
		}
		if (controller.getCurrent().DpadLeft && controller.getPrevious().DpadLeft == false || controller.getCurrent().LeftThumbStickLeft && controller.getPrevious().LeftThumbStickLeft== false)
		{
			m_audioP->m_soundArray[7].play();
			m_canScroll = false;
			newIndex--;
		}
		//a brings us to main menu and confirms the name 
		if (controller.getCurrent().A && controller.getPrevious().A == false)
		{
			m_audioP->m_soundArray[0].play();
			//comment out these lines
			auto tempState = current;
			current = GameState::MainMenu;
			previous = tempState;
			//and uncomment these lines to test name input 
			m_name = " " + m_alphabet[m_nameInput[0]] + "" + m_alphabet[m_nameInput[1]] + "" + m_alphabet[m_nameInput[2]] + "" + m_alphabet[m_nameInput[3]];
			 
		}
		//if our index's arnt equal then change our index to in the array 
		//also animate the top and bottom buttons
		if (newIndex != m_menuIndex)
		{
			//makes sure the numbers are within the range we want them 
			if (newIndex == 4)
				newIndex = 0;
			if (newIndex == -1)
				newIndex = 3;

		m_radiobuttons[m_menuIndex]->loseFocus();
		m_menuIndex = newIndex; //assign our new index to our menu index
		m_radiobuttons[m_menuIndex]->getFocus();
		animateSideButtons();
		}
		if (m_canScroll == false)
		{
			m_scrollClock.restart();
		}
		m_handledInput = true; //sets our bool to true so we can stop handling input on the screen
	}
	else
		m_handledInput = false;
}

void PostRaceScreen::animateSideButtons()
{
	if (m_menuIndex == 0)
	{
		//animate the button above and below us
		m_radiobuttons[4]->getFocus();
		m_radiobuttons[5]->getFocus();
		//also stop animating the previous selected buttons
		m_radiobuttons[m_x]->loseFocus();
		m_radiobuttons[m_y]->loseFocus();
		m_radiobuttons[m_z]->loseFocus();
		//these are the new previous selected buttons
		m_x = 0;
		m_y = 4;
		m_z = 5;
	}
	if (m_menuIndex == 1)
	{
		if (checkOnce == false)
		{
			m_x = 0;
			m_y = 4;
			m_z = 5;
			checkOnce = true;
		}
		 
		m_radiobuttons[6]->getFocus();
		m_radiobuttons[7]->getFocus();
		 
		m_radiobuttons[m_x]->loseFocus();
		m_radiobuttons[m_y]->loseFocus();
		m_radiobuttons[m_z]->loseFocus();
		
		m_x = 1;
		m_y = 6;
		m_z = 7;
	}
	if (m_menuIndex == 2)
	{
		m_radiobuttons[8]->getFocus();
		m_radiobuttons[9]->getFocus();
		 
		m_radiobuttons[m_x]->loseFocus();
		m_radiobuttons[m_y]->loseFocus();
		m_radiobuttons[m_z]->loseFocus();
 
		m_x = 2;
		m_y = 8;
		m_z = 9;
	}
	if (m_menuIndex == 3)
	{
		if (checkOnce == false)
		{
			m_x = 0;
			m_y = 4;
			m_z = 5;
			checkOnce = true;
		}


		m_radiobuttons[10]->getFocus();
		m_radiobuttons[11]->getFocus();

		m_radiobuttons[m_x]->loseFocus();
		m_radiobuttons[m_y]->loseFocus();
		m_radiobuttons[m_z]->loseFocus();

		m_x = 3;
		m_y = 10;
		m_z = 11;
	}
}