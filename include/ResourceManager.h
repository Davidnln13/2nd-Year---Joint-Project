#pragma once
#include "Thor\Resources.hpp" //including resource library
#include "SFML\Graphics.hpp"
#include <iostream>

/// <summary>
/// Authors: Daryl Keogh
/// Description: The resource manager is responsible for loading in any textures/fonts/sounds or videos we need.
/// Time Spent: 10 Minutes
/// </summary>
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void acquireResource(std::string resourceId, thor::ResourceLoader<sf::Texture> textureLoader);

	thor::ResourceHolder<sf::Texture, std::string>& getTextureHolder();
	thor::ResourceHolder<sf::Font, std::string>& getFontHolder();

private:
	//holds all of our textures
	thor::ResourceHolder<sf::Texture, std::string> m_textureHolder;
	//holds our font(s)
	thor::ResourceHolder<sf::Font, std::string> m_fontHolder;

	//Our font loader
	thor::ResourceLoader<sf::Font> m_font = thor::Resources::fromFile<sf::Font>("./resources/Font/TCM.TTF");

	//Our Icon loaders
	thor::ResourceLoader<sf::Texture> m_garageIcon = thor::Resources::fromFile<sf::Texture>("./resources/gui/Garage Icon.png");
	thor::ResourceLoader<sf::Texture> m_settingsIcon = thor::Resources::fromFile<sf::Texture>("./resources/gui/Settings Icon.png");
	thor::ResourceLoader<sf::Texture> m_raceIcon = thor::Resources::fromFile<sf::Texture>("./resources/gui/Race Icon.png");
	thor::ResourceLoader<sf::Texture> m_helpIcon = thor::Resources::fromFile<sf::Texture>("./resources/gui/Help Icon.png");
	thor::ResourceLoader<sf::Texture> m_menuIcon = thor::Resources::fromFile<sf::Texture>("./resources/gui/Menu Icon.png");
	thor::ResourceLoader<sf::Texture> m_exitIcon = thor::Resources::fromFile<sf::Texture>("./resources/gui/Exit Icon.png");
	thor::ResourceLoader<sf::Texture> m_menuBg = thor::Resources::fromFile<sf::Texture>("./resources/Images/menubg.jpg");
	thor::ResourceLoader<sf::Texture> m_Bbutton = thor::Resources::fromFile<sf::Texture>("./resources/Images/Bbutton.png");
	thor::ResourceLoader<sf::Texture> m_controller = thor::Resources::fromFile<sf::Texture>("./resources/Images/controller.png");
	thor::ResourceLoader<sf::Texture> m_checkIcon = thor::Resources::fromFile<sf::Texture>("./resources/gui/Check Icon.png");
	thor::ResourceLoader<sf::Texture> m_previousIcon = thor::Resources::fromFile<sf::Texture>("./resources/gui/Previous.png");
	thor::ResourceLoader<sf::Texture> m_nextIcon = thor::Resources::fromFile<sf::Texture>("./resources/gui/Next.png");
	thor::ResourceLoader<sf::Texture> m_upIcon = thor::Resources::fromFile<sf::Texture>("./resources/gui/up.png");
	thor::ResourceLoader<sf::Texture> m_downIcon = thor::Resources::fromFile<sf::Texture>("./resources/gui/down.png");
	thor::ResourceLoader<sf::Texture> m_numbers = thor::Resources::fromFile<sf::Texture>("./resources/gui/numbersSpriteSheet.png");
	thor::ResourceLoader<sf::Texture> m_testCar = thor::Resources::fromFile<sf::Texture>("./resources/gui/testCar.png");
	thor::ResourceLoader<sf::Texture> m_testMap = thor::Resources::fromFile<sf::Texture>("./resources/gui/testMap.png");
	thor::ResourceLoader<sf::Texture> m_letters = thor::Resources::fromFile<sf::Texture>("./resources/gui/letterSpriteSheet.png");
	thor::ResourceLoader<sf::Texture> m_currentCar = thor::Resources::fromFile<sf::Texture>("./resources/gui/carSelectBox.png");
	thor::ResourceLoader<sf::Texture> m_aButton = thor::Resources::fromFile<sf::Texture>("./resources/gui/A Button.png");
	thor::ResourceLoader<sf::Texture> m_basicPaint = thor::Resources::fromFile<sf::Texture>("./resources/gui/basePaint.png");
	thor::ResourceLoader<sf::Texture> m_startBtn = thor::Resources::fromFile<sf::Texture>("./resources/Images/startButton.png");
	thor::ResourceLoader<sf::Texture> m_lbIcon = thor::Resources::fromFile<sf::Texture>("./resources/gui/lb icon.png");
	thor::ResourceLoader<sf::Texture> m_rbIcon = thor::Resources::fromFile<sf::Texture>("./resources/gui/rb icon.png");

	//Our light loaders
	thor::ResourceLoader<sf::Texture> m_streetLight = thor::Resources::fromFile<sf::Texture>("./resources/Images/Street light.png");
	thor::ResourceLoader<sf::Texture> m_headLight = thor::Resources::fromFile<sf::Texture>("./resources/Images/headlights.png");

	//Our spritesheet loaders
	thor::ResourceLoader<sf::Texture> m_buttonSheet = thor::Resources::fromFile<sf::Texture>("./resources/gui/ButtonSpriteSheet.png");
	thor::ResourceLoader<sf::Texture> m_sliderSheet = thor::Resources::fromFile<sf::Texture>("./resources/gui/SliderSprite.png");
	thor::ResourceLoader<sf::Texture> m_sliderPositionSheet = thor::Resources::fromFile<sf::Texture>("./resources/gui/SliderPositionSheet.png");
	thor::ResourceLoader<sf::Texture> m_radioButtonSheet = thor::Resources::fromFile<sf::Texture>("./resources/gui/ToggleButtonSpriteSheet.png");
	thor::ResourceLoader<sf::Texture> m_upgradeSheet = thor::Resources::fromFile<sf::Texture>("./resources/gui/UpgradeSheet.png");
	thor::ResourceLoader<sf::Texture> m_colorSheet = thor::Resources::fromFile<sf::Texture>("./resources/gui/colorSheetSelected.png");
	thor::ResourceLoader<sf::Texture> m_startSheet = thor::Resources::fromFile<sf::Texture>("./resources/Images/startSheet.png");

	//temp track image
	thor::ResourceLoader<sf::Texture> m_track = thor::Resources::fromFile<sf::Texture>("./resources/Images/map.png");

	//our vehicle texture

	//our HUD texture
	thor::ResourceLoader<sf::Texture> m_hud = thor::Resources::fromFile<sf::Texture>("./resources/gui/HUDTexture.png");

	thor::ResourceLoader<sf::Texture> m_car = thor::Resources::fromFile<sf::Texture>("./resources/Images/car.png");
};