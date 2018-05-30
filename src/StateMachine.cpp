/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include "../include/StateMachine.hpp"

int StateMachine::push(AState *GameState)
{
	_states.push(std::unique_ptr<AState>(GameState));
	return 0;
}

int StateMachine::pop()
{
	_states.pop();
	return 0;
}

int StateMachine::start()
{
	return 0;
}

AState *StateMachine::top()
{
	if (_states.empty())
		return nullptr;
	return _states.top().get();
}
