#pragma once
#include "Screen.h"
#include "Label.h"
/// <summary>
/// Our postracescreen will be used to display the users best lap time and overral time taken on the track.
/// if the use rhas broken a best overall time or best laptime they will be asked to enter their name so 
/// that they can be added to the top 10 highscore table.
/// Authors: Daryl Keogh 
/// </summary>
/// 
/// /// Name: David Nolan
/// Time worked:  
///				 
/// Total Time: 
class PostRaceScreen : public Screen
{
public:
	PostRaceScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio);
	~PostRaceScreen();

	void update(GameState& current, GameState& previous) override;
	void render(sf::RenderWindow& window, GameState& current, GameState& previous) override;
	void handleInput(Xbox360Controller& controller, GameState& current, GameState& previous) override;
	//animates the buttons on top and bottom of the selected button without selecting them
	void animateSideButtons();

	std::string getName() { return m_name; }
private:
	//all labels for the post race
	Label m_raceOver;
	Label m_totalTime;
	Label m_bestLap;
	Label m_cashEarned;
	Label m_congratulations;
	Label m_newHighscore;
	Label m_enterName;
	Label m_confirm;
	//array to hold labels
	Label* m_labels[8];
	//makes the radiobuttons different to the originals the same as pre race
	bool m_postRaceBool = true;
	 
	//slow scrolling
	bool m_canScroll; //bool to hold if we can scroll through the menu or not
	sf::Clock m_scrollClock; //holds the time gone since the player has pressed down/up

	//radiobuttons  
	RadioButton m_firstLetter;
	RadioButton m_secondLetter;
	RadioButton m_thirdLetter;
	RadioButton m_fourthLetter;
	RadioButton m_upFirst;
	RadioButton m_downFirst;
	RadioButton m_upSecond;
	RadioButton m_downSecond;
	RadioButton m_upThird;
	RadioButton m_downThird;
	RadioButton m_upFourth;
	RadioButton m_downFourth;

	//array to hold radiobuttons
	Widget* m_radiobuttons[12];
	//sprite background 
	sf::Sprite m_bgSprite;

	//ints to be able to scroll through the menu
	int m_menuIndex;
	int newIndex;
	//used to make us start selected at the top 
	bool once = false;
	//used to make the first previous the top buttons
	bool checkOnce = false;
	//ints to lose focus on previous focused radiobuttons
	int m_x;
	int m_y;
	int m_z;

	//bool to only display text if it is a highscore
	bool isHighscore = true;
	//used to switch between the array
	int m_nameInput[4];
	
	//string array to save name
	std::string m_alphabet[27] = { "A", "B", "C", "D" , "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "" };
	//final name 
	std::string m_name = "";
};