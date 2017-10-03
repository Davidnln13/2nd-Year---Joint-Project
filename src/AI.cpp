#include "AI.h"

AI::AI() :
	m_changedGrid(false),
	m_acceleration(0),
	m_avoid(0,0),
	m_checkPointsHit(0),
	m_currentLap(1),
	m_raceOver(false)
{
	m_shader.loadFromFile("./resources/Shaders/colorChangeShader.frag", sf::Shader::Fragment); //load up our fragment shader
}

/// <summary>
/// Updates our ai to determine what actions to take
/// </summary>
void AI::update(LevelData& level)
{
	if (m_raceStarted)
	{
		m_checkpointTimer = m_checkpointClock.restart(); //add our time gone since the clock was last restarted into our timer

		checkGridPosChange(); //checks for grid position change

		m_acceleration += 0.0027777777777778;
		if (m_acceleration >= m_maxAccel)
			m_acceleration = m_maxAccel;


		sf::Vector2f zeroVector(0, 0);
		m_steering = zeroVector;
		m_steering += m_avoid;
		if (m_steering == zeroVector)
			m_steering += pathFollowing(level);
		m_steering = truncate(m_steering, m_maxForce);
		m_velocity = truncate(m_velocity + m_steering, m_maxSpeed * m_acceleration);

		m_position += m_velocity;


		auto dest = atan2(-1 * m_velocity.y, -1 * m_velocity.x) / thor::Pi * 180 + 180;

		auto currentRotation = m_rotation;

		// Find the shortest way to rotate towards the target (clockwise or anti-clockwise)
		if (std::round(currentRotation - dest) == 0.0)
		{
			m_steering.x = 0;
			m_steering.y = 0;
		}
		else if ((static_cast<int>(std::round(dest - currentRotation + 360))) % 360 < 180)
		{
			// rotate clockwise
			m_rotation = static_cast<int>(m_rotation + 1) % 360;
		}
		else if ((static_cast<int>(std::round(dest - currentRotation + 360))) % 360 > 180)
		{
			m_rotation = static_cast<int>(m_rotation - 1) % 360;
		}
	}

	//Set the position of ours sprites
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_rotation);
	m_headlightSprite.setPosition(m_position);
	m_headlightSprite.setRotation(m_rotation);
}

sf::Vector2f AI::pathFollowing(LevelData& level)
{
	m_currentTargetPos = level.m_checkpoints.at(m_currentCheckpoint).m_position;

	if (distance(m_position, m_currentTargetPos) <= level.m_checkpoints.at(m_currentCheckpoint).m_radius)
	{
		m_checkpointClock.restart(); //restart our lcock since we have reached our checkpoint

		if (level.m_checkpoints.at(m_currentCheckpoint).m_type == "finishLine")
		{
			std::cout << "AI CROSSED FINISH" << std::endl;
			if(m_raceOver == false)
				m_currentLap++;
			m_currentCheckpoint = 0;
		}
		if (m_currentLap > m_maxLaps)
		{
			m_raceOver = true;
		}
		else
			m_currentCheckpoint++;

		if (m_raceOver == false)
			m_checkPointsHit++;


		m_currentTargetPos = level.m_checkpoints.at(m_currentCheckpoint).m_position;
	}
	return sf::Vector2f(m_currentTargetPos.x - m_position.x, m_currentTargetPos.y - m_position.y);
}

/// <summary>
/// Renders our ai
/// </summary>
/// <param name="window"></param>
void AI::render(sf::RenderWindow& window, sf::FloatRect& windowRectangle)
{
	//if our ai's car sprite intersects the window rectangle then draw it, otherwise, dont
	if (m_sprite.getGlobalBounds().intersects(windowRectangle))
		window.draw(m_sprite, &m_shader);
}

/// <summary>
/// Sets the colour of our vehicle as the passed over vehicle
/// </summary>
/// <param name="aColor"></param>
void AI::setVehicleColour(sf::Color aColor)
{
	//Reset our shader variables
	m_shader.setUniform("newR", 0);
	m_shader.setUniform("newG", 0);
	m_shader.setUniform("newB", 0);
	m_shader.setUniform("newA", 0);

	//Calculate our new colours
	float newR = aColor.r / 255.0;
	float newG = aColor.g / 255.0;
	float newB = aColor.b / 255.0;
	float newA = aColor.a / 255.0;

	//Set our shade runiform variables to our new calculated colour
	m_shader.setUniform("newR", newR);
	m_shader.setUniform("newG", newG);
	m_shader.setUniform("newB", newB);
	m_shader.setUniform("newA", newA);
}

void AI::checkGridPosChange()
{
	auto aiRect = sf::FloatRect(m_sprite.getGlobalBounds());

	//if we are no longer intersecting our last grid position rectangle then change our bool
	if (aiRect.intersects(m_lastPosRect) == false)
		m_changedGrid = true;
	else
		m_changedGrid = false;

}

void AI::setRaceStarted(bool start)
{
	m_raceStarted = start;
}

void AI::setAiValues(float maxSpeed, float maxTurnForce)
{
	m_maxSpeed = maxSpeed;
	m_maxForce = maxTurnForce;
}

void AI::setPosition(sf::Vector2f& pos)
{
	m_position = pos;
}

/// <summary>
/// Sets the textures for the vehicle, the car and headlight texture
/// </summary>
/// <param name="carTexture"></param>
/// <param name="headLightTexture"></param>
void AI::setTexture(sf::Texture& carTexture, sf::Texture& headLightTexture)
{
	m_sprite.setTexture(carTexture);
	auto rect = m_sprite.getTextureRect();
	m_sprite.setOrigin(rect.width / 2.0f, rect.height / 2.0f);
	m_sprite.setPosition(m_position); 

	//setting up our headlights
	m_headlightSprite.setTexture(headLightTexture);
	auto headlightRect = m_headlightSprite.getGlobalBounds();
	m_headlightSprite.setOrigin(headlightRect.left + 25, headlightRect.height / 2.0f);
	m_headlightSprite.setPosition(m_position);
}

/// <summary>
/// Returns a sprite from our vehicle
/// </summary>
/// <param name="spriteiD"></param>
/// <returns></returns>
sf::Sprite& AI::getHeadlightSprite(std::string spriteiD)
{
	return m_headlightSprite;
}

/// <summary>
/// Checking for collision avoidance on the passed over vector
/// </summary>
/// <param name="objectPos"></param>
void AI::collisionAvoidance(sf::Vector2f objectPos, int radius)
{
	sf::CircleShape target;
	target.setRadius(radius);
	auto bounds = target.getGlobalBounds();
	target.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	target.setPosition(objectPos);

	auto headingRadians = thor::toRadian(m_rotation);
	sf::Vector2f headingVector(cos(headingRadians) * MAX_SEE_AHEAD, sin(headingRadians) * MAX_SEE_AHEAD);
	m_ahead = m_position + headingVector;
	m_halfAhead = m_position + (headingVector * 0.5f);

	bool collided = lineIntersectsCircle(m_ahead, m_halfAhead, target);

	if (distance(m_position, objectPos) < 60)
	{
		m_maxAccel = 0.92f;
	}

	//if we have collided then set our avoidance vector
	if (collided)
	{
		m_avoid.x = m_ahead.x - target.getPosition().x;
		m_avoid.y = m_ahead.y - target.getPosition().y;

		if(m_avoid != sf::Vector2f(0,0))
			m_avoid = thor::unitVector(m_avoid);

		m_avoid *= MAX_AVOID_FORCE;
	}
	else //else reset our avoidance vector
		m_avoid *= 0.0f;
}

bool AI::lineIntersectsCircle(sf::Vector2f ahead, sf::Vector2f halfAhead, sf::CircleShape circle)
{
	return distance(circle.getPosition(), ahead) <= circle.getRadius() ||
		distance(circle.getPosition(), halfAhead) <= circle.getRadius();
}

//reset sany variables which could have changed throughout a race
void AI::resetAi()
{
	m_checkpointTimer = sf::seconds(0);
	m_raceOver = false;
	m_currentLap = 1;
	m_checkPointsHit = 0;
	m_currentCheckpoint = 0;
	m_acceleration = 0;
	m_avoid = sf::Vector2f(0,0);
	m_steering = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);
	m_rotation = 0;
	m_raceStarted = false;
}

void AI::setLaps(int laps)
{
	m_maxLaps = laps;
}

void AI::setVelocity(sf::Vector2f newVel)
{
	m_velocity = newVel;
}

bool AI::hasChangedGrid()
{
	return m_changedGrid;
}

void AI::setSpeedPenalty()
{
	m_maxAccel = 0.85f;
}

void AI::setLastGridPos(sf::FloatRect posRect)
{
	m_lastPosRect = posRect;
}

double AI::distance(sf::Vector2f v1, sf::Vector2f v2)
{
	return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

sf::FloatRect AI::getRectangle()
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f AI::truncate(sf::Vector2f v, float const num)
{
	float i;
	i = num / thor::length(v);
	i = i < 1.0 ? i : 1.0;
	v *= i;
	return v;
}

sf::Vector2f AI::getPosition()
{
	return m_position;
}