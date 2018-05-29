/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include <iostream>
#include "../include/StateMachine.hpp"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{}


int StateMachine::push(AState *GameState) {
	_states.push(std::unique_ptr<AState>(GameState));
	return 0;
}

int StateMachine::pop() {
	_states.pop();
	return 0;
}

int StateMachine::start() {

}

AState *StateMachine::top() {
	if (_states.empty())
		return nullptr;
	return _states.top().get();
}

int main(int ac, char **av)
{
	StateMachine Machine;


	return 0;
 }
