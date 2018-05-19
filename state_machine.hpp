/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#ifndef BOMBERMAN_STATE_MACHINE_HPP
#define BOMBERMAN_STATE_MACHINE_HPP

class StateMachine
{
public:
	StateMachine();
	~StateMachine();
private:
	enum State {
		Initial,
		STATE2,
		STATE3
	};
	State _State;
public:
	State getState();
	//void setState(State);
	void RunState();

};

#endif //BOMBERMAN_STATE_MACHINE_HPP
