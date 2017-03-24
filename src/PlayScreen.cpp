
#include "PlayScreen.h"
#include "ScreenManager.h"

PlayScreen::PlayScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio) :
	Screen(audio),
	m_maxLaps(0),
	m_player(resourceHolder),
	m_track(resourceHolder),
	m_hud(resourceHolder, fontHolder),
	m_aiAmount(5),
	m_gameReady(false),
	changeToNight(false),
	m_currentColor(35),
	m_windowRect(0,0, 640, 360),
	m_timeGoneSinceStart(0),
	m_playAnimation(false),
	m_firstAnimationPlayed(false),
	m_secondAnimationPlayed(false),
	m_thirdAnimationPlayed(false),
	m_finalAnimationPlayed(false),
	m_canDrawStart(true),
	m_playersPos(1)
{
	//setting up our start indicator sprite
	m_startSprite.setTexture(resourceHolder["startSheet"]);
	m_startSprite.setTextureRect(sf::IntRect(0,0, 30, 114)); //set teh texture rectangle to the first image of the spritehseet
	auto spriteRect = m_startSprite.getGlobalBounds();
	m_startSprite.setOrigin(spriteRect.width / 2.0f, spriteRect.height / 2.0f);
	m_startSprite.setPosition(865, 1408); //position our timer indicator just infront of the lap finish indicator

	//Setting up all of our street lights
	setUpLight(m_streetLights[0], sf::Vector2f(740, 1339), resourceHolder["streetLight"]);
	setUpLight(m_streetLights[1], sf::Vector2f(740, 1476.5), resourceHolder["streetLight"]);
	setUpLight(m_streetLights[2], sf::Vector2f(1169.75, 1476.5), resourceHolder["streetLight"]);
	setUpLight(m_streetLights[3], sf::Vector2f(1169.75, 1339), resourceHolder["streetLight"]);
	setUpLight(m_streetLights[4], sf::Vector2f(1196, 954.5), resourceHolder["streetLight"]);
	setUpLight(m_streetLights[5], sf::Vector2f(868.5, 960.5), resourceHolder["streetLight"]);
	setUpLight(m_streetLights[6], sf::Vector2f(355.75, 706.25), resourceHolder["streetLight"]);
	setUpLight(m_streetLights[7], sf::Vector2f(681.75, 443.25), resourceHolder["streetLight"]);
	setUpLight(m_streetLights[8], sf::Vector2f(1111.75, 581.5), resourceHolder["streetLight"]);
	setUpLight(m_streetLights[9], sf::Vector2f(1111.75, 443.25), resourceHolder["streetLight"]);
	setUpLight(m_streetLights[10], sf::Vector2f(681.75, 581.5), resourceHolder["streetLight"]);


	//Create our render texture to the size of our map
	lightTexture.create(1920, 1920);
	darkSprite.setTexture(lightTexture.getTexture()); //make our darksprites textur ethe render texture

	//Set the textures for our ai 
	for (int i = 0; i < m_aiAmount; i++)
		m_aiArray[i].setTexture(resourceHolder["car"], resourceHolder["headLight"]);

	//setsup our animations
	setupStartAnimation();

	m_hudArtistLabel.setFont(fontHolder["font"]);
	m_hudArtistLabel.setTextSize(20);
	
	m_hudSongLabel.setFont(fontHolder["font"]);
	m_hudSongLabel.setTextSize(20);
	
}

PlayScreen::~PlayScreen()
{

}

void PlayScreen::update(GameState& current, GameState& previous)
{
	if (current == GameState::Play)
	{
		//if the race is finished check if the time gone is over 1.5 seconds, if so, go to post race screen
		if (m_raceFinished)
		{
			sf::Time timer = m_endClock.restart();
			m_timeGoneSinceEnd += timer.asSeconds();
			if (m_timeGoneSinceEnd >= 1.5f)
			{
				current = PostRace;
				previous = Play;
				if (m_playersPos == 1)
				{
					m_player.setCash(m_player.getCash() + 100);
				}
				if (m_playersPos == 2)
				{
					m_player.setCash(m_player.getCash() + 50);
				}
				else
					m_player.setCash(m_player.getCash() + 25);
				
				m_raceFinished = false;
				m_timeGoneSinceEnd = 0.0f;
			}
		}

		if (m_player.getLap() > m_maxLaps)
		{
			m_raceFinished = true;
			if (m_endClockStarted == false)
			{
				m_endClock.restart();
				m_endClockStarted = true;
			}

		}

		if(m_thirdAnimationPlayed)
			m_hud.update(current, m_player.getLap(), m_playersPos);

		animateStartIndicator();

		sf::Time timeGone = m_dayNightClock.restart();

		//Handling our night/day cycle
		if (changeToNight)
		{
			m_currentColor -= timeGone.asSeconds() * 3; //decrement our current color for our screen clear 
			if (m_currentColor < 35) //if we go below 35 (near pure black) set it to 35 and set our bool to false to reverse the cycle
			{
				m_currentColor = 35;
				changeToNight = false;
			}
		}
		//same as above but addign colour (light)
		else if (changeToNight == false)
		{
			m_currentColor += timeGone.asSeconds() * 3;
			if (m_currentColor > 205)
			{
				m_currentColor = 205;
				changeToNight = true;
			}
		}

		m_player.update(*m_levelRef); //update our player and their actions

		if (m_player.lapPassed()) //if the player has passed a lap then reset our hud
		{
			m_hud.resetTimer(); //reset our huds values
			m_player.setLapRecorded(); //set our lap recorded
		}


		for (int i = 0; i < m_aiAmount; i++)
			m_aiArray[i].update(*m_levelRef);

		for (int i = 0; i < m_aiAmount; i++)

			m_track.checkCollision(m_aiArray[i]);

		//Checks if any ai need to avoid any obstacles
		checkAiAvoid();

		checkPositions(); //checks the positions of each ai and player to see what positions they are in

		m_track.update(m_player, m_hud); //update our track
		m_track.update(m_player, m_hud); //update our track

		std::string s;
		std::string s2;
		if (m_audioP->musicIndexer == 0)
		{
			s = "Honom";
			s2 = "Purple Sun";
		}
		if (m_audioP->musicIndexer == 1)
		{
			s = "Hotline Miami";
			s2 = "Perturbator";
		}
		if (m_audioP->musicIndexer == 2)
		{
			s = "Lucy In Disgiuise";
			s2 = "Bristol Nights";
		}
		if (m_audioP->musicIndexer == 3)
		{
			s = "Makeup And Vanity Set";
			s2 = "Implant";
		}
		if (m_audioP->musicIndexer == 4)
		{
			s = "Miami Nights 1984";
			s2 = "Ocean Drive";
		}
		if (m_audioP->musicIndexer == 5)
		{
			s = "Michael Cassette";
			s2 = "Regetta";
		}
		if (m_audioP->musicIndexer == 6)
		{
			s = "Nightstop";
			s2 = "Dangerous Desires";
		}
		if (m_audioP->musicIndexer == 7)
		{
			s = "Robert Parker";
			s2 = "Running Wild";
		}
		if (m_audioP->musicIndexer == 8)
		{
			s = "A Space Love Adventure";
			s2 = "Power Rush";
		}
		if (m_audioP->musicIndexer == 9)
		{
			s = "VHS Dreams";
			s2 = "R.e.d.m";
		}

		m_hudArtistLabel.setString(s);
		m_hudSongLabel.setString(s2);
	}
}

void PlayScreen::render(sf::RenderWindow& window, GameState& current, GameState& previous)
{
	if (current == Play) //draw if the current gamestate is play
	{
		//calculating the top left of the window rectangle
		m_windowRect.left = window.getView().getCenter().x - window.getView().getSize().x / 2.0f;
		m_windowRect.top = window.getView().getCenter().y - window.getView().getSize().y / 2.0f;

		if (m_raceFinished == false)
		{
			//Setting our view to follow our player
			auto currentView = window.getView(); //gets the windows view
			currentView.setCenter(m_player.getPosition().x, m_player.getPosition().y); //sets its centre to follow the players position
			window.setView(currentView); //set our window our update view
		}

		lightTexture.clear(sf::Color(m_currentColor, m_currentColor, m_currentColor, 200)); //clear with slightly faded black
		lightTexture.display();

		//draw our players headlight onto the render texture
		lightTexture.draw(m_player.getSprite("headLight"));
		lightTexture.display();

		//For each street light, draw it to our render texture and display it
		for (int i = 0; i < 11; i++)
		{
			//if the window rectangle intersects the street light rectangle then draw them
			if (m_windowRect.intersects(m_streetLights[i].getGlobalBounds()))
			{
				lightTexture.draw(m_streetLights[i]);
				lightTexture.display();
			}
		}
		//For each ai in our array get their headlight sprite and draw it to our ender texture, then update our texture
		for (int i = 0; i < m_aiAmount; i++)
		{
			//if the window intersecst the headlight sprite then draw it and update our render texture
			if (m_windowRect.intersects(m_aiArray[i].getHeadlightSprite("headLight").getGlobalBounds()))
			{
				lightTexture.draw(m_aiArray[i].getHeadlightSprite("headLight"));
				lightTexture.display();
			}

		}

		//Render our track
		m_track.render(window, m_windowRect);

		//only draw our start animation/sprite if the bool is true
		if (m_canDrawStart)
			window.draw(m_startSprite);

		//Render our player
		m_player.render(window);

		//render our ai
		for (int i = 0; i < m_aiAmount; i++)
			m_aiArray[i].render(window, m_windowRect);

		//then draw our lights texture ontop of everything with the blend multiply
		window.draw(darkSprite, sf::BlendMultiply);

		m_hud.render(window,current);
		auto view = window.getView();
		m_hudArtistLabel.setGuiPos(view.getCenter().x - 300, view.getCenter().y + 115);
		m_hudSongLabel.setGuiPos( view.getCenter().x -300, view.getCenter().y + 140);
		m_hudArtistLabel.render(window);
		m_hudSongLabel.render(window);
	}
}

void PlayScreen::animateStartIndicator()
{
	//determine the time gone for our animation
	sf::Time timeSinceStart = m_raceClock.restart(); //get the time gone sinc ethe clock was restarted
	m_timeGoneSinceStart += timeSinceStart.asSeconds();
	
	if (m_timeGoneSinceStart < 0.9 && m_playStartSound == false)
	{
		m_playStartSound = true;
		m_audioP->m_soundArray[2].play();
	}

	if (m_timeGoneSinceStart >= 0.9 && m_firstAnimationPlayed == false)
	{
		m_firstAnimationPlayed = true;
		playAnaimtion("light1");
	}

	if (m_timeGoneSinceStart >= 1.9 && m_secondAnimationPlayed == false)
	{
		m_secondAnimationPlayed = true;
		playAnaimtion("light2");
	}

	if (m_timeGoneSinceStart >= 2.9 && m_thirdAnimationPlayed == false)
	{
		//start the race
		startRace();
		m_thirdAnimationPlayed = true;
		playAnaimtion("light3");
	}
	if (m_timeGoneSinceStart >= 3.9 && m_finalAnimationPlayed == false)
	{
		m_finalAnimationPlayed = true;
		playAnaimtion("fadeOff");
	}

	if (m_playAnimation)
	{
		animateStart();
	}
}


void PlayScreen::setGameReady(bool ready)
{
	m_dayNightClock.restart();
	m_raceClock.restart(); //restart our clock, we will allow the player to race after 4 seconds

	m_gameReady = ready;
}

//A method to setup a light, we will use this to place lights around the map to illuminate it
void PlayScreen::setUpLight(sf::Sprite& lightSprite, sf::Vector2f lightPos, sf::Texture& texture)
{
	lightSprite.setTexture(texture);
	auto tempRect = lightSprite.getGlobalBounds();
	lightSprite.setOrigin(tempRect.width / 2.0f, tempRect.height / 2.0f);
	lightSprite.setPosition(lightPos.x + 25, lightPos.y);
}

void PlayScreen::handleInput(Xbox360Controller& controller, GameState& current, GameState& previous)
{
	if (current == GameState::Play)
	{
		//If we hit start
		if(controller.getCurrent().Start && controller.getPrevious().Start == false)
		{
			current = Pause; //current gamestate is now pause
			previous = Play; //previous is now play
		}
		if (controller.getCurrent().LeftThumbClick && controller.getPrevious().LeftThumbClick == false)
		{
			m_audioP->m_soundArray[3].play();  
		}

		//handle playe rinput if the race isnt finished
		if(m_raceFinished == false)
			m_player.handleInput(controller);
	}
}

//sets up all of our animations for the start of the race
void PlayScreen::setupStartAnimation()
{
	//setting up our first second indicator
	for (int i = 0; i < 10; i++)
	{
		auto rect = sf::IntRect(30 * i, 0, 30, 114);
		m_light1Animation.addFrame(0.1f, rect);
	}
	for (int i = 10; i < 20; i++)
	{
		auto rect = sf::IntRect(30 * i, 0, 30, 114);
		m_light2Animation.addFrame(0.1f, rect);
	}

	for (int i = 20; i < 30; i++)
	{
		auto rect = sf::IntRect(30 * i, 0, 30, 114);
		m_light3Animation.addFrame(0.1f, rect);
	}
	for (int i = 30; i < 40; i++)
	{
		auto rect = sf::IntRect(30 * i, 0, 30, 114);
		m_fadeOffAnimation.addFrame(0.1f, rect);
	}

	m_animator.addAnimation("light1", m_light1Animation, sf::seconds(0.2f));
	m_animator.addAnimation("light2", m_light2Animation, sf::seconds(0.2f));
	m_animator.addAnimation("light3", m_light3Animation, sf::seconds(0.2f));
	m_animator.addAnimation("fadeOff", m_fadeOffAnimation, sf::seconds(0.2f));
}

void PlayScreen::animateStart()
{
	m_timer = m_AnimationClock.restart(); //get our time gone since last restart
	m_animator.update(m_timer); //update our animation using our timer
	m_animator.animate(m_startSprite); //animate our sprite

	if (m_animator.isPlayingAnimation() == false)
	{
		if (m_finalAnimationPlayed)
			m_canDrawStart = false;

		m_playAnimation = false;
		m_AnimationClock.restart(); //restart our clock
	}
}

void PlayScreen::playAnaimtion(std::string animationId)
{
	m_animator.stopAnimation(); //stop any animation playing
	m_AnimationClock.restart(); //restart clock
	m_playAnimation = true;
	m_animator.playAnimation(animationId); //play the animation with the id of (animationId)
}

//setting up our objects for the race screen
void PlayScreen::setLevelData(LevelData& level)
{
	m_player.setPosition(level.m_playerCar.m_position);

	for (int i = 0; i < m_aiAmount; i++)
	{
		m_aiArray[i].setPosition(level.m_AICars.at(i).m_position);

		//setting our ai's max speed and turn rate depending on their type
		if (level.m_AICars.at(i).m_type == "slow")
		{
			m_aiArray[i].setAiValues(1.55f, 0.03f);
			m_aiArray[i].setLastGridPos(sf::FloatRect(320 + (6 * 64), 320 + (16 * 64), 64, 64));
			m_aiArray[i].setVehicleColour(sf::Color(211, 84, 0, 255)); //orange
		}
		if (level.m_AICars.at(i).m_type == "slowTurner")
		{
			m_aiArray[i].setAiValues(1.5f, 0.025f);
			m_aiArray[i].setLastGridPos(sf::FloatRect(320 + (7 * 64), 320 + (17 * 64), 64, 64));
			m_aiArray[i].setVehicleColour(sf::Color(241, 196, 15, 255)); //yellow
		}
		if (level.m_AICars.at(i).m_type == "fastTurner")
		{
			m_aiArray[i].setAiValues(1.45f, 0.035f);
			m_aiArray[i].setLastGridPos(sf::FloatRect(320 + (6 * 64), 320 + (17 * 64), 64, 64));
			m_aiArray[i].setVehicleColour(sf::Color(41, 182, 246, 255)); //cyan
		}
		if (level.m_AICars.at(i).m_type == "fast")
		{
			m_aiArray[i].setAiValues(1.8f, 0.025f);
			m_aiArray[i].setLastGridPos(sf::FloatRect(320 + (5 * 64), 320 + (16 * 64), 64, 64));
			m_aiArray[i].setVehicleColour(sf::Color(103, 53, 183, 255)); //purple
		}
		if (level.m_AICars.at(i).m_type == "medium")
		{
			m_aiArray[i].setAiValues(1.7f, 0.025f);
			m_aiArray[i].setLastGridPos(sf::FloatRect(320 + (5 * 64), 320 + (17 * 64), 64, 64));
			m_aiArray[i].setVehicleColour(sf::Color(233, 30, 99, 255)); //pink
		}
	}

	m_levelRef = &level;
}

//resets our player and ai back to their starting positions
void PlayScreen::reset(LevelData& level)
{
	m_playersPos = 1;
	m_raceFinished = false;
	m_timeGoneSinceStart = 0;;
	m_playAnimation = false;
	m_firstAnimationPlayed = false;
	m_secondAnimationPlayed = false;
	m_thirdAnimationPlayed = false;
	m_finalAnimationPlayed = false;
	m_canDrawStart = false;
	m_playStartSound = false;
	m_startSprite.setTextureRect(sf::IntRect(0,0, 30, 114));
	m_endClockStarted = false;
	m_canDrawStart = true;
	
	
	m_gameReady = false;

	m_player.setPosition(level.m_playerCar.m_position);
	m_player.resetPlayer();

	for (int i = 0; i < m_aiAmount; i++)
	{
		m_aiArray[i].setPosition(level.m_AICars.at(i).m_position);

		//setting our ai's max speed and turn rate depending on their type
		if (level.m_AICars.at(i).m_type == "slow")
		{
			m_aiArray[i].setAiValues(1.55f, 0.03f);
			m_aiArray[i].setLastGridPos(sf::FloatRect(320 + (6 * 64), 320 + (16 * 64), 64, 64));
		}
		if (level.m_AICars.at(i).m_type == "slowTurner")
		{
			m_aiArray[i].setAiValues(1.5f, 0.025f);
			m_aiArray[i].setLastGridPos(sf::FloatRect(320 + (7 * 64), 320 + (17 * 64), 64, 64));
		}
		if (level.m_AICars.at(i).m_type == "fastTurner")
		{
			m_aiArray[i].setAiValues(1.45f, 0.035f);
			m_aiArray[i].setLastGridPos(sf::FloatRect(320 + (6 * 64), 320 + (17 * 64), 64, 64));
		}
		if (level.m_AICars.at(i).m_type == "fast")
		{
			m_aiArray[i].setAiValues(1.8f, 0.025f);
			m_aiArray[i].setLastGridPos(sf::FloatRect(320 + (5 * 64), 320 + (16 * 64), 64, 64));
		}
		if (level.m_AICars.at(i).m_type == "medium")
		{
			m_aiArray[i].setAiValues(1.7f, 0.025f);
			m_aiArray[i].setLastGridPos(sf::FloatRect(320 + (5 * 64), 320 + (17 * 64), 64, 64));
		}

		m_aiArray[i].resetAi();
	}
}

//Sets the apprpriate bools in each ai and player to start the race
void PlayScreen::startRace()
{
	m_player.setRaceStart(true);

	for (auto& ai : m_aiArray)
		ai.setRaceStarted(true);
}

//Checks if the ai needs to avoid any obstacles
void PlayScreen::checkAiAvoid()
{
	for (int i = 0; i < m_aiAmount; i++)
	{
		m_aiArray[i].collisionAvoidance(m_player.getPosition(), 35);
	}

	for (int i = 0; i < m_aiAmount; i++)
	{
		for (int j = 0; j < m_aiAmount; j++)
		{
			if (m_aiArray[i].getPosition() != m_aiArray[j].getPosition())
			{
				m_aiArray[i].collisionAvoidance(m_aiArray[j].getPosition(), 60);
			}
		}
	}

}

//Returns our player variable
Player& PlayScreen::getPlayer()
{
	return m_player;
}

//Returns the track
Track& PlayScreen::getTrack()
{
	return m_track;
}

//sets the properties of the race such as the amount of ai and amoutn of laps
void PlayScreen::setRaceProperties(int laps, int aiAmount)
{
	m_aiAmount = aiAmount;
	m_maxLaps = laps;

	for (auto& ai : m_aiArray)
		ai.setLaps(laps);
		

	m_hud.setMaxlaps(laps);
	m_hud.setMaxPos(aiAmount);

}

//returns the distance between two vectors
double PlayScreen::distance(sf::Vector2f v1, sf::Vector2f v2)
{
	return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

//Broken, somewhat works but doesnt always check 
void PlayScreen::checkPositions()
{
	int tempArray[6]; //we make our temporary array a size of 6 since there can be the player + 5 other ai

	//if the players checpoint has changed then update his position
	if (m_player.checkpointChanged())
	{
		bool playerAhead = false;
		int placesMoved = 0;

		for (int i = 0; i < m_aiAmount; i++)
		{
			if (m_player.getCheckpointsHit() > m_aiArray[i].getCheckPointsHit())
			{
				if (m_playersPos > 2)
					m_playersPos--;
			}
			else if (m_player.getCheckpointsHit() == m_aiArray[i].getCheckPointsHit()
				&& distance(m_player.getPosition(), m_player.getDistanceFromWaypoint()) < distance(m_aiArray[i].getPosition(), m_aiArray[i].getDistanceFromWaypoint()))
			{
				if (m_playersPos > 2)
					m_playersPos--;
			}
			else
			{
				if (m_playersPos < m_aiAmount)
					m_playersPos++;
			}
		}



		//set the checkoing pint change dvariable to false
		m_player.setCheckpointChanged(false);
	}
}
