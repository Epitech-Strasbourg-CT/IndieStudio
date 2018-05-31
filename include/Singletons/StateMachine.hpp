/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#ifndef BOMBERMAN_STATE_MACHINE_HPP
#define BOMBERMAN_STATE_MACHINE_HPP

#include <stack>
#include <memory>
#include <iostream>
#include "../AState.hpp"

class StateMachine {
public:
	void push(AState *gameState, bool keepLoaded);
	void replaceTop(AState *gameState, bool keepLoaded);
	void pop();
	AState *top();
	int start();
	static StateMachine &getInstance();
private:
	StateMachine() = default;
	~StateMachine() = default;
	std::stack<std::unique_ptr<AState>> _states;
	static StateMachine _instance;
};

#endif //BOMBERMAN_STATE_MACHINE_HPP
