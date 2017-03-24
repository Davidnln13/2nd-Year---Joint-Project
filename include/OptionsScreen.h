#pragma once
#include "Screen.h"
#include "Slider.h"
#include "RadioButton.h"

class Audio;


/// <summary>
/// Our options screen will display sliders and radio buttons that the user can adjust using the 
/// controller, they can toggle on and off music and sound effects, and can also adjust their volumes
/// Authors: Daryl Keogh 
/// </summary>
class OptionsScreen : public Screen
{
public:
	OptionsScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio);
	~OptionsScreen();

	void update(GameState& current, GameState& previous) override;
	void render(sf::RenderWindow& window, GameState& current, GameState& previous) override;
	void handleInput(Xbox360Controller& controller, GameState& current, GameState& previous) override;

	void flipMusic();
	void flipToggle();
	void flipAudioToggle();
	void flipAudio();
private:
	int m_menuIndex;//index to hold which button we are currently highlighting

	sf::Sprite m_sprite; //our bg sprite for our screen

	//Our widget array, will hold our sliders and radio buttons
	Widget* m_widgets[4];

	//Our sliders
	Slider m_fxSlider;
	Slider m_musicSlider;
	
	//Our radio buttons
	RadioButton m_fxRadio;
	RadioButton m_musicRadio;

	//Our Label
	Label m_label;
	sf::Sprite m_bSprite; //back button sprite
	bool m_hearMusic = true;
	bool m_hearAudio = true;
	bool m_setMusicOnce = false;
	int volumeSave = 50;
	int audioVolumeSave = 50;
	bool toggle = true;
	bool audioToggle = true;
	int saveNunm;
};