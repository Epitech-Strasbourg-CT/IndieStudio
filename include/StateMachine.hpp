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
#include "AState.hpp"

class StateMachine
{
	public:
		StateMachine() = default;
		~StateMachine() = default;
		int push(AState *gameState, bool keepLoaded);
		void pop();
		AState *top();
		int start();
private:
		std::stack<std::unique_ptr<AState>> _states;
};

#endif //BOMBERMAN_STATE_MACHINE_HPP
