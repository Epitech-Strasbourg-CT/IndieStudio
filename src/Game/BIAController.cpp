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
	if (rand() % _id)
		_controllable->callBind(MOVE_DOWN, KEY_DOWN);
	else
		_controllable->callBind(MOVE_UP, KEY_DOWN);
//	for (auto &n : _isKeyDown)
//		if (n.second && _bindsDown.count(n.first) > 0)
//			_controllable->callBind(_bindsDown[n.first],
//				KEY_DOWN);
}
