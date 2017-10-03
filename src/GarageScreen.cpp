#include "GarageScreen.h"
#include "ScreenManager.h"
#include "Player.h"

/// <summary>
/// Authors: Daryl Keogh
/// Description: The garage screen is used for upgrading the players vehicle. The player can change the part of the vehicle they would like to upgrade
/// by pressing either the Right or Left bumpers on the xbox controller. They can adjust the level of upgrades using the dpad or left thumbstick. 
/// When in the colour/paint menu the user can select a paint by pressing A, if the user presse sthe start button to confirm the purchase, that paint job will
/// be applied to the users car and will be seen during the race screen.
/// Date: 21/03/2017
/// Time Spent: 4-5 hours
/// </summary>

GarageScreen::GarageScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Player& player,Audio& audio) :
	Screen(audio),
	m_currentCost(0),
	m_sliderSelectedFirst(false),
	m_accelerationlevel("Acceleration", sf::Vector2f(640, 635)),
	m_topSpeedLevel("Top Speed", sf::Vector2f(640, 470)),
	m_brakeLevel("Braking", sf::Vector2f(640, 535)),
	m_handlingLevel("Handling", sf::Vector2f(640, 535)),
	m_engineLabel("Engine", 65),
	m_steeringLabel("Steering", 65),
	m_brakeLabel("Brakes", 65),
	m_colorLabel("Colour", 65),
	m_vehicleLabel("Vehicle", 50),
	m_cashLabel("Cash: $", 50),
	m_costLabel("Upgrades Cost: ", 50),
	m_confirmLabel("Confirm\nPurchase", 35),
	m_labelIndex(0),
	m_playerRef(player), 
	m_backLabel("Back", 50),
	m_white("white", resourceHolder, fontHolder),
	m_black("black", resourceHolder, fontHolder),
	m_red("red", resourceHolder, fontHolder),
	m_blue("blue", resourceHolder, fontHolder),
	m_orange("orange", resourceHolder, fontHolder),
	m_purple("purple", resourceHolder, fontHolder),
	m_selectLabel("Select", 50),
	m_paintIndex(0)
{
	m_rbSprite.setTexture(resourceHolder["rbIcon"]);
	auto rectangle = m_rbSprite.getGlobalBounds();
	m_rbSprite.setOrigin(rectangle.width / 2.0f, rectangle.height / 2.0f);
	m_rbSprite.setPosition(1230, 270);
	m_lbSprite.setTexture(resourceHolder["lbIcon"]);
	m_lbSprite.setOrigin(rectangle.width / 2.0f, rectangle.height / 2.0f);
	m_lbSprite.setPosition(50, 270);


	m_backLabel.setFont(fontHolder["font"]);
	m_backLabel.setGuiPos(sf::Vector2f(1220, 665));

	//b button
	m_bSprite.setTexture(resourceHolder["Bbutton"]);
	m_bSprite.setPosition(1120, 660);
	m_bSprite.setScale(0.023f, 0.023f);
	//loading up our recolour shader
	m_shader.loadFromFile("./resources/Shaders/colorChangeShader.frag", sf::Shader::Fragment);
	
	m_aBtnSprite.setTexture(resourceHolder["aButton"]);
	auto aBtnRect = m_aBtnSprite.getGlobalBounds();
	m_aBtnSprite.setOrigin(aBtnRect.width / 2.0f, aBtnRect.height / 2.0f);
	m_aBtnSprite.setPosition(605, 680);

	m_selectLabel.setFont(fontHolder["font"]);
	m_selectLabel.setGuiPos(705, 665);

	//Adding pur paint objects to our paint array
	m_paintArray[0] = &m_white;
	m_paintArray[1] = &m_red;
	m_paintArray[2] = &m_blue;
	m_paintArray[3] = &m_orange;
	m_paintArray[4] = &m_purple;
	m_paintArray[5] = &m_black;

	//setting the alpha and positions of our paint objects
	m_white.setPos(640, 480);
	m_white.setAlpha(255);
	m_red.setPos(920, 480);
	m_red.setAlpha(127);
	m_blue.setPos(1200, 480);
	m_blue.setAlpha(0);
	m_orange.setPos(-200, 480);
	m_orange.setAlpha(0);
	m_black.setPos(360, 480);
	m_black.setAlpha(127);
	m_purple.setPos(80, 480);
	m_purple.setAlpha(0);

	setPaintAlphas();

	//Setting up our A button sprite
	m_startButtonSprite.setTexture(resourceHolder["startButton"]);
	auto btnRect = m_startButtonSprite.getGlobalBounds();
	m_startButtonSprite.setOrigin(btnRect.width / 2.0f, btnRect.height / 2.0f);
	m_startButtonSprite.setPosition(35, 680);

	//Setting up our information labels font
	m_cashLabel.setFont(fontHolder["font"]);
	m_cashLabel.setString("CASH: $" + std::to_string(m_playerRef.getCash()), sf::Color::Green); //set the cash label to green
	m_costLabel.setFont(fontHolder["font"]);
	m_confirmLabel.setFont(fontHolder["font"]);
	//Setting the position of our information labels
	m_confirmLabel.setGuiPos(140, 670);
	m_cashLabel.resetOrigin(); //reset our oriign of the label so it is not centred on its size
	m_cashLabel.setGuiPos(2.5, 2.5);
	m_costLabel.resetOrigin();
	m_costLabel.setGuiPos(2.5, 50);
	m_costLabel.setString("COST: $0", sf::Color::White); //set the cost label to white and set its default string

 
	//centre the car sprite on our car selected box
	m_carSprite = player.getSprite("car");
	auto carRect = m_carSprite.getGlobalBounds();
	m_carSprite.setOrigin(carRect.width / 2.0f, carRect.height / 2.0f);
	m_carSprite.setScale(1.5, 1.5);
	m_carSprite.setPosition(640, 125);

	//Setting our background texture
	m_sprite.setTexture(resourceHolder["mainMenuBg"]);
	m_carBoxSprite.setTexture(resourceHolder["carSelect"]);
	auto rect = m_carBoxSprite.getGlobalBounds();
	m_carBoxSprite.setOrigin(rect.width / 2.0f, rect.height / 2.0f);
	m_carBoxSprite.setPosition(640, 125);

	//Setting the textures of all of our sliders
	m_accelerationlevel.setGarageTexture(resourceHolder["sliderSheet"], resourceHolder["upgradeSheet"], fontHolder["font"]);
	m_topSpeedLevel.setGarageTexture(resourceHolder["sliderSheet"], resourceHolder["upgradeSheet"], fontHolder["font"]);
	m_brakeLevel.setGarageTexture(resourceHolder["sliderSheet"], resourceHolder["upgradeSheet"], fontHolder["font"]);
	m_handlingLevel.setGarageTexture(resourceHolder["sliderSheet"], resourceHolder["upgradeSheet"], fontHolder["font"]);

	//Adding our labels to the array
	m_labelArray[0] = &m_engineLabel;
	m_labelArray[1] = &m_steeringLabel;
	m_labelArray[2] = &m_colorLabel;
	m_labelArray[3] = &m_brakeLabel;

	//Setting the font of each label
	for (auto& label : m_labelArray)
		label->setFont(fontHolder["font"]);

	m_vehicleLabel.setFont(fontHolder["font"]);

	//Setting the position and alpha of our labels
	m_engineLabel.setGuiPos(640, 250);
	m_steeringLabel.setGuiPos(1040, 250);
	m_steeringLabel.setAlpha(125); //set the alpha of our label so we know that the engine label is in focus
	m_brakeLabel.setGuiPos(240, 250);
	m_brakeLabel.setAlpha(125);
	m_vehicleLabel.setGuiPos(640, 25);
	m_colorLabel.setGuiPos(-160, 250);


	m_engineUpgrades[0] = &m_topSpeedLevel;
	m_engineUpgrades[1] = &m_accelerationlevel;

	//Putting all of our sliders into one array 
	m_sliders[0] = &m_topSpeedLevel;
	m_sliders[1] = &m_accelerationlevel;
	m_sliders[2] = &m_brakeLevel;
	m_sliders[3] = &m_handlingLevel;
}

GarageScreen::~GarageScreen()
{

}

void GarageScreen::update(GameState& current, GameState& previous)
{
	if (current == GameState::Garage)
	{
		m_carSprite.setRotation(m_carSprite.getRotation() + .15); //rotate our car sprite 

		//selects our top speed slider to get focus when we enter the garage for the first time
		if (m_sliderSelectedFirst == false)
		{
			m_topSpeedLevel.getFocus();
			m_sliderSelectedFirst = true;
		}

		//Update our sliders
		m_accelerationlevel.update();
		m_topSpeedLevel.update();
		m_handlingLevel.update();
		m_brakeLevel.update();

		//Update our paint objects
		for (auto& paint : m_paintArray)
			paint->update();
	}	

	//updating our cash label to refelect any changes made to their cash
	m_cashLabel.setString("CASH: $" + std::to_string(m_playerRef.getCash()), sf::Color::Green);
}

void GarageScreen::render(sf::RenderWindow& window, GameState& current, GameState& previous)
{
	if (current == GameState::Garage)
	{
		
		//draw all of our sprites
		window.draw(m_sprite);
		window.draw(m_lbSprite);
		window.draw(m_rbSprite);
		window.draw(m_bSprite);
		m_backLabel.render(window);
		window.draw(m_carBoxSprite);
		window.draw(m_carSprite, &m_shader); //draw our car sprite with the recolour shader so we can show the new re-colour


		//draw our labels
		m_vehicleLabel.render(window);
		m_cashLabel.render(window);
		m_costLabel.render(window);
		m_confirmLabel.render(window);


		//Draw our A Button sprite
		window.draw(m_startButtonSprite);


		if (m_labelIndex == 0)//if the label focused is engine
		{
			m_accelerationlevel.render(window);
			m_topSpeedLevel.render(window);
		}
		if (m_labelIndex == 1) //if the label focused is brake
			m_handlingLevel.render(window);

		if (m_labelIndex == 2) //if the label focused is colour, draw our paint array
		{
			for (auto& paint : m_paintArray)
				paint->render(window);

			window.draw(m_aBtnSprite);
			m_selectLabel.render(window);
		}
		if (m_labelIndex == 3)
			m_brakeLevel.render(window);

		//Draw our labels
		for (auto& label : m_labelArray)
			label->render(window);
	}
}
void GarageScreen::handleInput(Xbox360Controller& controller, GameState& current, GameState& previous)
{
	if (current == GameState::Garage)
	{
		int labelIndex = m_labelIndex;
		int sliderIndex = m_engineIndex;

		if (controller.getCurrent().B && controller.getPrevious().B == false)
		{
			m_audioP->m_soundArray[0].play();
			auto tempState = current;
			current = previous;
			previous = tempState;
			resetSliders(); //reset our sliders if we have changed them
			m_currentCost = 0;
			setCost();

			//deslect any selected paint objects
			for (auto& paint : m_paintArray)
				paint->selected(false);
		}

		//If we hit a to select a color
		if (controller.getCurrent().A && controller.getPrevious().A == false)
		{
			if (m_labelIndex == 2)
			{
				if (m_paintArray[m_paintIndex]->isSelected() == false)
				{
					m_paintArray[m_paintIndex]->getFocus();
					m_paintArray[m_paintIndex]->selected(true);
					m_currentCost += m_paintArray[m_paintIndex]->getPrice(); //add the pric eof the paint to the current cost variable
					//Update our cost label
					setCost();
				}
			}
		}
		//if the user presses Start to confirm purchase we check if there has been any changes in the sliders levels
		//and if the user has the appropriate amount of cash we take it away from them and apply the upgrades
		if(controller.getCurrent().Start && controller.getPrevious().Start == false)
		{
			int cost = 0;// we will use this to calculate the total cost of the upgrades

			cost += getCost(m_accelerationlevel.getLevel(), m_playerRef.getAccelerationLevel(), ACCEL_PRICE);
			cost += getCost(m_topSpeedLevel.getLevel(), m_playerRef.getTopSpeedLevel(), TOP_SPEED_PRICE);
			cost += getCost(m_brakeLevel.getLevel(), m_playerRef.getBrakeLevel(), BRAKE_PRICE);
			cost += getCost(m_handlingLevel.getLevel(), m_playerRef.getSteeringLevel(), HANDLING_PRICE);

			//if our colour array at the last indexed colour is selected, then add the cost of the paint to the total cost
			if (m_paintArray[m_paintIndex]->isSelected())
				cost += m_paintArray[m_paintIndex]->getPrice();

			//If the player has enough cash, apply the upgrade(s)
			if (m_playerRef.getCash() >= cost)
			{
				//if our colour array at the last indexed colour is selected, then apply the colour of th epaint to the players vehicle
				if (m_paintArray[m_paintIndex]->isSelected())
				{
					m_paintArray[m_paintIndex]->selected(false);
					m_playerRef.setVehicleColour(m_paintArray[m_paintIndex]->getColour());
					m_paintArray[m_paintIndex]->loseFocus(); //unhighlight the colour a sit is not applied
				}


				m_playerRef.setCash(m_playerRef.getCash() - cost);
				m_audioP->m_soundArray[1].play();
				applyUpgrades(m_accelerationlevel.getLevel(), m_playerRef.getAccelerationLevel(), "accel");
				applyUpgrades(m_topSpeedLevel.getLevel(), m_playerRef.getTopSpeedLevel(), "speed");
				applyUpgrades(m_brakeLevel.getLevel(), m_playerRef.getBrakeLevel(), "brake");
				applyUpgrades(m_handlingLevel.getLevel(), m_playerRef.getSteeringLevel(), "steering");

				//reset our current cost
				m_currentCost = 0;
				//Update our cost label
				setCost();
			}

				//updating our cash label to refelect any changes made to their cash
			m_cashLabel.setString("CASH: $" + std::to_string(m_playerRef.getCash()), sf::Color::Green);
		}

	 

		//Checking if we have moved through our sliders
		if (controller.getCurrent().DpadDown && controller.getPrevious().DpadDown == false)
		{
			sliderIndex++;
			m_audioP->m_soundArray[7].play();
		}

		if (controller.getCurrent().DpadUp && controller.getPrevious().DpadUp == false)
		{
			sliderIndex--;
			m_audioP->m_soundArray[7].play();
		}

		//checking if we can upgrade our parts
		if (controller.getCurrent().DpadRight && controller.getPrevious().DpadRight == false
			|| controller.getCurrent().LeftThumbStickRight && controller.getPrevious().LeftThumbStickRight == false)
		{
			if (m_labelIndex == 0)
			{

				if (m_engineIndex == 0 && m_topSpeedLevel.getLevel() < 5)
				{
					m_topSpeedLevel.increaseGarageIndicator();
					m_currentCost += TOP_SPEED_PRICE;
				}
					
				else if (m_engineIndex == 1 && m_accelerationlevel.getLevel() < 5)
				{
					m_accelerationlevel.increaseGarageIndicator();
					m_currentCost += ACCEL_PRICE;
				}
					
			}

			else if (m_labelIndex == 1 && m_handlingLevel.getLevel() < 5)
			{
				if(m_labelIndex == 0)
					m_engineUpgrades[m_engineIndex]->increaseGarageIndicator();
				else if (m_labelIndex == 1)
					m_handlingLevel.increaseGarageIndicator();
					m_currentCost += HANDLING_PRICE;
			}	

			//if we are on the color menu
			else if (m_labelIndex == 2 && m_paintArray[m_paintIndex]->getPos() == m_paintArray[m_paintIndex]->getNextPos())
			{
				if (m_paintArray[m_paintIndex]->isSelected())
				{
					m_paintArray[m_paintIndex]->loseFocus(); //lose focus on the currently focused paint object
					m_paintArray[m_paintIndex]->selected(false); //deselect the paint object
					m_currentCost -= m_paintArray[m_paintIndex]->getPrice(); //reduces the cost of upgrade sby the pric eof the selecte dpaint object
				}
					

				m_paintIndex++;

				if (m_paintIndex > 5)
					m_paintIndex = 0;

				//decrease the position of each paint object by 280, and focus on the one 
				for (auto& paint : m_paintArray)
					paint->setNextPos(paint->getPos().x - 280, paint->getPos().y);

				setPaintAlphas(); //set the next alpha of each paint
				setColour(m_paintArray[m_paintIndex]->getColour()); //sets the color of the car sprite to reflect the colour change
			}

			else if (m_labelIndex == 3 && m_brakeLevel.getLevel() < 5)
			{
				m_brakeLevel.increaseGarageIndicator();
				m_currentCost += BRAKE_PRICE;
			}
			
			//Update our cost label
			setCost();
		}
		//checking if the use rpresse dleft on the dpad or left thumbstick
		if (controller.getCurrent().DpadLeft && controller.getPrevious().DpadLeft == false
			|| controller.getCurrent().LeftThumbStickLeft && controller.getPrevious().LeftThumbStickLeft == false)
		{
			m_audioP->m_soundArray[7].play();
			if (m_labelIndex == 0)
			{
				if (m_engineIndex == 0 && m_topSpeedLevel.getLevel() > m_playerRef.getTopSpeedLevel())
				{
					m_currentCost -= TOP_SPEED_PRICE;
					m_topSpeedLevel.decreaseGarageIndicator();
				}

				else if (m_engineIndex == 1 && m_accelerationlevel.getLevel() > m_playerRef.getAccelerationLevel())
				{
					m_currentCost -= ACCEL_PRICE;
					m_accelerationlevel.decreaseGarageIndicator();
				}
					
			}

			else if (m_labelIndex == 1 && m_handlingLevel.getLevel() > m_playerRef.getSteeringLevel())
			{
				m_handlingLevel.decreaseGarageIndicator();
				m_currentCost -= HANDLING_PRICE;
			}

			//if we are on the color menu and our focused button is in place then move
			else if (m_labelIndex == 2 && m_paintArray[m_paintIndex]->getPos() == m_paintArray[m_paintIndex]->getNextPos())
			{
				if (m_paintArray[m_paintIndex]->isSelected())
				{
					m_paintArray[m_paintIndex]->loseFocus(); //lose focus on the currently focused paint object
					m_paintArray[m_paintIndex]->selected(false); //deselect the paint object
					m_currentCost -= m_paintArray[m_paintIndex]->getPrice(); //reduces the cost of upgrade sby the pric eof the selecte dpaint object
				}

				m_paintIndex--;

				if (m_paintIndex < 0)
					m_paintIndex = 5;

				//decrease the position of each paint object by 280, and focus on the one 
				for (auto& paint : m_paintArray)
					paint->setNextPos(paint->getPos().x + 280, paint->getPos().y);

				setPaintAlphas(); //set the next alpha of each paint object
				setColour(m_paintArray[m_paintIndex]->getColour()); //sets the color of the car sprite to reflect the colour change
			}
				
			else if (m_labelIndex == 3 && m_brakeLevel.getLevel() > m_playerRef.getBrakeLevel())
			{
				m_brakeLevel.decreaseGarageIndicator();
				m_currentCost -= BRAKE_PRICE;
			}

			//Update our cost label
			setCost();
		}


		//if we hit LB move our labels left
		if (controller.getCurrent().LB && controller.getPrevious().LB == false)
		{
			labelIndex--;
			m_audioP->m_soundArray[7].play();
			for (auto& label : m_labelArray)
			{
				if (label->getPos().x >= 1040)
				{
					label->setGuiPos(-560, label->getPos().y);
				}
				label->setGuiPos(label->getPos().x + 400, label->getPos().y);
			}

		}
		//If w ehit RB move our labels right
		if (controller.getCurrent().RB && controller.getPrevious().RB == false)
		{
			labelIndex++;
			m_audioP->m_soundArray[7].play();
			for (auto& label : m_labelArray)
			{
				if (label->getPos().x <= -160)
				{
					label->setGuiPos(1440, label->getPos().y);
				}
				label->setGuiPos(label->getPos().x - 400, label->getPos().y);
			}
			
		}

		//checking if our local index is different from our global index, if so change the currently index label
		if (labelIndex != m_labelIndex)
		{
			if (labelIndex < 0)
				labelIndex = 3;
			if (labelIndex > 3)
				labelIndex = 0;

			for (auto& label : m_labelArray)
			{
				if (label->getPos().x == 640)
					label->setAlpha(255); //sets the label to be full alpha if centre don screen
				else if (label->getPos().x == 1040 || label->getPos().x == 240)
					label->setAlpha(125); //set the alpha to roughly 50% if not focused
				else
					label->setAlpha(0); //if off screen then set the alpha to 0
			}

			//Asigning our label index our new index
			m_labelIndex = labelIndex;


			//Focusing on our sliders depending on what slider is in view
			if (m_labelIndex == 1)
			{
				focusSlider("Steer");
			}
			if (m_labelIndex == 3)
			{
				focusSlider("Brake");
			}
		}

		//Checking if we have cycled through our slider son the engine option
		if (sliderIndex != m_engineIndex)
		{
			m_engineUpgrades[m_engineIndex]->loseFocus(); //lose focus on the currently selected slider

			//checking the bounds of our array
			if (sliderIndex <= -1)
				sliderIndex = 1;
			if (sliderIndex >= 2)
				sliderIndex = 0;

			//update our index
			m_engineIndex = sliderIndex;

			//get focus on the new index
			m_engineUpgrades[m_engineIndex]->getFocus();
		}
	}
}

void GarageScreen::focusSlider(std::string sliderName)
{
	//if the slider name is brake, then get focus on brake, otherwise lose focus
	if (sliderName == "Brake")
		m_brakeLevel.getFocus();
	else
		m_brakeLevel.loseFocus();


	if (sliderName == "Steer")
		m_handlingLevel.getFocus();
	else
		m_handlingLevel.loseFocus();
}

//Calculate sthe cost of a part
int GarageScreen::getCost(int sliderLevel, int playerLevel, const int UpgradePrice)
{
	//we chekc if the slider level is greater than the players level
	if (sliderLevel > playerLevel)
	{
		int levelDiff = sliderLevel - playerLevel;
		return levelDiff * UpgradePrice; //we then return a cost of the level difference multiplied by the cost
	}
	else
		return 0;
}

void GarageScreen::applyUpgrades(int sliderLevel, int playerLevel, std::string part)
{
	int newLevel = sliderLevel - playerLevel;

	if (part == "speed")
		m_playerRef.setTopSpeedLevel(newLevel + m_playerRef.getTopSpeedLevel());
	else if (part == "accel")
		m_playerRef.setAccelerationLevel(newLevel + m_playerRef.getAccelerationLevel());
	else if (part == "brake")
		m_playerRef.setBrakeLevel(newLevel + m_playerRef.getBrakeLevel());
	else
		m_playerRef.setSteeringLevel(newLevel + m_playerRef.getSteeringLevel());
}

void GarageScreen::resetSliders()
{
	m_accelerationlevel.setSliderLevel(m_playerRef.getAccelerationLevel());
	m_topSpeedLevel.setSliderLevel(m_playerRef.getTopSpeedLevel());
	m_brakeLevel.setSliderLevel(m_playerRef.getBrakeLevel());
	m_handlingLevel.setSliderLevel(m_playerRef.getSteeringLevel());
}

void GarageScreen::setCost()
{
	//Updating our cost label
	if (m_currentCost > 0 && m_currentCost > m_playerRef.getCash()) //if our cost is greater than the players cash, set the cost colour to red
		m_costLabel.setString("COST: $" + std::to_string(m_currentCost), sf::Color::Red);
	else if(m_currentCost > 0 && m_currentCost <= m_playerRef.getCash()) //else if our cost is greater than 0 and less than the players cash, set it to yellow
		m_costLabel.setString("COST: $" + std::to_string(m_currentCost), sf::Color::Yellow);
	else //else if it is 0 set it to white
		m_costLabel.setString("COST: $" + std::to_string(m_currentCost), sf::Color::White);
}

void GarageScreen::setPaintAlphas()
{
	for (auto& paint : m_paintArray)
	{
		if (paint->getNextPos().x == 640)
			paint->setNextAlpha(100);
		else if (paint->getNextPos().x == 920 || paint->getNextPos().x == 360)
			paint->setNextAlpha(50);
		else
			paint->setNextAlpha(0);
	}
}

void GarageScreen::setColour(sf::Color color)
{
	//Reset our shader variables
	m_shader.setUniform("newR", 0);
	m_shader.setUniform("newG", 0);
	m_shader.setUniform("newB", 0);
	m_shader.setUniform("newA", 0);

	//Calculate our new colours
	float newR = color.r / 255.0;
	float newG = color.g / 255.0;
	float newB = color.b / 255.0;
	float newA = color.a / 255.0;

	//Set our shade runiform variables to our new calculated colour
	m_shader.setUniform("newR", newR);
	m_shader.setUniform("newG", newG);
	m_shader.setUniform("newB", newB);
	m_shader.setUniform("newA", newA);
}