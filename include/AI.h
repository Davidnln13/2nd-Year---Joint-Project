#pragma once
#include "Thor\Vectors.hpp"
#include "SFML\Graphics.hpp"
#include "LevelLoader.h"

/// <summary>
/// Author: Daryl Keogh
/// Date: 20/03/2017
/// Description: The ai will control a vehicle in which they will use to race around the track against the player
/// and/or other Ai.
/// Time Spent: N/A
/// </summary>
class AI
{
public:
	AI();

	void update(LevelData& level);
	void render(sf::RenderWindow& window, sf::FloatRect& windowRectangle);
	sf::Vector2f pathFollowing(LevelData& level);
	bool lineIntersectsCircle(sf::Vector2f ahead, sf::Vector2f halfAhead, sf::CircleShape circle);
	void collisionAvoidance(sf::Vector2f objectPos, int radius);
	void resetAi();


	//setters
	void setVehicleColour(sf::Color aColor);
	void setTexture(sf::Texture& carTexture, sf::Texture& headLightTexture);
	void setPosition(sf::Vector2f& position);
	void setSpeedPenalty();
	void setAiValues(float maxSpeed, float maxTurnForce); //sets our ai's max speed and turn force, this will allow us to create slightly different ai
	void checkGridPosChange(); //checks if our grid position has changed
	void setLastGridPos(sf::FloatRect posRect); //sets our last grid position rectangle
	void setRaceStarted(bool start);
	void setLaps(int laps);
	void setVelocity(sf::Vector2f newVel);

	//Getters
	sf::Sprite& getHeadlightSprite(std::string spriteiD);
	sf::FloatRect getRectangle();
	bool hasChangedGrid(); //returns if we have changed grid position or not
	sf::Vector2f getPosition();
	sf::Vector2f getvelocity() { return m_velocity; }
	sf::Vector2f getDistanceFromWaypoint() { return m_currentTargetPos; }
	float getHeading() { return m_rotation; }
	int getCheckPointsHit() { return m_checkPointsHit; }
	float getCheckPointTime() { return m_checkpointTimer.asSeconds(); }
	int getLap() { return m_currentLap; }

private:
	double distance(sf::Vector2f v1, sf::Vector2f v2);
	sf::Vector2f truncate(sf::Vector2f v, float const num);

	bool m_raceOver; //bool to hold if the race is over or not
	int m_currentLap; //the curren tlap the ai is on
	int m_maxLaps; //the max amount of laps the ai will take
	int m_checkPointsHit; //hold sthe amount of checkpoints we have hit
	bool m_crossedLine;
	bool m_raceStarted; //bool to show if the race has starte dyet or not
	bool m_changedGrid;
	bool m_canIncreaseLap;
	float m_acceleration;
	sf::Sprite m_sprite;
	sf::Sprite m_headlightSprite;

	float m_rotation; //the rotation of the ai
	sf::Vector2f m_position; //the ais current position
	sf::Vector2f m_velocity; //the ai's velocity
	sf::Vector2f m_steering; //the ais steering force
	sf::Vector2f m_currentTargetPos; //the current target the ai is aiming for
	sf::Vector2f m_ahead; //our ahead vector, it will be used to determine if we are gonna hit an obstacle or not
	sf::Vector2f m_halfAhead;
	sf::Vector2f m_avoid; //our avoid vector, we will add this to the ai's steering if they are trying to avoid an obstacle
	sf::FloatRect m_lastPosRect; //holds the rectangle we were last intersecting

	//ai behaviour variables
	int m_currentCheckpoint; //the current checkpoint our ai is on

	float m_maxSpeed = 1.7f; //our max speed, the higher, the faste rthe ai will go
	float m_maxForce = 0.03f; //our max steering force, the higher the number the easier the ai will turn
	float m_maxAccel = 1.0f; //the max value our acceleration can reach

	sf::Shader m_shader; //Our shader, this allows us to recoulour our vehicle

	sf::Clock m_checkpointClock; //we will use this clock to hold how long has gone since they hit a checkpoint
	sf::Time m_checkpointTimer; //will hold the time gone since the clock has been restarted

	const float MAX_SEE_AHEAD = 50.0f;
	const float MAX_AVOID_FORCE = 50.0f;
};