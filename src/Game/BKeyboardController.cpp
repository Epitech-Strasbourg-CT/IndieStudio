/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BKeyboardController.cpp
*/

#include "../../include/Game/BKeyboardController.hpp"
#include "../../include/Singletons/EventReceiver.hpp"

BKeyboardController::BKeyboardController()
{
	auto &er = EventReceiver::getInstance();
	er.registerEvent(100, irr::EET_KEY_INPUT_EVENT,
	[this](const irr::SEvent &ev) {
		if (_binds.count(ev.KeyInput.Key) > 0 && _controllable)
			_controllable->callBind(_binds[ev.KeyInput.Key]);
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
