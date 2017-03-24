#include "Xbox360Controller.h"

Xbox360Controller::Xbox360Controller()
{
}

void Xbox360Controller::update()
{
	//Updates connected controller
	sf::Joystick::update();
}

void Xbox360Controller::handleInput()
{
	m_previousPadState = m_currentPadState; //set the previous state as the current
	m_currentPadState = m_defaultPadState; //Sets our current state to the default state (setting all bools to false)

	//Get the position of our dpad axis : PovY & PovX
	float povY = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY);
	float povX = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);

	//gets the position of our left thumbstick
	m_stickValue = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
	float axisY = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);

	m_triggerAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z);

	//asigning our bools to our current gamepadstate: Chekcing face Buttons
	m_currentPadState.A = sf::Joystick::isButtonPressed(0, 0);
	m_currentPadState.B = sf::Joystick::isButtonPressed(0, 1);
	m_currentPadState.X = sf::Joystick::isButtonPressed(0, 2);
	m_currentPadState.Y = sf::Joystick::isButtonPressed(0, 3);

	m_currentPadState.LB = sf::Joystick::isButtonPressed(0, 4);
	m_currentPadState.RB = sf::Joystick::isButtonPressed(0, 5);

	m_currentPadState.RightThumbClick = sf::Joystick::isButtonPressed(0, 9);
	m_currentPadState.LeftThumbClick = sf::Joystick::isButtonPressed(0, 8);

	//Checking if the start button has been pressed
	m_currentPadState.Start = sf::Joystick::isButtonPressed(0, 7);

	//Checking if the dpad has been hit
	if (povY < -dpadDeadzone)
		m_currentPadState.DpadDown = true;
	else if (povY > dpadDeadzone)
		m_currentPadState.DpadUp = true;
	else if (povX > dpadDeadzone)
		m_currentPadState.DpadRight = true;
	else if (povX < -dpadDeadzone)
		m_currentPadState.DpadLeft = true;

	//Check if our thumbstick has been moved
	if (axisY < -dpadDeadzone)
		m_currentPadState.LeftThumbStickUp = true;
	else if (axisY > dpadDeadzone)
		m_currentPadState.LeftThumbStickDown = true;
	else if (m_stickValue > dpadDeadzone)
		m_currentPadState.LeftThumbStickRight = true;
	else if (m_stickValue < -dpadDeadzone)
		m_currentPadState.LeftThumbStickLeft = true;

	if (m_triggerAxis > triggerDeadzone)
		m_currentPadState.LT = true;
	else if(m_triggerAxis < -triggerDeadzone)
		m_currentPadState.RT = true;
}

void Xbox360Controller::resetStates()
{
	m_previousPadState = m_currentPadState; //set the previous state as the current
	m_currentPadState = m_defaultPadState; //Sets our current state to the default state (setting all bools to false)
}

float Xbox360Controller::getTriggerValue() const
{
	return m_triggerAxis;
}
float Xbox360Controller::getStickValue() const
{
	return m_stickValue;
}

GamePadState& Xbox360Controller::getCurrent()
{
	return m_currentPadState;
}

GamePadState& Xbox360Controller::getPrevious()
{
	return m_previousPadState;
}
