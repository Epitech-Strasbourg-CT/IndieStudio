/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BIAController.cpp
*/

#include "../../include/Game/BIAController.hpp"
#include "../../include/Singletons/EventReceiver.hpp"

BIAController::BIAController(size_t id) : _id(id)
{
}

void BIAController::updateInputs()
{
	switch (rand() % 4) {
	case 0:
		_controllable->callBind(MOVE_UP, KEY_DOWN);
	case 1:
		_controllable->callBind(MOVE_DOWN, KEY_DOWN);
	case 2:
		_controllable->callBind(MOVE_LEFT, KEY_DOWN);
	case 3:
		_controllable->callBind(MOVE_RIGHT, KEY_DOWN);
	}
//	for (auto &n : _isKeyDown)
//		if (n.second && _bindsDown.count(n.first) > 0)
//			_controllable->callBind(_bindsDown[n.first],
//				KEY_DOWN);
}
