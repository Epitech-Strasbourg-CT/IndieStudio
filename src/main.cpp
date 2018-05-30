/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/
#include "../include/Singletons.hpp"
#include "../include/SplashState.hpp"

GameManager gameManager;
StateMachine stateMachine;

int main()
{
    auto splash = new SplashState();
    stateMachine.push(splash, false);
    return stateMachine.start();
}