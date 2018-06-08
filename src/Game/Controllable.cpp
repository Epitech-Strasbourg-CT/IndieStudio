/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** Controllable.cpp
*/

#include "../../include/Game/Controllable.hpp"

void Controllable::addEvent(ControlName_e c, ControlType_e t,
	std::function<void()> fct
)
{
	_getBinds(t)[c] = fct;
}

void Controllable::delEvent(ControlName_e c, ControlType_e t)
{
	_getBinds(t).erase(c);
}

void Controllable::update()
{
	_controller->updateInputs();
	for (auto &n : _actions) {
		auto c = std::get<0>(n);
		auto t = std::get<1>(n);
		if (_getBinds(t).count(c) >= 0)
			_getBinds(t)[c]();
	}
	_actions.clear();
}

Controllable::Controllable()
	: _actions(), _bindsPressed(), _bindsReleased(), _controller(nullptr)
{
}

void Controllable::callBind(ControlName_e c, ControlType_e t)
{
	this->_actions.emplace(c, t);
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

std::unordered_map<ControlName_e, std::function<void()>> &
Controllable::_getBinds(ControlType_e t)
{
	if (t == KEY_PRESSED)
		return _bindsPressed;
	else if (t == KEY_RELEASED)
		return _bindsReleased;
	return _bindsPressed;
}
