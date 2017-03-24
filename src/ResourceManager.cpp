#include "ResourceManager.h"

/// <summary>
/// Authors: Daryl Keogh
/// Description: The resource manager is responsible for loading in any textures/fonts/sounds or videos we need.
/// Time Spent: 10 Minutes
/// </summary>

ResourceManager::ResourceManager()
{
	//try to load our resources
	try
	{
		//Load our icons
		acquireResource("garageIcon", m_garageIcon);
		acquireResource("settingsIcon", m_settingsIcon);
		acquireResource("mainMenuBg", m_menuBg);
		acquireResource("menuIcon", m_menuIcon);
		acquireResource("helpIcon", m_helpIcon);
		acquireResource("raceIcon", m_raceIcon);
		acquireResource("exitIcon", m_exitIcon);
		acquireResource("checkIcon", m_checkIcon);
		acquireResource("controller", m_controller);
		acquireResource("Bbutton", m_Bbutton);
		acquireResource("previousIcon", m_previousIcon);
		acquireResource("up", m_upIcon);
		acquireResource("down", m_downIcon);
		acquireResource("nextIcon", m_nextIcon);
		acquireResource("testCar", m_testCar);
		acquireResource("testMap", m_testMap);
		acquireResource("carSelect", m_currentCar);
		acquireResource("aButton", m_aButton);
		acquireResource("basicPaint", m_basicPaint);
		acquireResource("startButton", m_startBtn);
		acquireResource("lbIcon", m_lbIcon);
		acquireResource("rbIcon", m_rbIcon);

		//letters
		acquireResource("letterSpriteSheet", m_letters);


		//load our Lights
		acquireResource("streetLight", m_streetLight);
		acquireResource("headLight", m_headLight);


		//numbers
		acquireResource("numbersSpriteSheet", m_numbers);		 

		//Load our spritesheet
		acquireResource("buttonSheet", m_buttonSheet);
		acquireResource("sliderSheet", m_sliderSheet);
		acquireResource("sliderPosition", m_sliderPositionSheet);
		acquireResource("radioSheet", m_radioButtonSheet);
		acquireResource("upgradeSheet", m_upgradeSheet);
		acquireResource("colorSheet", m_colorSheet);
		acquireResource("startSheet", m_startSheet);


		//Load our track
		acquireResource("track", m_track);

		//Load our car sprite
		acquireResource("car", m_car);

		//Load our font
		m_fontHolder.acquire("font", m_font);

		//Load our HUD Texture
		acquireResource("hudTexture", m_hud);

		//loading in our track sprites
		for (int i = 0; i < 16; i++)
		{
			//since our tracks tetxures are numbered, we can easily load them in by creating a local loader object and create the string on the fly by converting the index to a string
			auto loader = thor::Resources::fromFile<sf::Texture>(std::string("./resources/Tracks/mapTile_" + std::to_string(i) + ".png"));

			acquireResource(std::string("trackPart" + std::to_string(i)), loader);
		}
		
	}
	catch (thor::ResourceLoadingException& e)
	{
		std::cout << e.what() << std::endl; //output error
	}
}

ResourceManager::~ResourceManager()
{
	//unload assets
}

//This method acquires our texture and then sets our texture smooth to true
void ResourceManager::acquireResource(std::string resourceId, thor::ResourceLoader<sf::Texture> textureLoader)
{
	m_textureHolder.acquire(resourceId, textureLoader);
	m_textureHolder[resourceId].setSmooth(true);
}

thor::ResourceHolder<sf::Texture, std::string>& ResourceManager::getTextureHolder()
{
	return m_textureHolder;
}

thor::ResourceHolder<sf::Font, std::string>& ResourceManager::getFontHolder()
{
	return m_fontHolder;
}