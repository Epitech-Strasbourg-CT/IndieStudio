/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/
#include "../include/StateMachine.hpp"
#include "../include/SplashState.hpp"

int main()
{
	auto splash = new SplashState();
	StateMachine::getInstance().push(splash, false);
	return StateMachine::getInstance().start();
}