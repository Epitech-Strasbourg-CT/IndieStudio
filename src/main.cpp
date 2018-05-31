/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/
#include "../include/Singletons/StateMachine.hpp"
#include "../include/States/SplashState.hpp"

int main()
{
	auto splash = new SplashState();
	StateMachine::getInstance().push(splash, false);
	return StateMachine::getInstance().start();
}