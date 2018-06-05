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
	for (auto &n : _actions)
		if (_binds.count(n) >= 0)
			_binds[n]();
	_actions.clear();
}

Controllable::Controllable() : _actions(), _binds(), _controller(nullptr)
{
}

void Controllable::callBind(ControlName_e c)
{
	this->_actions.insert(c);
}

void Controllable::saveController(AController *controller)
{
	_controller.reset(controller);
}

void Controllable::dump(std::ostream &s) const
{
	struct Controllable::serialize ser = {};
	auto se = std::unique_ptr<char>(new char[sizeof(ser)]);
	memcpy(se.get(), &ser, sizeof(ser));
	// s.write(se.get(), sizeof(ser));
}

void Controllable::load(std::istream &s)
{
	struct Controllable::serialize ser;
	auto se = std::unique_ptr<char>(new char[sizeof(ser)]);
	// s.read(se.get(), sizeof(ser));
	memcpy(&ser, se.get(), sizeof(ser));
}
