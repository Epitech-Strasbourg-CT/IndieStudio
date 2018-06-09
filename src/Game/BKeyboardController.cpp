/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BKeyboardController.cpp
*/

#include <string>
#include "../../include/Game/BKeyboardController.hpp"
#include "../../include/Singletons/EventReceiver.hpp"

const std::map<unsigned int, std::list<BKeyboardController::KeyMap>> BKeyboardController::_keyMap = {
{0,
	{
		{irr::KEY_KEY_Z, MOVE_UP, KEY_DOWN},
		{irr::KEY_KEY_S, MOVE_DOWN, KEY_DOWN},
		{irr::KEY_KEY_Q, MOVE_LEFT, KEY_DOWN},
		{irr::KEY_KEY_D, MOVE_RIGHT, KEY_DOWN},
		{irr::KEY_KEY_A, DROP_BOMB, KEY_PRESSED}
	}
},
{1,
	{
		{irr::KEY_KEY_T, MOVE_UP, KEY_DOWN},
		{irr::KEY_KEY_G, MOVE_DOWN, KEY_DOWN},
		{irr::KEY_KEY_F, MOVE_LEFT, KEY_DOWN},
		{irr::KEY_KEY_H, MOVE_RIGHT, KEY_DOWN},
		{irr::KEY_KEY_R, DROP_BOMB, KEY_PRESSED}
	}
},
{2,
	{
		{irr::KEY_KEY_O, MOVE_UP, KEY_DOWN},
		{irr::KEY_KEY_L, MOVE_DOWN, KEY_DOWN},
		{irr::KEY_KEY_K, MOVE_LEFT, KEY_DOWN},
		{irr::KEY_KEY_M, MOVE_RIGHT, KEY_DOWN},
		{irr::KEY_KEY_I, DROP_BOMB, KEY_PRESSED}
	}
},
{3,
	{
		{irr::KEY_UP, MOVE_UP, KEY_DOWN},
		{irr::KEY_DOWN, MOVE_DOWN, KEY_DOWN},
		{irr::KEY_LEFT, MOVE_LEFT, KEY_DOWN},
		{irr::KEY_RIGHT, MOVE_RIGHT, KEY_DOWN},
		{irr::KEY_RCONTROL, DROP_BOMB, KEY_PRESSED}
	}
}
};

BKeyboardController::BKeyboardController(size_t id) : _id(id), _bindsDown(),
_bindsPressed(), _bindsReleased(), _isKeyDown(), _isKeyPressed(),
_isKeyRelease()
{
	if (id < 1 || id > 4)
		throw std::out_of_range("Can't instanciate player with id " + std::to_string(id));
	auto &er = EventReceiver::getInstance();
	er.registerEvent(_id, irr::EET_KEY_INPUT_EVENT,
		[this](const irr::SEvent &ev) {
			auto key = ev.KeyInput.Key;
			if (_bindsDown.count(key) > 0 && _controllable)
				this->_isKeyDown[key] = ev.KeyInput.PressedDown;
			else if (_bindsPressed.count(key) > 0 && _controllable)
				this->_isKeyPressed[key] = ev.KeyInput.PressedDown;
			else if (_bindsReleased.count(key) > 0 && _controllable)
				this->_isKeyRelease[key] = !ev.KeyInput.PressedDown;
			return true;
		});
	for (auto elem : _keyMap.at(id - 1))
		registerBind(elem.key, elem.control, elem.type);
}

void BKeyboardController::registerBind(irr::EKEY_CODE code, ControlName c,
	ControlType t
)
{
	_getBinds(t)[code] = c;
}

void BKeyboardController::unregisterBind(irr::EKEY_CODE code, ControlType t)
{
	_getBinds(t).erase(code);
}

void BKeyboardController::updateInputs()
{
	for (auto &n : _isKeyDown)
		if (n.second && _bindsDown.count(n.first) > 0)
			_controllable->callBind(_bindsDown[n.first],
				KEY_DOWN);
	for (auto &n : _isKeyPressed)
		if (n.second && _bindsPressed.count(n.first) > 0) {
			_controllable->callBind(_bindsPressed[n.first],
				KEY_PRESSED);
			n.second = false;
		}
	for (auto &n : _isKeyRelease)
		if (n.second && _bindsReleased.count(n.first) > 0) {
			_controllable->callBind(_bindsReleased[n.first],
				KEY_RELEASED);
			n.second = false;
		}
}

std::unordered_map<irr::EKEY_CODE, ControlName> &BKeyboardController::_getBinds(
	ControlType t
)
{
	switch (t) {
	case KEY_DOWN:
		return _bindsDown;
	case KEY_PRESSED:
		return _bindsPressed;
	case KEY_RELEASED:
		return _bindsReleased;
	default:
		throw std::runtime_error("key mode not implemented");
	}
}

#include <iostream>

BKeyboardController::~BKeyboardController()
{
	std::cout << "Destroy Controller" << std::endl;
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(_id, irr::EET_KEY_INPUT_EVENT);
}
