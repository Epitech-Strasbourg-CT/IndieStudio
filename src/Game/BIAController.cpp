/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BIAController.cpp
*/

#include <iostream>
#include <map>
#include "../../include/Game/BIAController.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Game/Entities/PlayerEntity.hpp"

BIAController::BIAController(EntitiesMap &map, size_t id) : _alreadyMove(false),
	_id(id), _targetPos({0, 0}), _map(map)
{
}

void BIAController::updateInputs()
{
	_p = dynamic_cast<PlayerEntity *>(_controllable);
	if (!_p)
		return;
	if (!_alreadyMove && _targetPos[0] == 0 && _targetPos[1] == 0) {
		_alreadyMove = true;
		_targetPos = {_p->AEntity::getPosX(), _p->AEntity::getPosY()};
	}
//	std::cout << "Current: (" << _p->AEntity::getPosX() << ","
//		<< _p->AEntity::getPosY() << ")" << std::endl;
//	std::cout << "Target: (" << _targetPos[0] << "," << _targetPos[1] << ")"
//		<< std::endl;
//	std::cout << std::endl;
	if (rand() % 150 == 0)
		_controllable->callBind(DROP_BOMB, KEY_PRESSED);
	if (_targetQueue.empty())
		_fillTargetQueue();
	_goToTarget();
}

bool BIAController::_onTarget()
{
	return _p->AEntity::getPosX() == _targetPos[0] &&
		_p->AEntity::getPosY() == _targetPos[1] &&
		_p->AMovable::getPosX() == BORDERX / 2 &&
		_p->AMovable::getPosY() == BORDERY / 2;
}

bool BIAController::_move(ControlName_e c)
{
	std::map<ControlName_e, std::vector<int>> a = {{MOVE_DOWN, {0, 1}},
		{MOVE_UP, {0, -1}}, {MOVE_LEFT, {1, 0}}, {MOVE_RIGHT, {-1, 0}}};
	auto realX = _p->AEntity::getPosX() + a[c][0];
	auto realY = _p->AEntity::getPosY() + a[c][1];
	if (!_map.canMoveTo({realX, realY}))
		return false;
	_targetPos[0] = realX;
	_targetPos[1] = realY;
	_targetMove = c;
	return true;
}

void BIAController::_goToTarget()
{
	if (!_onTarget())
		_controllable->callBind(_targetMove, KEY_DOWN);
	else if (!_targetQueue.empty()) {
		_move(_targetQueue.front());
		_targetQueue.pop();
	}
}

bool BIAController::_isDanger(int x, int y)
{
	for (auto &e : _map.getMap()[y][x]) {
		if (e->getType() == "bomb")
			return true;
	}
	return false;
}

ControlName_e BIAController::_bestEscape()
{
	return static_cast<ControlName_e>(rand() % 4);
}

void BIAController::_fillTargetQueue()
{
	int x = _p->AEntity::getPosX();
	int y = _p->AEntity::getPosY();
	if (_isDanger(x, y)) {
		std::cout << "in danger" << std::endl;
		_targetQueue.push(_bestEscape());
	}
//	std::cout << "uuu" << std::endl;
//	for (auto i = 0 ; i < _map.getMap().size() ; ++i)
//		for (auto j = 0 ; j < _map.getMap()[i].size() ; ++j)
//			for (auto o = 0 ; o < _map.getMap()[i][j].size() ; ++o)
//				if (_map.getMap()[i][j][o]->getType() == "player")
//					std::cout << "found player at (" << i << "," << j << ")" << std::endl;
//	std::cout << "ooo" << std::endl;
//	_targetQueue.push(MOVE_DOWN);
//	_targetQueue.push(MOVE_DOWN);
//	_targetQueue.push(MOVE_RIGHT);
//	_targetQueue.push(MOVE_RIGHT);
//	_targetQueue.push(MOVE_RIGHT);
//	_targetQueue.push(MOVE_RIGHT);
//	_targetQueue.push(MOVE_DOWN);
//	_targetQueue.push(MOVE_DOWN);
//	_targetQueue.push(MOVE_DOWN);
//	_targetQueue.push(MOVE_DOWN);
//	_targetQueue.push(MOVE_DOWN);
}
