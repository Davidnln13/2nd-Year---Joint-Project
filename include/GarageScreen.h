#pragma once
#include "Screen.h"
#include "Slider.h"
#include "Paint.h"

class Player;

/// <summary>
/// Authors: Daryl Keogh
/// Description: The garage screen is used for upgrading the players vehicle. The player can change the part of the vehicle they would like to upgrade
/// by pressing either the Right or Left bumpers on the xbox controller. They can adjust the level of upgrades using the dpad or left thumbstick. 
/// When in the colour/paint menu the user can select a paint by pressing A, if the user presse sthe start button to confirm the purchase, that paint job will
/// be applied to the users car and will be seen during the race screen.
/// Date: 21/03/2017
/// Time Spent: 4-5 hours
/// </summary>
class GarageScreen : public Screen
{
public:
	GarageScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Player& player, Audio& audio);
	~GarageScreen();

	void update(GameState& current, GameState& previous) override;
	void render(sf::RenderWindow& window, GameState& current, GameState& previous) override;
	void handleInput(Xbox360Controller& controller, GameState& current, GameState& previous) override;
	void focusSlider(std::string sliderName);
	int getCost(int sliderLevel, int playerLevel, const int UpgradePrice); //calculate sthe cost of an upgrade if there is one
	void applyUpgrades(int sliderLevel, int playerLevel, std::string part); //applie sthe purchases upgrades to the player
	void resetSliders(); //method used to reset our sliders levels
	void setCost();
	void setPaintAlphas();
	void setColour(sf::Color color);

private:
	bool m_sliderSelectedFirst; //bool to select a slider when we first enter the garage
	int m_currentCost; //holds the current cost of the selecte dupgrades

	sf::Sprite m_rbSprite; //our right bumper icon
	sf::Sprite m_lbSprite; //our left bumper icon
	sf::Sprite m_sprite; //our bg sprite
	sf::Sprite m_carBoxSprite;
	sf::Sprite m_carSprite; //the sprite of our players vehicle
	sf::Sprite m_startButtonSprite; //the start button sprite, to visually show the user how to confirm a purchase
	sf::Sprite m_aBtnSprite; //is used to show the user how they select a colour

	//Our sliders 
	Slider* m_sliders[4]; //this will hold all of our sliders
	Slider* m_engineUpgrades[2]; //we have two sliders for our engine
	Slider m_accelerationlevel;
	Slider m_topSpeedLevel;
	int m_engineIndex; //holds the index of our engine

	//Our brake slider
	Slider m_brakeLevel;

	//our steering level
	Slider m_handlingLevel;

	//Our labels, we will draw certain sliders depending on which sliders are in view
	Label* m_labelArray[4]; //our array of pointers so we can easily index labels
	Label m_engineLabel;
	Label m_brakeLabel;
	Label m_steeringLabel;
	Label m_colorLabel;
	int m_labelIndex;

	//These labels will show information to the user, such as their vehicle, cash and cost of their chosen upgrades
	Label m_vehicleLabel;
	Label m_cashLabel;
	Label m_costLabel;
	Label m_confirmLabel;
	Label m_selectLabel;

	//Our cost variables, these will be used for the prices of our upgrades
	int const ACCEL_PRICE = 35;
	int const TOP_SPEED_PRICE = 55;
	int const HANDLING_PRICE = 30;
	int const BRAKE_PRICE = 25;
	int const PAINT_PRICE = 15;

	Player& m_playerRef; //reference to our player, we will need this to apply upgrades and subtract cash from the player
 
 
	Label m_backLabel; //label for displaying the option to go back while in the menu
	sf::Sprite m_bSprite; //the B button sprite
 
	sf::Shader m_shader; //our shader object, we will use this to recolour the car sprite while selecting a colour

	//Our paint objects
	Paint m_blue;
	Paint m_red;
	Paint m_black;
	Paint m_white;
	Paint m_orange;
	Paint m_purple;
	Paint* m_paintArray[6]; //our paint array
	int m_paintIndex;
 
};