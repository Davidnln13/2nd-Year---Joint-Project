#pragma once
#include "Label.h"
#include <Thor\Resources.hpp>

enum GameState;
class HUD
{
public:
	HUD(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder);
	~HUD();
	void update(GameState& current, int playersLap, int playersPos);
	void render(sf::RenderWindow& window, GameState& current);
	void setMaxlaps(int val);
	void setMaxPos(int val);
	void resetTimer(); //resets the timer on the hud
private:
	int m_maxLaps = 0;
	int m_maxPos;

	Label m_lapLabel;
	Label m_positionLabel;
	Label m_timeLabel;
	Label* m_lblArray[3];
	int m_maxLbl = 3;
	int m_currentLap;
	int m_previousLap;

	std::stringstream m_ssLap;
	std::stringstream m_ssPos;
	std::stringstream m_ssTime;
	sf::String m_lapString;
	sf::String m_posString;
	sf::String m_timeString;
	sf::Clock m_clock;
	double m_timePassed;
	int m_minutes;
	int m_seconds;
	float m_miliSecs;
	bool startCounting = false;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

