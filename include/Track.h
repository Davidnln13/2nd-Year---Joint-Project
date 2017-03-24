#pragma once
#include <iostream>
#include <Player.h>
#include <AI.h>
#include <SFML\Graphics.hpp>
#include <Thor/Resources.hpp>
#include "HUD.h"


//class for the different tracks in our game
class Track
{
public:
	Track(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder);

	void update(Player& player, HUD& hud);

	void render(sf::RenderWindow& window, sf::FloatRect& windowRectangle);


	void checkCollision(Player& player, HUD& hud); //Checks if the player is in any grids apart from the road tiles
	void checkCollision(AI& ai); //Checks if the ai is in any grids apart from the road tiles

	//Getters
	sf::Sprite& getSprite();

	//setters
	void setTrack(int trackNum); //Sets the current track using the trackNumber
private:
	int m_playerCollisionType; //holds the type of grid the player has collided with
	int trackSelected;

	sf::Sprite m_trackSprites[16]; //our track is made up of 16 tiles
	sf::Sprite m_sprite;

	sf::FloatRect m_textureRects[16];

	//our grid for our first track, these values need to change depending on how great we want our collision detection
	int m_grid1[20][20] =
	{
		{ 2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2 }, //give each row all 0 values, we will replace these values with different numbers which correspond to different parts of the track
		{ 2,1,0,0,0,0,0,0,0,0,1,2,2,1,1,1,1,1,2,2 },
		{ 2,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,2 },
		{ 2,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,2 },
		{ 2,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,2 },
		{ 2,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,2 },
		{ 2,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,2 },
		{ 2,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,2 },
		{ 2,1,0,0,1,1,0,0,0,1,1,0,0,0,1,1,3,3,1,2 },
		{ 2,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,2 },
		{ 2,1,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,1,2 },
		{ 2,1,0,0,1,2,2,2,2,2,2,2,2,1,1,1,0,0,1,2 },
		{ 2,1,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,1,2 },
		{ 2,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,2 },
		{ 2,1,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,2 },
		{ 2,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,2 },
		{ 2,1,0,0,0,0,0,1,2,2,2,1,1,0,0,0,0,0,1,2 },
		{ 2,1,1,0,0,0,0,1,2,2,2,2,1,0,0,0,0,1,1,2 },
		{ 2,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,2 },
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	};

	const int RECTANGLE_HEIGHT = 1280.0 / 20.0; //20 is the amount of squares going accross and down our screen(our grid essentially)
	const int RECTANGLE_WIDTH = 1280.0 / 20.0;
};