/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BKeyboardController.cpp
*/

#include "../../include/Game/BKeyboardController.hpp"
#include "../../include/Singletons/EventReceiver.hpp"

BKeyboardController::BKeyboardController(size_t id) : _id(id), _bindsPressed(),
	_bindsReleased(), _isKeyDown(), _isKeyRelease()
{
	auto &er = EventReceiver::getInstance();
	er.registerEvent(_id, irr::EET_KEY_INPUT_EVENT,
		[this](const irr::SEvent &ev) {
			auto key = ev.KeyInput.Key;
			if (_bindsPressed.count(key) > 0 && _controllable)
				this->_isKeyDown[key] = ev.KeyInput.PressedDown;
			else if (_bindsReleased.count(key) > 0 && _controllable)
				this->_isKeyRelease[key] = !ev.KeyInput.PressedDown;
			return true;
		});
}

void BKeyboardController::registerBind(irr::EKEY_CODE code, ControlName_e c,
	ControlType_e t
)
{
	_getBinds(t)[code] = c;
}

void BKeyboardController::unregisterBind(irr::EKEY_CODE code, ControlType_e t)
{
	_getBinds(t).erase(code);
}

void BKeyboardController::updateInputs()
{
	for (auto &n : _isKeyDown)
		if (n.second && _bindsPressed.count(n.first) > 0)
			_controllable->callBind(_bindsPressed[n.first],
				KEY_PRESSED);
	for (auto &n : _isKeyRelease)
		if (n.second && _bindsReleased.count(n.first) > 0) {
			_controllable->callBind(_bindsReleased[n.first],
				KEY_RELEASED);
			n.second = false;
		}
}

std::unordered_map<irr::EKEY_CODE, ControlName_e> &
BKeyboardController::_getBinds(ControlType_e t)
{
	if (t == KEY_PRESSED)
		return _bindsPressed;
	else if (t == KEY_RELEASED)
		return _bindsReleased;
}
