#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"

//Structs pertaining to the data in the YAML files
struct BackgroundData
{
	std::string m_fileName;
};

struct AICarData
{
	std::string m_type;
	sf::Vector2f m_position;
	int m_rotation;
};
struct PlayerCarData
{
	sf::Vector2f m_position;
	int m_rotation;
};
struct CheckpointData
{
	std::string m_type;
	sf::Vector2f m_position;
	float m_radius;
};
struct  LevelData
{
	BackgroundData m_background;
	std::vector<AICarData> m_AICars;
	PlayerCarData m_playerCar;
	std::vector<CheckpointData> m_checkpoints;

};
//class used to load the level
class LevelLoader
{
public:

	LevelLoader();

	static bool load(int nr, LevelData& level);
};