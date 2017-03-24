#include "LevelLoader.h"

//Read through the YAML File and find the background name, assign it to the correct variable
void operator >> (const YAML::Node& backgroundNode, BackgroundData& background)
{
	background.m_fileName = backgroundNode["file"].as<std::string>();
}
//Read through the YAML file and find the X & Y components of position and the rotation and assign them to the correct variables.
void operator >> (const YAML::Node& aiNode, AICarData& ai)
{
	ai.m_type = aiNode["type"].as<std::string>();
	ai.m_position.x = aiNode["position"]["x"].as<float>();
	ai.m_position.y = aiNode["position"]["y"].as<float>();
	ai.m_rotation = aiNode["rotation"].as<float>();
}

void operator >> (const YAML::Node& checkpointNode, CheckpointData& checkpoint)
{
	checkpoint.m_type = checkpointNode["type"].as<std::string>();
	checkpoint.m_position.x = checkpointNode["position"]["x"].as<float>();
	checkpoint.m_position.y = checkpointNode["position"]["y"].as<float>();
	checkpoint.m_radius = checkpointNode["radius"].as<float>();
}
//Read through the YAML file and assign the players position and rotation to the correct variables.
void operator >> (const YAML::Node& player, PlayerCarData& playerCar)
{
	playerCar.m_position.x = player["position"]["x"].as<float>();
	playerCar.m_position.y = player["position"]["y"].as<float>();
	playerCar.m_rotation = player["rotation"].as<float>();
} 

void operator >> (const  YAML::Node& levelNode, LevelData& level)
{
	levelNode["background"] >> level.m_background;

	levelNode["player"] >> level.m_playerCar;

	const YAML::Node& aiNode = levelNode["ai"].as<YAML::Node>();
	for (unsigned i = 0; i < aiNode.size(); i++)
	{
		AICarData ai;
		aiNode[i] >> ai;
		level.m_AICars.push_back(ai);
	}
	const YAML::Node& checkpointNode = levelNode["checkpoint"].as<YAML::Node>();
	for (unsigned i = 0; i < checkpointNode.size(); i++)
	{
		CheckpointData checkpoint;
		checkpointNode[i] >> checkpoint;
		level.m_checkpoints.push_back(checkpoint);
	}
}

LevelLoader::LevelLoader()
{
}
//Used to load the specific YAML file depending on the level
bool LevelLoader::load(int nr, LevelData& level)
{
	std::stringstream ss;
	ss << "./resources/Levels/";
	ss << "level";
	ss << nr;
	ss << ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(ss.str());
		if (baseNode.IsNull())
		{
			std::string message("file: " + ss.str() + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> level;
	}
	catch (YAML::ParserException& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}
