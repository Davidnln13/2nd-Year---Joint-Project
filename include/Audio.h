#pragma once
#include "SFML\Audio.hpp"

enum GameState;
class Xbox360Controller;


/*
Author: David Nolan
Time Worked: 21/03/2017 12.30 - 6 -> 5.5hrs
*/

class Audio 
{
public:
	Audio();
	sf::Music& getSong() { return m_menuMusic[musicIndexer]; };
	void update(Xbox360Controller& controller, GameState& current);
	void handleInput(Xbox360Controller& controller, GameState& current, GameState& previous);
	sf::Music m_menuMusic[10];
	sf::SoundBuffer m_soundBuffer[8];
	sf::Sound m_soundArray[8];
	int musicIndexer = 9;
private:
	//title music
	bool m_playFirstSong = false;
	bool m_songOver = false;
	bool m_startedMoving = false;
	
};
