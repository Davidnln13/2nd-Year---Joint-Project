#include "Player.h"
#include "Xbox360Controller.h"

//Static varibles
float const Player::DEG_TO_RAD = thor::Pi / 180.0f;
float const Player::RAD_TO_DEG = 180.0f / thor::Pi;

///Class: Player
///Author: Daryl keogh
///Description: The player class is what the user will control during the race screen. The playe rclass controls a sprite (car sprite)
///which is made up of 2 imaginary wheels, front and back, this gives us a more realistic look and feel.
///The player can control the vehicle/player by using the left thumbstick to steer, Right trigger to accelerate and Left trigger to decelerate/reverse.
///They may also turn on and off their headlights by clicking the right analog stick in. Holding the B button will use the brake and caus ethe car to come to a stop quickly.
///Time Spent: 3+ hours
Player::Player(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder) : 
	m_useHeadlights(true),
	m_speed(0),
	m_maxSpeed(150),
	m_isAccelerating(false),
	m_steerAngle(0),
	m_friction(.005f),
	m_speedPercent(0.0f),
	m_acceleration(0.45f),
	m_carHeading(0),
	m_turnRate(0.55f),
	m_steerChange(5.0f),
	m_brakePower(0.0025f),
	m_currentCheckPoint(0),
	m_checkpointsHit(0),
	m_currentLap(1),
	m_overAllTime(0)
{
	//pass over our texture for our vehicle
	setTexture(resourceHolder["car"], resourceHolder["headLight"]);
	m_shader.loadFromFile("./resources/Shaders/colorChangeShader.frag", sf::Shader::Fragment);
}

//handles input from the user to control our vehicle object
void Player::handleInput(Xbox360Controller& controller)
{
	bool stickHeld = false;

	if (controller.getCurrent().RT) //if RT is held down
	{
		setIsAcceleration(true);
		increaseSpeed(-controller.getTriggerValue());
	}
	else
		setIsAcceleration(false);
	if (controller.getCurrent().LT)
	{
		decreaseSpeed(controller.getTriggerValue());
	}

	//if the user is holding B, then brake
	if (controller.getCurrent().B)
	{
		brake();
	}
	if (controller.getCurrent().LeftThumbStickLeft)
	{
		decreaseRotation(-controller.getStickValue());
		stickHeld = true;
	}
	 
	else if (controller.getCurrent().LeftThumbStickRight)
	{
		increaseRotation(controller.getStickValue());
		stickHeld = true;
	}

	//turning on and off our headlights
	if (controller.getCurrent().RightThumbClick && controller.getPrevious().RightThumbClick == false)
	{
		if (m_useHeadlights)
			m_useHeadlights = false;
		else
			m_useHeadlights = true;
	}
	

	if (stickHeld == false)
	{
		resetSteerAngle();
	}
}

void Player::update(LevelData& level)
{	
	if(m_raceStarted)
	{
		m_raceTimer += m_raceClock.restart();
		m_lapTimer += m_lapClock.restart(); //assigns the time gone since the lap clock was restarted and add it to our timer
		m_overAllTime = m_raceTimer.asSeconds();
	}


	//get waypoint position and check if player is in distance to increase the waypoint
	getWaypointPos(level);

	m_checkPointTimer = m_checkPointClock.restart(); //get our time elapsed sinc ethe clock was started and put it into our timer variable

	checkGridChange();

	float speedDifference = (m_maxSpeed - m_speed) / m_maxSpeed;//gets the percentage of our speed left that we can acomplish
	speedDifference += m_turnRate; //we add our turnRate to our speedDifference so we can turn faster at low speeds, and turn slower at higher speeds

	//if we arent holding RT and our speed is greater than 0
	if (m_isAccelerating == false && m_speed > 0)
		m_speed -= (m_speed * m_friction);

	//create two wheels, front and back, give them thei rposition
	sf::Vector2f frontWheel = m_position + wheelbase * sf::Vector2f(cos(m_carHeading * DEG_TO_RAD), sin(m_carHeading * DEG_TO_RAD));
	sf::Vector2f backWheel = m_position - wheelbase * sf::Vector2f(cos(m_carHeading * DEG_TO_RAD), sin(m_carHeading * DEG_TO_RAD));

	//Get our ne wposition of our wheels
	backWheel += m_speed * (DT / 1000) * sf::Vector2f(cos(m_carHeading * DEG_TO_RAD), sin(m_carHeading * DEG_TO_RAD));
	frontWheel += m_speed * (DT / 1000) * sf::Vector2f(cos((m_carHeading + (m_steerAngle * speedDifference)) * DEG_TO_RAD), sin((m_carHeading + (m_steerAngle * speedDifference)) * DEG_TO_RAD));

	//gets the position of our vehicle
	m_position = (frontWheel + backWheel) / 2.0f;
	//Calculate sthe rotation/heading of the vehicle
	m_carHeading = atan2(frontWheel.y - backWheel.y, frontWheel.x - backWheel.x) * RAD_TO_DEG;

	//Setting our sprites position and rotation of our sprites
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_carHeading);
	m_headlightSprite.setPosition(m_position);
	m_headlightSprite.setRotation(m_carHeading);
}

void Player::checkGridChange()
{
	//we multiply by 64 becuase each grid is 64 x64
	if (m_position.x > m_currentGridPos.x * 64)
		m_currentGridPos.x++;
	if (m_position.x < m_currentGridPos.x * 64)
		m_currentGridPos.x--;
	if (m_position.y > m_currentGridPos.y * 64)
		m_currentGridPos.y++;
	if (m_position.y < m_currentGridPos.y * 64)
		m_currentGridPos.y--;
}

void Player::render(sf::RenderWindow& window)
{
	//draws our car sprite with our shader
	window.draw(m_sprite, &m_shader);
}

//When this method is called the user will come to stop if the B button is continously held down
void Player::brake()
{
	if (m_speed > 0)
	{
		m_speed -= (m_brakePower * m_speed) + m_friction;
	}
}

//resets our variables that could have changed throught a race, this allows us to restart a race
void Player::resetPlayer()
{
	m_raceClock.restart();
	m_lapTimer = sf::seconds(0);
	m_checkPointTimer = sf::seconds(0);
	m_currentLap = 1;
	m_currentCheckPoint = 0;
	m_checkpointsHit = 0;
	m_speed = 0;
	m_acceleration = 0;
	m_speedPercent = 0;
	m_carHeading = 0;
	m_useHeadlights = true;
	m_raceStarted = false;
}

//Increases the players speed
void Player::increaseSpeed(float const & triggerAmount)
{
	float sensitivityPercent = triggerAmount / 100.0f;

	//gets our acceleration by multiplying our Base acceleration by our acceleration level + 1 and then by our trigger sensitivy
	m_acceleration = (BASE_ACCEL * (m_accelerationlevel + 1)) * sensitivityPercent;

	if (m_speed < m_maxSpeed && m_raceStarted) //if the race has started we can increase our speed as long as our spee dis below max speed
	{
		m_speed += (m_acceleration * sensitivityPercent) - m_friction; //add our acceleration amount 
	}
}

//decreases our speed due to the LT being held
void Player::decreaseSpeed(float const& triggerAmount)
{
	float sensitivityPercent = triggerAmount / 100.0f;

	//gets our acceleration by multiplying our Base acceleration by our acceleration level + 1 and then by our trigger sensitivy
	m_acceleration = (BASE_ACCEL * (m_accelerationlevel + 1)) * sensitivityPercent;

	if (m_speed > -(m_maxSpeed / 2.0f) && m_raceStarted) //we can reverse upto a max of half of our max speed while the race has started
	{
		m_speed -= (m_acceleration * sensitivityPercent) + m_friction;
	}
}
//Increases the rotation of our player
void Player::increaseRotation(float const& stickAmount)
{
	float stickPercent = stickAmount / 100.0f;

	m_steerAngle += ((m_steerChange * stickPercent));
	if (m_steerAngle >= 15)
	{
		m_steerAngle = 15;
	}

}

//Decreases the rotation we want to face at (facing left)
void Player::decreaseRotation(float const& stickAmount)
{
	//get the percentage of how much our analog stick is moved by and divid eit by 100
	float stickPercent = stickAmount / 100.0f;

	m_steerAngle -= ((m_steerChange * stickPercent)); //change our steering angle 
	if (m_steerAngle <= -15) //if our angle has gone past the max angle then set the angle to the max angle
	{
		m_steerAngle = -15;
	}
}

//Sets the tetxure of our vehicle
//It also sets the origin of our sprite along with its position.
void Player::setTexture(sf::Texture& carTexture, sf::Texture& headLightTexture)
{
	m_sprite.setTexture(carTexture);
	auto rect = m_sprite.getTextureRect();
	m_sprite.setOrigin(rect.width - 20, rect.height / 2.0f);
	m_currentGridPos.x = 7;
	m_currentGridPos.y = 17;
	m_sprite.setPosition(m_position); //put our vehicle in the centre of the screen

									  //setting up our headlights
	m_headlightSprite.setTexture(headLightTexture);
	auto headlightRect = m_headlightSprite.getGlobalBounds();
	m_headlightSprite.setOrigin(headlightRect.left + 30, headlightRect.height / 2.0f);
	m_headlightSprite.setPosition(m_position);
}

//Gets the next waypoint in the waypoints list in the level object
void Player::getWaypointPos(LevelData& level)
{
	m_currentWaypointPos = level.m_checkpoints.at(m_currentCheckPoint).m_position;

	//if the distance between the player and the waypoint is smaller than the waypoinst radius
	if (distance(m_position, m_currentWaypointPos) <= level.m_checkpoints.at(m_currentCheckPoint).m_radius)
	{
		m_checkPointClock.restart(); //restart our checkpoint timer

		m_checkpointsHit++; 

		m_checkPointChanged = true;

		//if the waypoints type is finishline then increment our laps and save our bets laptime if it has been beaten
		if (level.m_checkpoints.at(m_currentCheckPoint).m_type == "finishLine")
		{
			float lapTime = m_lapTimer.asSeconds();

			m_lapTimer = sf::seconds(0);

			m_lapClock.restart();

			if (lapTime < m_bestLaptime)
				m_bestLaptime = lapTime;

			m_lapRecorded = true;

			m_currentLap++;
			m_currentCheckPoint = 0; //reset our checkpoints
		}
		else
		{
			m_currentCheckPoint++;
		}


		m_currentWaypointPos = level.m_checkpoints.at(m_currentCheckPoint).m_position;
	}
}

//returns the distance between two vectors
double Player::distance(sf::Vector2f v1, sf::Vector2f v2)
{
	return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

void Player::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}

void Player::setRaceStart(bool start)
{
	m_lapClock.restart(); //restart our lap clock when the race begins
	m_raceStarted = start;
}


void Player::setAcceleration(bool aBool)
{
	m_isAccelerating = aBool;
}

void Player::resetSteerAngle()
{
	m_steerAngle = 0.0f;
}

void Player::setIsAcceleration(bool aBool)
{
	m_isAccelerating = aBool;
}

void Player::setCash(int newCashAmount)
{
	m_cash = newCashAmount;
}

//setting our players vehicle levels
void Player::setAccelerationLevel(int level)
{
	m_accelerationlevel = level;
	m_acceleration = BASE_ACCEL + (ACCEL_UPGRADE * level);
}
void Player::setTopSpeedLevel(int level)
{
	m_topSpeedLevel = level;
	m_maxSpeed = BASE_MAXSPEED + (MAXSPEED_UPGRADE * level);
}
void Player::setBrakeLevel(int level)
{
	m_brakesLevel = level;
	m_brakePower = BASE_BRAKE + (BRAKE_UPGRADE * level);
}
void Player::setSteeringLevel(int level)
{
	m_steeringLevel = level;
	m_turnRate = BASE_STEER + (STEER_UPGRADE * level);
}

int Player::getAccelerationLevel()
{
	return m_accelerationlevel;
}

int Player::getBrakeLevel()
{
	return m_brakesLevel;
}

int Player::getTopSpeedLevel()
{
	return m_topSpeedLevel;
}

int Player::getSteeringLevel()
{
	return m_steeringLevel;
}

sf::Vector2f& Player::getPosition()
{
	return m_position;
}

int Player::getCash()
{
	return m_cash;
}

void Player::setCheckpointChanged(bool changed)
{
	m_checkPointChanged = changed;
}

//returns a sprite depending on what the string is
sf::Sprite Player::getSprite(std::string spriteid)
{
	if (spriteid == "car")
		return m_sprite;
	else if (m_useHeadlights)
		return m_headlightSprite;
	else
		return m_emptySprite;
}

//Sets the parameters of our shader so we can recolour the vehicle on the fly
//We us ethe RBG & A value sof the sf::Color parameter passed over to it
void Player::setVehicleColour(sf::Color color)
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

//gets the rectangle of our vehicle
sf::FloatRect Player::getRectangle()
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Player::getLastGridPos()
{
	return m_lastGridPos;
}

sf::Vector2f Player::getCurrentGridPos()
{
	return m_currentGridPos;
}

float Player::getFriction()
{
	return m_friction;
}

void Player::giveSpeedPenalty(float val)
{
	m_speed *= val;
}

void Player::setLastGridPos(sf::Vector2f position)
{
	m_lastGridPos = position;
	m_currentGridPos = m_lastGridPos;
}
 