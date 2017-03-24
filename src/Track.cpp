#include "Track.h"
#include <iostream>

Track::Track(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder) :
	m_playerCollisionType(0), //0 is the track, 1 and 2 are off road
	m_sprite(resourceHolder["track"])
{
	//loading in all of our tracks sprites
	for (int i = 0; i < 16; i++)
	{
		m_trackSprites[i].setTexture(resourceHolder[std::string("trackPart" + std::to_string(i))]);
		auto rect = m_trackSprites[i].getGlobalBounds();
		m_trackSprites[i].setOrigin(rect.width / 2.0f, rect.height / 2.0f);

		//positioning our track tiles
		if (i < 4)
		{
			m_textureRects[i] = sf::FloatRect(0 + (480 * i), 0, 480, 480);
			m_trackSprites[i].setPosition(240 + (480 * i), 240);
		}
			
		else if (i > 3 && i < 8)
		{
			m_textureRects[i] = sf::FloatRect(0 + (480 * (i - 4)), 480, 480, 480);
			m_trackSprites[i].setPosition(240 + (480 * (i - 4)), 720);
		}
			
		else if (i > 7 && i < 12)
		{
			m_textureRects[i] = sf::FloatRect(0 + (480 * (i - 8)), 960, 480, 480);
			m_trackSprites[i].setPosition(240 + (480 * (i - 8)), 1200);
		}
			
		else
		{
			m_textureRects[i] = sf::FloatRect(0 + (480 * (i - 12)), 1440, 480, 480);
			m_trackSprites[i].setPosition(240 + (480 * (i - 12)), 1680);
		}
			
	}

}

void Track::update(Player& player, HUD& hud)
{
	if(player.getCurrentGridPos() != player.getLastGridPos())
		checkCollision(player, hud);

	//Give a speed penalty to the player depending on where they are on the track
	if (m_playerCollisionType == 1)
		player.giveSpeedPenalty(.992f);
	if(m_playerCollisionType == 2)
		player.giveSpeedPenalty(.99f);
	if (m_playerCollisionType == 3)
		player.giveSpeedPenalty(.98f);
}

void Track::render(sf::RenderWindow& window, sf::FloatRect& windowRectangle)
{
	//draw our track
	for (int i = 0; i < 16; i++)
	{
		//if the window rectangle intersects any track rectangles, draw the track at the index i
		if (windowRectangle.intersects(m_textureRects[i]))
		{
			window.draw(m_trackSprites[i]);
		}
	}
}

//Could probably pass over a player object to have acces to its methods?
void Track::checkCollision(Player& player, HUD& hud)
{
	bool breakOut = false;

	//loop through our rows
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (player.getRectangle().intersects(sf::FloatRect(320 +(RECTANGLE_WIDTH * i), 320 + (RECTANGLE_HEIGHT * j), RECTANGLE_WIDTH, RECTANGLE_HEIGHT)))
			{
				breakOut = true; //make our local bool true
				player.setLastGridPos(sf::Vector2f(i, j)); //set our players grid pos
				if (m_grid1[i][j] == 0)
				{
					m_playerCollisionType = 0;
					break;
				}
				if (m_grid1[i][j] == 1)
				{
					m_playerCollisionType = 1;
					break;
				}
				else if (m_grid1[i][j] == 2)
				{
					m_playerCollisionType = 2;
					break;
				}
				else if (m_grid1[i][j] == 3)
				{

				}
				else
				{
					m_playerCollisionType = 3;
					break;
				}
			}
		}
		//if our local bool is true then break out of the for loop
		if (breakOut)
		{
			break;
		}
	}
}

void Track::checkCollision(AI& ai)
{
	if (ai.hasChangedGrid())
	{
		bool breakOut = false;

		//loop through our rows
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				auto intersected = sf::FloatRect(320 + (RECTANGLE_WIDTH * i), 320 + (RECTANGLE_HEIGHT * j), RECTANGLE_WIDTH, RECTANGLE_HEIGHT);
				if (ai.getRectangle().intersects(intersected))
				{
					breakOut = true;
					if (m_grid1[i][j] == 1)
					{
						ai.setLastGridPos(intersected);
						ai.setSpeedPenalty();
						break;
					}
					if (m_grid1[i][j] == 0)
					{
						ai.setLastGridPos(intersected);
						break;
					}
				}
			}

			if (breakOut)
			{
				break;
			}
		}
	}
}

sf::Sprite& Track::getSprite()
{
	return m_sprite;
}


//Set our grid values depending on the passed over track number
void Track::setTrack(int trackNum)
{

}