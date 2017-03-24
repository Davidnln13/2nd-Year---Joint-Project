#include "HighscoreScreen.h"
#include "ScreenManager.h"

HighscoreScreen::HighscoreScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio) :
	Screen(audio),
	m_backLabel("Back", 50),
	m_highscore("Highscore", 50),
	m_identifiers("  Name			Best Lap Time		Overall Time		Number Of Laps	",30),
	m_minutesSeconds("   Seconds	     		 Seconds"),	
	//initialises all pos's
	posXName(200),
	posYName(150),
	posXLaps(425),
	posYLaps(150),
	posXOverall(675),
	posYOverall(150),
	posXLapNo(950),
	posYLapNo(150)
{
	m_bgSprite.setTexture(resourceHolder["mainMenuBg"]);
	m_bgSprite.setPosition(0, 0);
	m_backLabel.setFont(fontHolder["font"]);
	m_backLabel.setGuiPos(sf::Vector2f(1220, 665));
	//b button
	m_bSprite.setTexture(resourceHolder["Bbutton"]);
	m_bSprite.setPosition(1120, 660);
	m_bSprite.setScale(0.023f, 0.023f);

	//each title
	m_identifiers.setGuiPos(640, 100);
	m_identifiers.setFont(fontHolder["font"]);

	m_highscore.setGuiPos(sf::Vector2f(640, 0));
	m_highscore.setFont(fontHolder["font"]);


	m_minutesSeconds.setGuiPos(560, 150);
	m_minutesSeconds.setFont(fontHolder["font"]);

	for (int i = 0; i < 10; i++)
	{
		//sets each arrays font and text size
		m_highscoreLabelsName[i].setFont(fontHolder["font"]);
		m_highscoreLabelsName[i].setTextSize(30);

		m_highscoreLabelsLap[i].setFont(fontHolder["font"]);
		m_highscoreLabelsLap[i].setTextSize(30);

		m_highscoreLabelsOverall[i].setFont(fontHolder["font"]);
		m_highscoreLabelsOverall[i].setTextSize(30);

		m_highscoreLabelsLapNo[i].setFont(fontHolder["font"]);
		m_highscoreLabelsLapNo[i].setTextSize(30);

		 
	}

	
}

HighscoreScreen::~HighscoreScreen()
{

}

void HighscoreScreen::update(GameState& current, GameState& previous)
{
	if (current == GameState::Highscore)
	{
		if (once == false)
		{
			updateFile("", 1000, 10, 10);
			once = true;
		}
		
		
	}
	if (current != GameState::Highscore)
	{
		once = false;
		posYName = 150;
		posYLapNo = 150;
		posYLaps = 150;
		posYOverall = 150; 
	}
		
}

void HighscoreScreen::render(sf::RenderWindow& window, GameState& current, GameState& previous)
{
	if (current == GameState::Highscore)
	{
		window.draw(m_bgSprite);
		window.draw(m_bSprite);

		m_backLabel.render(window);
		m_highscore.render(window);

		m_identifiers.render(window);
		for (int i = 0; i < 10; i++)
		{
			//draws each array 
			m_highscoreLabelsName[i].render(window);
			m_highscoreLabelsLap[i].render(window);
			m_highscoreLabelsOverall[i].render(window);
			m_highscoreLabelsLapNo[i].render(window);
		}
		m_minutesSeconds.render(window);

	}
}
void HighscoreScreen::handleInput(Xbox360Controller& controller, GameState& current, GameState& previous)
{
	if (current == GameState::Highscore)
	{
		
		if (controller.getCurrent().B && controller.getPrevious().B == false)
		{
			
			auto tempState = current;
			current = previous;
			previous = tempState;
			m_audioP->m_soundArray[0].play();
		}

		m_handledInput = true; //sets our bool to true so we can stop handling input on the screen
	}
	else
		m_handledInput = false;
}

void HighscoreScreen::updateFile(std::string playerName, float playerBestLapTime, float playerOverallTime, int playerLapNumber)
{	
	//if 10 values are read break
	int tenValuesRead = 0;
	//input to file and output to file 
	std::fstream readingHighscoreFile;
	std::ofstream writingHighscoreFile;
	//file location
	readingHighscoreFile.open("./resources/File/Highscores.txt");

	bool nameNext = false;
	bool bestLapTimeNext = false;
	bool bestOverallTimeNext = false;
	bool numberOfLapsNext = false;
	//reading
	for (std::string line; std::getline(readingHighscoreFile, line);)
	{
		if (tenValuesRead == 11)
		{
			break;
		}


		if (nameNext)
		{ 
			//reads the line if its after name adds it to the array
			m_names[tenValuesRead] = line;
			nameNext = false;
		}
		if (bestLapTimeNext)
		{
			//same but its a double
			double toDouble = atof(line.c_str());
			
			m_bestLapTimes[tenValuesRead] = toDouble;
			bestLapTimeNext = false;
		}
		if (bestOverallTimeNext)
		{
			 //same
			float toDouble = atof(line.c_str());
			toDouble = roundf(toDouble * 100) / 100;

			m_overallTimes[tenValuesRead] = toDouble;
			bestOverallTimeNext = false;
		}
		if (numberOfLapsNext)
		{
			
			int changeValueToInt = atoi(line.c_str());
			float toFloat = changeValueToInt;
			m_numberOfLaps[tenValuesRead] = toFloat;
			//increases past 10 then break
			tenValuesRead++;
			numberOfLapsNext = false;
		}
		if (line == "Name")
			nameNext = true;
		if (line == "Best Laptime")
			bestLapTimeNext = true;
		if (line == "Overall Time")
			bestOverallTimeNext = true;
		if (line == "Number Of Laps")
			numberOfLapsNext = true;
		
		
		
	}
	

	readingHighscoreFile.close();
	//updating with player
	for (int i = 0; i < 10; i++)
	{
		if (m_bestLapTimes[i] > playerBestLapTime)
		{
			std::string tempNameArray[11];
			float tempLapArray[11];
			float tempOverallArray[11];
			int tempLapNoArray[11];
			for (int j = i; j < 10; j++)
			{
				tempNameArray[j+1] = m_names[j];
				tempLapArray[j+1] = m_bestLapTimes[j];
				tempOverallArray[j+1] = m_overallTimes[j];
				tempLapNoArray[j+1] = m_numberOfLaps[j];
				
				m_names[j] = tempNameArray[j];
				m_bestLapTimes[j] = tempLapArray[j];
				m_overallTimes[j] = tempOverallArray[j];
				m_numberOfLaps[j] = tempLapNoArray[j];



			}
			m_names[i] = playerName;
			m_bestLapTimes[i] = playerBestLapTime;
			m_overallTimes[i] = playerOverallTime;
			m_numberOfLaps[i] = playerLapNumber;
			break;
			
		}
	}













	writingHighscoreFile.open("./resources/File/Highscores.txt");
	//writing to screen
	for (int i = 0; i < 10; i++)
	{

		
		//sets the floats to two decimal places
		sstream[i] << std::setprecision(3) << m_bestLapTimes[i];
		
		convertBestTime[i] = sstream[i].str();
		sstream[i].str("");
	
		sstream2[i] << std::setprecision(3) << m_overallTimes[i];
		convertOverallTime[i] = sstream2[i].str();
		sstream2[i].str("");

		
		//four strings so screen is not distorted
		std::string one;
		std::string two;
		std::string three;
		std::string four;
			
		one = m_names[i];
		two = convertBestTime[i];
		three = convertOverallTime[i];
		four = std::to_string(m_numberOfLaps[i]);
	 
		//set the pos and string of each array
		m_highscoreLabelsName[i].setGuiPos(posXName, posYName += 50);
		m_highscoreLabelsLap[i].setGuiPos(posXLaps, posYLaps += 50);
		m_highscoreLabelsOverall[i].setGuiPos(posXOverall, posYOverall += 50);
		m_highscoreLabelsLapNo[i].setGuiPos(posXLapNo, posYLapNo += 50);
			 
		 
		
		m_highscoreLabelsName[i].setString(one);

		
		m_highscoreLabelsLap[i].setString(two);

		
		m_highscoreLabelsOverall[i].setString(three);

		
		m_highscoreLabelsLapNo[i].setString(four);

		 
	}
	//writing to file
	for (int i = 0; i <10; i++)
	{
		//writes all to file
		writingHighscoreFile << "Name" << std::endl;
		writingHighscoreFile << m_names[i] << std::endl;
		writingHighscoreFile << "Best Laptime" << std::endl;
		writingHighscoreFile << m_bestLapTimes[i] << std::endl;
		writingHighscoreFile << "Overall Time" << std::endl;
		writingHighscoreFile << m_overallTimes[i] << std::endl;
		writingHighscoreFile << "Number Of Laps" << std::endl;
		writingHighscoreFile << m_numberOfLaps[i] << std::endl;
		writingHighscoreFile << std::endl;
		writingHighscoreFile << "...";
		writingHighscoreFile << std::endl;
		writingHighscoreFile << std::endl;
	}
	writingHighscoreFile.close();


}
