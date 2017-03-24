#pragma once
#include "Screen.h"

/// <summary>
/// Our preracescreen will be used to allow the user to select the vehicle, track, amount of laps and amount of Ai they would like to play against.
/// Authors: Daryl Keogh, David Nolan
/// </summary>
/// 
/// 
/// Name: David Nolan
/// Time worked: 15/03/2017 all day
///				 16/03/2017 9-4
/// Total Time: approx 15hrs
class PreRaceScreen : public Screen
{
public:
	PreRaceScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio);
	~PreRaceScreen();

	void update(GameState& current, GameState& previous) override;
	void render(sf::RenderWindow& window, GameState& current, GameState& previous) override;
	void handleInput(Xbox360Controller& controller, GameState& current, GameState& previous) override;
	void animateSideButtons();

	//getters
	int getAiAmount() { return saveAiNum; }
	int getLapAmount() { return saveLapsNum; }
	int getTrackNum() { return saveTrackNum; }

private:
	//bool to make our radio buttons different than the ones used for toggling 
	bool preRaceBool = true;
	//widget array holds 12 radiobuttons and one button
	Widget* m_widgets[13];
	 
	bool m_canScroll; //bool to hold if we can scroll through the menu or not
	sf::Clock m_scrollClock; //holds the time gone since the player has pressed down/up

	//button to play the game after settings confirmed
	Button m_play;

	//RadioButtons for the number selectors
	RadioButton m_selectCarPrevious;
	RadioButton m_selectCarNext;
	RadioButton m_selectTrackPrevious;
	RadioButton m_selectTrackNext;
	RadioButton m_selectLapsPrevious;
	RadioButton m_selectLapsNext;
	RadioButton m_selectAiAmountPrevious;
	RadioButton m_selectAiAmountNext;

	RadioButton m_carNum;
	RadioButton m_trackNum;
	RadioButton m_lapsNum;
	RadioButton m_aiNum;

	//labels to write what the buttons do to the screen
	Label m_label;
	Label m_selectCar;
	Label m_selectTrack;
	Label m_selectLaps;
	Label m_selectAiNo;

	//sprites  background and b button
	sf::Sprite m_bButtonSprite;
	sf::Sprite m_bgSprite;
	//scrolls options


	//ints to be able to scroll through the menu
	int m_menuIndex;
	int newIndex;
	//ints to lose focus on previous focused radiobuttons
	int x;
	int y;
	int z;
	 //ints to save the number of these selected for the match
	int saveCarNum = 1;
	int saveTrackNum = 1;
	int saveLapsNum = 1;
	int saveAiNum = 1;
	 //used to make us start selected at the top 
	bool once = false;
	//used to make the first previous the top buttons
	bool checkOnce = false;

	//sprites to draw images on the right
	sf::Sprite m_trackSprite;
	sf::Sprite m_carSprite;
	 

};