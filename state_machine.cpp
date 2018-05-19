/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include <iostream>
#include "state_machine.hpp"

StateMachine::StateMachine()
{
	_State = State::Initial;
}

StateMachine::~StateMachine()
{}

StateMachine::State StateMachine::getState()
{
	return (_State);
}

void StateMachine::RunState()
{
	switch(_State) {
		case Initial:
			std::cout << "état initial" << std::endl;
			_State = StateMachine::STATE2;
			std::cout << "nouvel état: " << StateMachine::getState() << std::endl;
			break;
		case STATE2:
			std::cout << "STATE2" << std::endl;
			_State = StateMachine::STATE3;
			std::cout << "nouvel état: " << StateMachine::getState() << std::endl;
			break;
		case STATE3:
			std::cout << "STATE3, dernier état" << std::endl;
			break;
	}
}

int main(int ac, char **av)
{
	StateMachine Machine;

	/* passe de l'était initial à STATE2 puis STATE3 */
	Machine.RunState();
	Machine.RunState();
	Machine.RunState();

	/* reste dans l'état final */
	Machine.RunState();
	Machine.RunState();
	return 0;
}
