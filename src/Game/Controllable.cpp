/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** Controllable.cpp
*/

#include "../../include/Game/Controllable.hpp"

void Controllable::addEvent(ControlName_e c, std::function<void()> fct)
{
	_binds[c] = fct;
}

void Controllable::delEvent(ControlName_e c)
{
	_binds.erase(c);
}

void Controllable::update()
{
	for (auto &n : _binds) {
		n.second();
	}
	_actions.clear();
}

Controllable::Controllable(AController &_controller)
: _actions(), _binds(), _controller(_controller)
{
}

void Controllable::callBind(ControlName_e c)
{
	this->_actions.insert(c);
}
