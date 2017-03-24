#include "OptionsScreen.h"
#include "ScreenManager.h"
#include "Audio.h"

/// <summary>
/// Our options screen will display sliders and radio buttons that the user can adjust using the 
/// controller, they can toggle on and off music and sound effects, and can also adjust their volumes
/// Authors: Daryl Keogh, David Nolan
/// Total Time David: 21/03/2017 12.30 - 6 -> 5.5hrs
/// </summary>
OptionsScreen::OptionsScreen(thor::ResourceHolder<sf::Texture, std::string>& resourceHolder, thor::ResourceHolder<sf::Font, std::string>& fontHolder, Audio& audio) :
	Screen(audio),
	m_menuIndex(0),
	m_fxSlider("Fx Volume", sf::Vector2f(640, 134)),
	m_musicSlider("Music Volume", sf::Vector2f(640, 329)),
	m_fxRadio("Fx Toggle", sf::Vector2f(489, 479)),
	m_musicRadio("Music Toggle", sf::Vector2f(489, 637)),
	m_label("Back", 50)
{
	//Adding our sliders and buttons to our widget array
	m_widgets[0] = &m_fxSlider;
	m_widgets[1] = &m_musicSlider;
	m_widgets[2] = &m_fxRadio;
	m_widgets[3] = &m_musicRadio;

	//b button
	m_bSprite.setTexture(resourceHolder["Bbutton"]);
	m_bSprite.setPosition(1120, 660);
	m_bSprite.setScale(0.023f, 0.023f);

	m_label.setFont(fontHolder["font"]);
	m_label.setGuiPos(sf::Vector2f(1220, 665));

	//Passes over our textures from our texture holder
	m_fxSlider.setTexture(resourceHolder["sliderSheet"], resourceHolder["sliderPosition"],  fontHolder["font"]);
	m_musicSlider.setTexture(resourceHolder["sliderSheet"], resourceHolder["sliderPosition"], fontHolder["font"]);
	m_fxRadio.setTexture(resourceHolder["radioSheet"], resourceHolder["checkIcon"], fontHolder["font"]);
	m_musicRadio.setTexture(resourceHolder["radioSheet"], resourceHolder["checkIcon"], fontHolder["font"]);
	//setting our bg sprite
	m_sprite.setTexture(resourceHolder["mainMenuBg"]);
	
	
}

OptionsScreen::~OptionsScreen()
{

}

void OptionsScreen::update(GameState& current, GameState& previous)
{
	if (m_setMusicOnce == false)
	{
		//m_audioPointer->setPlayingOffset(sf::seconds(1));
		for (int i = 0; i < 10; i++)
		{
			m_audioP->m_menuMusic[i].setVolume(50);
		}
		
		m_setMusicOnce = true;
	}
	 
	if(current == GameState::Options)
	{
		//Updates our widgets
		for (auto& widget : m_widgets)
			widget->update();
	}
	
	
	 
}
void OptionsScreen::render(sf::RenderWindow& window, GameState& current, GameState& previous)
{
	if (current == GameState::Options)
	{
		window.draw(m_sprite); //draw our bg sprite

		//Render our widgets
		for (auto& widget : m_widgets)
			widget->render(window);

		//render our label and b button sprite
		m_label.render(window);
		window.draw(m_bSprite);

	}
}

void OptionsScreen::handleInput(Xbox360Controller& controller, GameState& current, GameState& previous)
{
	if (current == GameState::Options)
	{
		//used to save the volume for when we toggle the radiobutton
		if (volumeSave < 10)
		{
			volumeSave = 0;
		}
		if (volumeSave > 100)
		{
			volumeSave = 100;
		}
		//change m_hearMusic if volume is 0
		if (volumeSave == 0 )
		{
			
			flipMusic();
		}
		if (audioVolumeSave < 10)
			audioVolumeSave = 0;
		if (audioVolumeSave > 100)
			audioVolumeSave = 100;
		if (audioVolumeSave == 0)
			flipAudio();
		 
			
		 
		int newIndex = m_menuIndex; //assigning our index to local temporary index

		m_widgets[m_menuIndex]->handleInput(controller); //handle inpot on the indexed widget

		if (controller.getCurrent().B && controller.getPrevious().B == false)
		{
			m_audioP->m_soundArray[0].play();
			auto tempState = current;
			current = previous;
			previous = tempState;
			m_handledInput = true;
		}
		if (controller.getCurrent().DpadRight && controller.getPrevious().DpadRight== false
			|| controller.getCurrent().LeftThumbStickRight && controller.getPrevious().LeftThumbStickRight== false)
		{
			m_audioP->m_soundArray[7].play();
			if (newIndex == 0)
			{
				if(m_hearAudio == true || audioToggle == true)
				{
					for (int i = 0; i < 8; i++)
					{
						m_audioP->m_soundArray[i].setVolume(m_audioP->m_soundArray[i].getVolume() + 10);
					}
				}
				for (int i = 0; i < 8; i++)
				{
					if (m_audioP->m_soundArray[i].getVolume() > 100)
					{
						m_audioP->m_soundArray[i].setVolume(100);

					}
				}
				audioVolumeSave += 10;
			}
			if (newIndex == 1)
			{
				
				
				//add 10 to the volume
				if (m_hearMusic == true || toggle == true)
				{
					for (int i = 0; i < 10; i++)
					{
						m_audioP->m_menuMusic[i].setVolume(m_audioP->m_menuMusic[i].getVolume() + 10);
					}
				}
				//add 10 to the value we will use to reset the volume
					volumeSave += 10;
					//volume cant be above 100
					for (int i = 0; i < 10; i++)
					{
						if (m_audioP->m_menuMusic[i].getVolume() > 100)
						{
							m_audioP->m_menuMusic[i].setVolume(100);

						}
					}
				
		}
			
			 
		}
		if (controller.getCurrent().DpadLeft&& controller.getPrevious().DpadLeft == false
			|| controller.getCurrent().LeftThumbStickLeft&& controller.getPrevious().LeftThumbStickLeft== false)
		{
			m_audioP->m_soundArray[7].play();

			if (newIndex == 0)
			{
				if (m_hearAudio == true || audioToggle == true)
				{
					for (int i = 0; i < 8; i++)
					{
						m_audioP->m_soundArray[i].setVolume(m_audioP->m_soundArray[i].getVolume() - 10);
					}
				}
				system("CLS");
				audioVolumeSave -= 10;
			}
			//1 is the music slider
			if (newIndex == 1)
			{
				if (m_hearMusic == true || toggle == true)
				{
					for (int i = 0; i < 10; i++)
					{
						// -10 volume
						m_audioP->m_menuMusic[i].setVolume(m_audioP->m_menuMusic[i].getVolume() - 10);
					}
					system("CLS");
				}
					volumeSave -= 10;
					
				
				
			}
		}
		//If we navigate down/up through the buttons using the dpad or left thumbstick
		if (controller.getCurrent().DpadDown && controller.getPrevious().DpadDown == false
			|| controller.getCurrent().LeftThumbStickDown && controller.getPrevious().LeftThumbStickDown == false)
		{
			m_audioP->m_soundArray[7].play();
			//decrease our index
			newIndex++;
		}
		if (controller.getCurrent().DpadUp && controller.getPrevious().DpadUp == false
			|| controller.getCurrent().LeftThumbStickUp && controller.getPrevious().LeftThumbStickUp == false)
		{
			m_audioP->m_soundArray[7].play();
			//decrease our index
			newIndex--;
		}
		if (controller.getCurrent().A && controller.getPrevious().A == false)
		{
			if (newIndex == 2)
			{
				m_audioP->m_soundArray[0].play();
			}
			if (newIndex == 2)
			{
				flipAudioToggle();
				flipAudio();
			}
			if (newIndex == 3)
			{
				flipToggle();
				m_audioP->m_soundArray[0].play();
				
				flipMusic();
				 
				 
			}
		}
		
		//if our local index has changed form our original index
		 
		if (newIndex != m_menuIndex)
		{
			if (newIndex == 4)
				newIndex = 0;
			if (newIndex == -1)
				newIndex = 3;

			m_widgets[m_menuIndex]->loseFocus();
			m_menuIndex = newIndex; //assign our new index to our menu index
			m_widgets[m_menuIndex]->getFocus();
		}
	}
	else
		m_handledInput = false;
}
void OptionsScreen::flipMusic()
{//if toggle is true then we can play music
	if (toggle == true)
	{
		m_hearMusic = true;
		for (int i = 0; i < 10; i++)
		{
			m_audioP->m_menuMusic[i].setVolume(volumeSave);
		}
		
	}
	if (toggle == false)
	{
		m_hearMusic = false;
		for (int i = 0; i < 10; i++)
		{
			m_audioP->m_menuMusic[i].setVolume(0);

		}
	}
}
void OptionsScreen::flipAudio()
{
	if (audioToggle == true)
	{
		m_hearAudio = true;
		for (int i = 0; i < 8; i++)
		{
			m_audioP->m_soundArray[i].setVolume(audioVolumeSave);
		}
	}
	if (audioToggle == false)
	{
		m_hearAudio = false;
		for (int i = 0; i < 8; i++)
		{
			m_audioP->m_soundArray[i].setVolume(0);

		}
	}
}
void OptionsScreen::flipToggle()
{//switch toggle only with radio button
	if (toggle == false)
	{
		toggle = true;
		
	}
		
	else 
	{
		toggle = false;
	}
		
}
void OptionsScreen::flipAudioToggle()
{
	if (audioToggle == false)
	{
		audioToggle = true;
	}
	else
	{
		audioToggle = false;
	}
}