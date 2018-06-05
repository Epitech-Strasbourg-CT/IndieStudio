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
#include "../Abstracts/AState.hpp"

class StateMachine {
public:
	static StateMachine &getInstance();

	void push(AState *gameState, bool keepLoaded);
	void replaceTop(
	AState *gameState, bool keepLoaded);
	void pop();
	void popAll();
	AState *top();
	int start();
private:
	StateMachine() = default;
	~StateMachine() = default;

	std::stack<std::unique_ptr<AState>> _states;

	static StateMachine _instance;
};

#endif //BOMBERMAN_STATE_MACHINE_HPP
