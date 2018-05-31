/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/
#include "../include/Singletons/StateMachine.hpp"
#include "../include/States/SplashState.hpp"
#include "../include/Singletons/GameManager.hpp"
#include "../include/Singletons/EventReceiver.hpp"

int main()
{
	auto splash = new SplashState();
	StateMachine::getInstance().push(splash, false);

	auto device = GameManager::getInstance().getDevice();
	device->setEventReceiver(&EventReceiver::getInstance());
	return StateMachine::getInstance().start();
}