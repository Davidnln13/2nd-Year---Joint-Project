#pragma once
#include "SFML\Graphics.hpp"
#include "Thor\Resources.hpp"
#include "Thor\Math.hpp"
#include "LevelLoader.h"


class Xbox360Controller;

///Class: Player
///Author: Daryl keogh
///Description: The player class is what the user will control during the race screen. The playe rclass controls a sprite (car sprite)
///which is made up of 2 imaginary wheels, front and back, this gives us a more realistic look and feel.
///The player can control the vehicle/player by using the left thumbstick to steer, Right trigger to accelerate and Left trigger to decelerate/reverse.
///They may also turn on and off their headlights by clicking the right analog stick in. Holding the B button will use the brake and caus ethe car to come to a stop quickly.
///Time Spent: 3+ hours
class Player
{
public:
	Player(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder);
	void update(LevelData& level); //Updates the player
	void render(sf::RenderWindow& window); //Draws the player to the screen
	void handleInput(Xbox360Controller& controller);


	void increaseSpeed(float const& triggerAmount);
	void decreaseSpeed(float const& triggerAmount);
	void decreaseRotation(float const& stickAmount);
	void increaseRotation(float const& stickAmount);
	void brake();
	void checkGridChange(); //checks if we have moved to a new grid position
	void getWaypointPos(LevelData& level);

	//setters
	void setVehicleColour(sf::Color aColor); //sets the colour of our vehicle
	void setTexture(sf::Texture& carTexture, sf::Texture& headLightTexture); 	//sets the texture of our vehicle
	void setAcceleration(bool aBool);
	void resetSteerAngle();
	void setIsAcceleration(bool aBool);
	void giveSpeedPenalty(float val);
	void setLastGridPos(sf::Vector2f position);
	void setPosition(sf::Vector2f position);
	void setRaceStart(bool start);
	void resetPlayer();

	//Our upgrade methods
	void setAccelerationLevel(int level);
	void setTopSpeedLevel(int level);
	void setBrakeLevel(int level);
	void setSteeringLevel(int level);
	void setCash(int newCashAmount);
	void setCheckpointChanged(bool changed);
	void setLapRecorded() { m_lapRecorded = false; }

	//getters
	float getFriction();
	float getHeading() { return m_carHeading; }
	float getCheckPointTime() { return m_checkPointTimer.asSeconds(); }
	float getLapTime() { return m_lapTimer.asMilliseconds(); }
	float getOverallTime() { return m_overAllTime; }

	void setOverallTime() {	m_overAllTime = 0;};
	
	sf::FloatRect getRectangle();// returns our rectangle of our vehicle
	sf::Vector2f& getPosition();
	sf::Sprite getSprite(std::string spriteid);
	sf::Vector2f getLastGridPos();
	sf::Vector2f getCurrentGridPos();
	sf::Vector2f getDistanceFromWaypoint() { return m_currentWaypointPos; }
	sf::Time getlapTimer() { return m_lapTimer; }
	int getAccelerationLevel();
	int getTopSpeedLevel();
	int getBrakeLevel();
	int getSteeringLevel();
	int getCheckpointsHit() { return m_checkpointsHit; }
	int getCash();
	int getLap() { return m_currentLap; }
	int getBestlapTime() { return m_bestLaptime; }
	bool checkpointChanged() { return m_checkPointChanged; }
	bool lapPassed() { return m_lapRecorded; }
private:
	double distance(sf::Vector2f v1, sf::Vector2f v2);
	bool m_checkPointChanged; //bool to hold if our checkpoint we are aiming for has changed or not
	bool m_crossedFinish;
	bool m_lapRecorded; 
	int m_currentCheckPoint;
	int m_checkpointsHit;
	int m_currentLap;
	sf::Vector2f m_currentWaypointPos;
	float m_bestLaptime = 250; //our best laptime, this value will be replaced with the shorted laptime
	float m_overAllTime; //holds the overall time it took the player to complete the race

	bool m_raceStarted; //bool to hold if the race started or not

	int m_cash = 50; //the players cash, this will start at 50

	bool m_canDrive; //bool to hold if our car can accelerate or not
	bool m_useHeadlights; //bool to determine if we are using our headlights or not

	int m_accelerationlevel; //holds the current acceleration level of our car
	int m_topSpeedLevel;//holds teh current acceleration level of our car
	int m_steeringLevel; //holds the current steering level of our car
	int m_brakesLevel; //holds the current brakes level of our car
	int m_colourNumber; //holds the id of the colour of the car
	double m_turnRate; //the turn rate of our car, this is determine by our steering level
	float m_speed; //the current speed of our vehicle
	double m_maxSpeed; //the max speed of our car, this is determined by our engine level 
	double m_acceleration; //the acceleration our car, this is determined by our engine level 
	double m_brakePower; //the speed our car brakes at (this wil determine how quickly we can slow down)

	float m_speedPercent;
	float m_turnSpeed;

	float m_friction; //friction

	float m_steerAngle; //the current rotation of our vehicle
	float m_carHeading;
	float wheelbase = 12.5f;
	float m_steerChange;

	sf::Vector2f m_position;
	sf::Vector2f m_currentGridPos;
	sf::Vector2f m_lastGridPos;
	sf::Sprite m_sprite; //Our car sprite
	sf::Sprite m_headlightSprite; //our headlight sprite
	sf::Sprite m_emptySprite;

	sf::Clock m_raceClock; //our race clock will hold the overall time it took the player to race around each lap
	sf::Time m_raceTimer;
	sf::Clock m_lapClock; //a clock which holds the time it took the player to complete a lap
	sf::Time m_lapTimer;

	sf::Clock m_checkPointClock; //our clock will hold th eitmer gone since we last hit a checkpoint
	sf::Time m_checkPointTimer;

	const float DT = 10.0; //our milliseconds per update

	bool m_isAccelerating;
	sf::Shader m_shader; //Our shader, this allows us to recoulour our vehicle

	float static const DEG_TO_RAD;
	float static const RAD_TO_DEG;

	//Our upgrade consts, we will use these when upgrading th eplayer
	float const ACCEL_UPGRADE = 0.05f; //our acceleration increases by 0.5f per engine level
	float const STEER_UPGRADE = 0.025f; //our steering increases by 0.025f per steering level (this makes the handling smoother)
	float const MAXSPEED_UPGRADE = 2.5f; // our max speed increases by 2.5f per engine level
	float const BRAKE_UPGRADE = 0.00025f; //our brake power increases by 0.00025f per level

	//Our base value consts
	float const BASE_ACCEL = 0.45f;
	float const BASE_STEER = 0.55;
	float const BASE_MAXSPEED = 150;
	float const BASE_BRAKE = 0.0025f;
};