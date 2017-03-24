#include "HUD.h"
#include <sstream>
#include <iostream>
#include "ScreenManager.h"
HUD::HUD(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder) :
	m_lapLabel(m_lapString, 40),
	m_positionLabel(m_posString, 20),
	m_timeLabel(m_timeString, 20)

{
	//Setting each label to a position in a label array to make drawing and setting the same variables easier
	m_lblArray[0] = &m_lapLabel;
	m_lblArray[1] = &m_positionLabel;
	m_lblArray[2] = &m_timeLabel;

	//Seeing the font and alpha values for each label
	for (int i = 0; i < m_maxLbl; i++)
	{
		m_lblArray[i]->setFont(fontHolder["font"]);
		m_lblArray[i]->setAlpha(255);
	}

	m_texture = resourceHolder["hudTexture"];
	m_sprite.setTexture(m_texture);

	auto color = m_sprite.getColor();
	color.a = 191;
	m_sprite.setColor(color);

	/*m_sprite.setPosition(480, 1195);*/
}

HUD::~HUD()
{
}

void HUD::update(GameState& current, int playersLap, int playersPos)
{
	if (current == GameState::Play)
	{
		sf::Time timer = m_clock.restart();
		int milTrunct = 0;
		//Managing the timer.
		m_miliSecs += timer.asMilliseconds();
		//Adding 1 to the m_milisecond variable every milisecond.
		if (m_miliSecs > 999)
		{
			m_miliSecs = 0;

			m_seconds++;

			//if the amount of seconds passed is over a minute then reset the seconds and add one to the minutes.
			if (m_seconds > 59)
			{
				m_seconds = 0;
				m_minutes++;
			}

		}

		milTrunct = m_miliSecs / 10.0f;

		//Setting the string stream and changing the string of the label to the time;
		m_ssTime.str("");
		m_ssTime.precision(1);
		if (m_seconds < 10)
		{
			m_ssTime << "Lap-Time: " << m_minutes << ":" << "0" << m_seconds << ":" << milTrunct;
		}
		else
		{
			m_ssTime << "Lap-Time: " << m_minutes << ":" << m_seconds << ":" << milTrunct;

		}

		m_timeString = m_ssTime.str();
		m_lblArray[2]->setString(m_timeString);

		m_ssLap.str("");

		m_ssLap << "Lap:" << playersLap << "/" << m_maxLaps;
		m_lapString = m_ssLap.str();
		m_lblArray[0]->setString(m_lapString);

		m_ssPos.str("");
		m_ssPos << "Position: " << playersPos << "/" << m_maxPos;
		m_posString = m_ssPos.str();
		m_lblArray[1]->setString(m_posString);
	}
}

void HUD::render(sf::RenderWindow& window, GameState& current)
{
	if (current == GameState::Play)
	{
		auto view = window.getView();

		//Setting each label to a different posiiton is the viewport. This makes sure the labels will stay on the screen.
		m_lblArray[0]->setGuiPos(view.getCenter().x - 150, view.getCenter().y + 130);
		m_lblArray[1]->setGuiPos(view.getCenter().x + 190, view.getCenter().y + 150);
		m_lblArray[2]->setGuiPos(view.getCenter().x + +30, view.getCenter().y + 150);

		m_sprite.setPosition(view.getCenter().x - 320, view.getCenter().y - 180);

		window.draw(m_sprite);

		//Drawing all the labels to the string
		for (int i = 0; i < m_maxLbl; i++)
		{
			m_lblArray[i]->render(window);
		}
	}
}

void HUD::setMaxlaps(int val)
{
	m_maxLaps = val;
}

void HUD::setMaxPos(int val)
{
	m_maxPos = val + 1;
}

//Resets our milliseconds, minutes and second svariables
void HUD::resetTimer()
{
	m_clock.restart();
	m_miliSecs = 0;
	m_seconds = 0;
	m_minutes = 0;
}

