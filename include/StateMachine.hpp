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

class AState {
public:
	AState(AState *last);
	virtual bool draw() = 0;
	virtual bool setEnable(bool enable) = 0;
protected:
	AState *_lastState;
private:
	bool _enable;
};

class StateMachine
{
	public:
		StateMachine();
		~StateMachine();
		int push(AState *);
		int pop();
		AState *top();
		int start();
private:
	std::stack<std::unique_ptr<AState>> _states;
};

#endif //BOMBERMAN_STATE_MACHINE_HPP
