#pragma once
#include "Screen.h"
#include "Player.h"
#include "AI.h"
#include "Track.h"
#include "HUD.h"

/// <summary>
/// Our game screen. in here we will update our player and Ai objects and will hold most of the game code.
/// Authors: Daryl Keogh 
/// 
/// </summary>
class PlayScreen : public Screen
{
public:
	PlayScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio);
	~PlayScreen();

	void update(GameState& current, GameState& previous) override;
	void render(sf::RenderWindow& window, GameState& current, GameState& previous) override;
	void handleInput(Xbox360Controller& controller, GameState& current, GameState& previous) override;
	void setUpLight(sf::Sprite& lightSprite, sf::Vector2f lightPos, sf::Texture& texture);
	void setRaceProperties(int laps, int aiAmount);
	void setLevelData(LevelData& level);
	void setGameReady(bool ready);
	void checkAiAvoid();
	void animateStartIndicator();
	void animateStart();
	void startRace();
	void reset(LevelData& level);
	void checkPositions();

	//getters
	Player& getPlayer();
	Track& getTrack();
	bool& isGameReady() { return m_gameReady; }
	int getNoOfLaps() { return m_maxLaps; }
	
	//sets up our start animation
	void setupStartAnimation();
	void playAnaimtion(std::string animationId);
private:
	double distance(sf::Vector2f v1, sf::Vector2f v2);

	bool m_raceFinished;
	int m_maxLaps;
	int m_playersPos; //the player sposition in the race, the player starts ahead of all ai so this value will be 1 automatically
	//our ai array, we will only use the amount our player chooses at the pre-race screen
	AI m_aiArray[5];

	//Our player object
	Player m_player;

	Track m_track;

	sf::Sprite darkSprite; //we will draw our dark layer onto this sprite
	sf::RenderTexture lightTexture; //our render texture will be used to draw light sonto the screen
	sf::Sprite m_streetLights[11]; //our street lights, we will use these to draw street lights around the map

	HUD m_hud; //our hud object

	int m_aiAmount; //the amount of ai we will use for the track

	bool m_gameReady; //bool to hold if the game is ready to start or not

	LevelData* m_levelRef; //a reference to our level data

	sf::Clock m_dayNightClock; //our day and night cycle clock, this will be used to change the time of day in our game
	sf::Clock m_raceClock; //holds the time gone sinc ethe beginning of the race
	sf::Clock m_endClock; //holds the time gone since the end of the race
	bool m_endClockStarted; //bool to hold if we have restarted our end clock or not
	float m_currentColor; //the alpha our black layer will start off at
	float m_timeGoneSinceEnd; //holds the time gone since the end of the race
	bool changeToNight;

	sf::FloatRect m_windowRect; //our windows rectangle, we will use this rectangle to cull objects in the game, such as ai a and lights

	bool m_playStartSound;

	//Animation objects
	//this our holder for our animations
	thor::Animator<sf::Sprite, std::string> m_animator;
	//This is our animation 
	thor::FrameAnimation m_light1Animation;
	thor::FrameAnimation m_light2Animation;
	thor::FrameAnimation m_light3Animation;
	thor::FrameAnimation m_fadeOffAnimation;
	sf::Sprite m_startSprite;
	sf::Clock m_AnimationClock;
	sf::Time m_timer;
	float m_timeGoneSinceStart;
	bool m_playAnimation;
	bool m_firstAnimationPlayed;
	bool m_secondAnimationPlayed;
	bool m_thirdAnimationPlayed;
	bool m_finalAnimationPlayed;
	bool m_canDrawStart;

	Label m_hudArtistLabel;
	Label m_hudSongLabel;
};