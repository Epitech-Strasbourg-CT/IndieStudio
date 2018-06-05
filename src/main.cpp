/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/
#include "../include/Singletons/StateMachine.hpp"
#include "../include/States/SplashState.hpp"
#include "../include/Singletons/IrrManager.hpp"
#include "../include/Singletons/EventReceiver.hpp"

int main()
{
	auto shared = AStateShare();
	auto splash = new SplashState(shared);
	StateMachine::getInstance().push(splash, false);
	auto device = IrrManager::getInstance().getDevice();
	device->setEventReceiver(&EventReceiver::getInstance());
	return StateMachine::getInstance().start();
}