#include "PreRaceScreen.h"
#include "ScreenManager.h"
//initialises all radiobuttons labels and sets menu index to start at the top
PreRaceScreen::PreRaceScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio) :
	Screen(audio),
	m_canScroll(true),
	m_play(sf::Vector2f(200, 640), "Play"),
	//these bools are to make these radiobuttons different to normal radio buttons
	m_selectCarPrevious("Previous", sf::Vector2f(500, 200), preRaceBool),
	m_selectCarNext("Next", sf::Vector2f(800, 200), preRaceBool),
	m_selectTrackPrevious("", sf::Vector2f(500, 300), preRaceBool),
	m_selectTrackNext("", sf::Vector2f(800, 300), preRaceBool),
	m_selectLapsPrevious("", sf::Vector2f(500, 400), preRaceBool),
	m_selectLapsNext("", sf::Vector2f(800, 400), preRaceBool),
	m_selectAiAmountPrevious("", sf::Vector2f(500, 500), preRaceBool),
	m_selectAiAmountNext("", sf::Vector2f(800, 500), preRaceBool),
	m_carNum("", sf::Vector2f(650, 200), preRaceBool),
	m_trackNum("", sf::Vector2f(650, 300), preRaceBool),
	m_lapsNum("", sf::Vector2f(650, 400), preRaceBool),
	m_aiNum("", sf::Vector2f(650, 500), preRaceBool),
	m_label("Back", 50),
	m_selectCar("Select Car", 50),
	m_selectTrack("Select Track", 50),
	m_selectLaps("Select Laps", 50),
	m_selectAiNo("Select Enemies", 50),
	m_menuIndex(8)
{
	//sets the textures on the button
	m_play.setTexture(resourceHolder["buttonSheet"]);
	m_play.setFont(fontHolder["font"]);
	m_play.setIconTexture(resourceHolder["raceIcon"]);
	//setting up widget array
	
	//widget array holds all radio buttons and the button 
	m_widgets[0] = &m_selectCarPrevious;
	m_widgets[1] = &m_selectCarNext;
	m_widgets[2] = &m_selectTrackPrevious;
	m_widgets[3] = &m_selectTrackNext;
	m_widgets[4] = &m_selectLapsPrevious;
	m_widgets[5] = &m_selectLapsNext;
	m_widgets[6] = &m_selectAiAmountPrevious;
	m_widgets[7] = &m_selectAiAmountNext;
	m_widgets[8] = &m_carNum;
	m_widgets[9] = &m_trackNum;
	m_widgets[10] = &m_lapsNum;
	m_widgets[11] = &m_aiNum;
	m_widgets[12] = &m_play;

	 

	//b button
	m_bButtonSprite.setTexture(resourceHolder["Bbutton"]);
	m_bButtonSprite.setPosition(1120, 660);
	m_bButtonSprite.setScale(0.023f, 0.023f);
	m_bgSprite.setTexture(resourceHolder["mainMenuBg"]);
	//labels
	m_label.setFont(fontHolder["font"]);
	m_label.setGuiPos(sf::Vector2f(1220, 665));
	//labels to write the options on the screen
	m_selectCar.setFont(fontHolder["font"]);
	m_selectCar.setGuiPos(sf::Vector2f(175,185));

	m_selectTrack.setFont(fontHolder["font"]);
	m_selectTrack.setGuiPos(sf::Vector2f(195,285));

	m_selectLaps.setFont(fontHolder["font"]);
	m_selectLaps.setGuiPos(sf::Vector2f(175,385));

	m_selectAiNo.setFont(fontHolder["font"]);
	m_selectAiNo.setGuiPos(sf::Vector2f(210,485));

	//sets the textures for the radio buttons gives them an initial spot on the spritesheet
	m_selectCarPrevious.setTexture(resourceHolder["radioSheet"], resourceHolder["previousIcon"], fontHolder["font"], sf::IntRect(0,0,51, 48));
	m_selectCarNext.setTexture(resourceHolder["radioSheet"], resourceHolder["nextIcon"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_selectTrackPrevious.setTexture(resourceHolder["radioSheet"], resourceHolder["previousIcon"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_selectTrackNext.setTexture(resourceHolder["radioSheet"], resourceHolder["nextIcon"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_selectLapsPrevious.setTexture(resourceHolder["radioSheet"], resourceHolder["previousIcon"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_selectLapsNext.setTexture(resourceHolder["radioSheet"], resourceHolder["nextIcon"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_selectAiAmountPrevious.setTexture(resourceHolder["radioSheet"], resourceHolder["previousIcon"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	m_selectAiAmountNext.setTexture(resourceHolder["radioSheet"], resourceHolder["nextIcon"], fontHolder["font"], sf::IntRect(0, 0, 51, 48));
	//number sprite sheet gives initial pposition for the spritesheet
	m_carNum.setTexture(resourceHolder["radioSheet"], resourceHolder["numbersSpriteSheet"], fontHolder["font"], sf::IntRect(40, 0, 40, 48));
	m_trackNum.setTexture(resourceHolder["radioSheet"], resourceHolder["numbersSpriteSheet"], fontHolder["font"], sf::IntRect(40, 0, 40, 48));
	m_lapsNum.setTexture(resourceHolder["radioSheet"], resourceHolder["numbersSpriteSheet"], fontHolder["font"], sf::IntRect(40, 0, 40, 48));
	m_aiNum.setTexture(resourceHolder["radioSheet"], resourceHolder["numbersSpriteSheet"], fontHolder["font"], sf::IntRect(40, 0, 40, 48));

	newIndex = m_menuIndex;
	//images on the right
	m_trackSprite.setTexture(resourceHolder["testMap"]);
	m_trackSprite.setPosition(1000, 500);
	 
	m_carSprite.setTexture(resourceHolder["testCar"]);
	m_carSprite.setPosition(1050, 200);
}

PreRaceScreen::~PreRaceScreen()
{
	 
}
//update all widgets
void PreRaceScreen::update(GameState& current, GameState& previous)
{
	if (current == GameState::PreRace)
	{	
		//if statement used to make the menu start at the top
		if (once == false)
		{
			m_widgets[m_menuIndex]->getFocus();
			m_widgets[0]->getFocus();
			m_widgets[1]->getFocus();
			system("CLS");
			once = true;
		}

		for (auto& widget : m_widgets)
		{
			widget->update();
		}
		 
		if (m_canScroll == false)
		{
			//Checking if we can scroll again
			float timeGone = m_scrollClock.getElapsedTime().asSeconds();
			if (timeGone > 0.35f)
				m_canScroll = true;
		
		}
	}
}

void PreRaceScreen::render(sf::RenderWindow& window, GameState& current, GameState& previous)
{
	if (current == GameState::PreRace)
	{
		window.draw(m_bgSprite);
		//draw all widgets
		for (auto& widget : m_widgets)
		{
			widget->render(window);
		}
				 
		window.draw(m_bButtonSprite);
		//draw all labels
		m_label.render(window);
		m_selectCar.render(window);
		m_selectTrack.render(window);
		m_selectLaps.render(window);
		m_selectAiNo.render(window);
		window.draw(m_trackSprite);
		window.draw(m_carSprite);
	}
}

void PreRaceScreen::handleInput(Xbox360Controller& controller, GameState& current, GameState& previous)
{
	if (current == GameState::PreRace && m_canScroll)
	{
		//used for menu selection
		newIndex = m_menuIndex;

		m_widgets[m_menuIndex]->handleInput(controller);
		//press down menu selection goes down
		if (controller.getCurrent().DpadDown && controller.getPrevious().DpadDown == false
			|| controller.getCurrent().LeftThumbStickDown && controller.getPrevious().LeftThumbStickDown == false)
		{
			m_canScroll = false;
			newIndex++;
			m_audioP->m_soundArray[7].play();

		}
		//press up menu selection goes up
		if (controller.getCurrent().DpadUp && controller.getPrevious().DpadUp == false
			|| controller.getCurrent().LeftThumbStickUp && controller.getPrevious().LeftThumbStickUp == false)
		{
			m_canScroll = false;
			newIndex--;
			m_audioP->m_soundArray[7].play();

		}
		//b to go to previous gamestate
		if (controller.getCurrent().B && controller.getPrevious().B == false)
		{

			auto tempState = current;
			current = previous;
			previous = tempState;
			m_handledInput = true;
			m_audioP->m_soundArray[0].play();
		}
		//change game state

		if (newIndex == 12 && controller.getCurrent().A && controller.getPrevious().A == false)
		{
			m_audioP->m_soundArray[0].play();
			m_play.changeGameState(current, previous);
			m_handledInput = true;
		}


		//lets us move the numbers to what we want if its in range
		if (controller.getCurrent().DpadRight && controller.getPrevious().DpadRight == false || controller.getCurrent().LeftThumbStickRight && controller.getPrevious().LeftThumbStickRight == false)
		{
			m_audioP->m_soundArray[7].play();
			//if statement moves the textureRect to a new position also saves the car number were using 
			//while we are on the top button when we press right
			if (newIndex == 8)
			{
				auto rect = m_carNum.getTextureRect();
				m_carNum.setTextureRectCar(sf::IntRect(rect.left + 40, 0, 40, 48));
				saveCarNum++;
				if (saveCarNum > 9)
					saveCarNum = 1;
				m_widgets[8] = &m_carNum;
			}
			//same as above
			if (newIndex == 9)
			{
				auto rect = m_trackNum.getTextureRect();
				m_trackNum.setTextureRectTrack(sf::IntRect(rect.left + 40, 0, 40, 48));
				saveTrackNum++;
				if (saveTrackNum > 1)
					saveTrackNum = 1;
				m_widgets[9] = &m_trackNum;
			}
			//same as above
			if (newIndex == 10)
			{
				auto rect = m_lapsNum.getTextureRect();
				m_lapsNum.setTextureRectLaps(sf::IntRect(rect.left + 40, 0, 40, 48));
				m_widgets[10] = &m_lapsNum;
				saveLapsNum++;
				if (saveLapsNum > 9)
					saveLapsNum = 1;
			}
			//same as above
			if (newIndex == 11)
			{
				auto rect = m_aiNum.getTextureRect();
				m_aiNum.setTextureRectAi(sf::IntRect(rect.left + 40, 0, 40, 48));
				m_widgets[11] = &m_aiNum;
				saveAiNum++;
				if (saveAiNum > 5)
					saveAiNum = 1;
			}
			
		}
		//if statement moves the textureRect to a new position also saves the car number were using 
		//while we are on the top button when we press left
		if (controller.getCurrent().DpadLeft && controller.getPrevious().DpadLeft == false || controller.getCurrent().LeftThumbStickLeft && controller.getPrevious().LeftThumbStickLeft == false)
		{
			m_audioP->m_soundArray[7].play();
			if (newIndex == 8)
			{
				auto rect = m_carNum.getTextureRect();
				m_carNum.setTextureRectCar(sf::IntRect(rect.left - 40, 0, 40, 48));
				m_widgets[8] = &m_carNum;
				saveCarNum--;
				if (saveCarNum < 1)
					saveCarNum = 1;

			}
			//same as above
			if (newIndex == 9)
			{
				auto rect = m_trackNum.getTextureRect();
				m_trackNum.setTextureRectTrack(sf::IntRect(rect.left - 40, 0, 40, 48));
				m_widgets[9] = &m_trackNum;
				saveTrackNum--;
				if (saveTrackNum < 1)
					saveTrackNum = 1;
			}
			//same as above
			if (newIndex == 10)
			{
				auto rect = m_lapsNum.getTextureRect();
				m_lapsNum.setTextureRectLaps(sf::IntRect(rect.left - 40, 0, 40, 48));
				m_widgets[10] = &m_lapsNum;
				saveLapsNum--;
				if (saveLapsNum < 1)
					saveLapsNum = 9;
			}
			//same as above
			if (newIndex == 11)
			{
				auto rect = m_aiNum.getTextureRect();
				m_aiNum.setTextureRectAi(sf::IntRect(rect.left - 40, 0, 40, 48));
				m_widgets[11] = &m_aiNum;
				saveAiNum--;
				if (saveAiNum < 1)
					saveAiNum = 5;

			}
		}
		//if the menu index is not equal to our index
		if (newIndex != m_menuIndex)
		{
			//makes sure the numbers are within the range we want them 
			if (newIndex == 13)
				newIndex = 8;
			if (newIndex == 7)
				newIndex = 12;

			m_widgets[m_menuIndex]->loseFocus();
			m_menuIndex = newIndex; //assign our new index to our menu index
			m_widgets[m_menuIndex]->getFocus();

			//calls the method that lets us animate and colour the buttons to the left and right of our selected button without
			//selecting them
			animateSideButtons();
		}

		if (m_canScroll == false)
		{
			m_scrollClock.restart();
		}
	}
	else
		m_handledInput = false;
}
void PreRaceScreen::animateSideButtons()
{
	//if we are on the top button
	if (m_menuIndex == 8)
	{
		//animate the button to the left and the right of us
		m_widgets[0]->getFocus();
		m_widgets[1]->getFocus();
		//also stop animating the previous selected buttons
		m_widgets[x]->loseFocus();
		m_widgets[y]->loseFocus();
		
		m_widgets[z]->loseFocus();
		//these are the new previous selected buttons
		x = 8;
		y = 0;
		z = 1;
	}
	
	if (m_menuIndex == 9)
	{
		if (checkOnce == false)
		{
			//do this once or it wont work
			//sets the initial previous to these values
			z = 1;
			x = 8;
			y = 0;
			checkOnce = true;
		}
		
		m_widgets[2]->getFocus();
		m_widgets[3]->getFocus();
		m_widgets[x]->loseFocus();
		m_widgets[y]->loseFocus();
		m_widgets[z]->loseFocus();

		x = 9;
		y = 2;
		z = 3;
	}
	//same as above
	if (m_menuIndex == 10)
	{
		m_widgets[4]->getFocus();
		m_widgets[5]->getFocus();
		m_widgets[x]->loseFocus();
		m_widgets[y]->loseFocus();
		m_widgets[z]->loseFocus();

		x = 10;
		y = 4;
		z = 5;
	}
	//same as above
	if (m_menuIndex == 11)
	{
		m_widgets[6]->getFocus();
		m_widgets[7]->getFocus();
		m_widgets[x]->loseFocus();
		m_widgets[y]->loseFocus();
		m_widgets[z]->loseFocus();

		x = 11;
		y = 6;
		z = 7;
	}
	//same as above
	if (m_menuIndex == 12)
	{
		if (checkOnce == false)
		{
			//do this once or it wont work
			//sets the initial previous to these values
			z = 1;
			x = 8;
			y = 0;
			checkOnce = true;
		}
		m_widgets[12]->getFocus();
		m_widgets[x]->loseFocus();
		m_widgets[y]->loseFocus();
		m_widgets[z]->loseFocus();

		x = 12;
		y = 12;
		z = 12;
	}
	 

}




