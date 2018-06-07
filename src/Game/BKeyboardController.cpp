/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BKeyboardController.cpp
*/

#include "../../include/Game/BKeyboardController.hpp"
#include "../../include/Singletons/EventReceiver.hpp"

BKeyboardController::BKeyboardController(size_t id)
: _id(id), _binds(), _isKeyDown()
{
	auto &er = EventReceiver::getInstance();
	er.registerEvent(_id, irr::EET_KEY_INPUT_EVENT,
	[this](const irr::SEvent &ev) {
		auto key = ev.KeyInput.Key;
		if (_binds.count(key) > 0 && _controllable)
			this->_isKeyDown[key] = ev.KeyInput.PressedDown;
		return true;
	});
}

void BKeyboardController::registerBind(irr::EKEY_CODE code, ControlName_e c)
{
	_binds[code] = c;
}

void BKeyboardController::unregisterBind(irr::EKEY_CODE code)
{
	_binds.erase(code);
}

void BKeyboardController::updateInputs()
{
	for (auto &n : _isKeyDown)
		if (n.second && _binds.count(n.first) > 0)
			_controllable->callBind(_binds[n.first]);
}
