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

irr::core::vector2di BIAController::_getFuturePos(ControlName c)
{
	std::map<ControlName, std::vector<int>> a = {{MOVE_DOWN, {0, 1}},
		{MOVE_UP, {0, -1}}, {MOVE_LEFT, {1, 0}}, {MOVE_RIGHT, {-1, 0}}};
	auto realX = _p->AEntity::getPosX() + a[c][0];
	auto realY = _p->AEntity::getPosY() + a[c][1];
	return {realX, realY};
};

bool BIAController::_move(ControlName c)
{
	auto pos = _getFuturePos(c);
	if (!_map.canMoveTo(pos))
		return false;
	_targetPos[0] = pos.X;
	_targetPos[1] = pos.Y;
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

int BIAController::_getDangerLevel(irr::core::vector2di pos, irr::core::vector2di dir, int r)
{
	if (r < 0)
		return false;
	if (dir.X == 0 && dir.Y == 0) {
		return (_getDangerLevel(pos, {1, 0}, 5) +
			_getDangerLevel(pos, {-1, 0}, 5) +
			_getDangerLevel(pos, {0, 1}, 5) +
			_getDangerLevel(pos, {0, -1}, 5));
	}
	if (pos.Y >= 0 && pos.X >= 0 && _map.getMap().size() > pos.Y &&
		_map.getMap()[pos.Y].size() > pos.X)
		for (auto &e : _map.getMap()[pos.Y][pos.X]) {
			if (e->getType() == "bomb")
				return true;
		}
	pos.X += dir.X;
	pos.Y += dir.Y;
	return _getDangerLevel(pos, dir, r - 1);
}

bool BIAController::_isSafe(irr::core::vector2di pos)
{
	if (pos.Y >= 0 && pos.X >= 0 && _map.getMap().size() > pos.Y &&
		_map.getMap()[pos.Y].size() > pos.X)
		for (auto &e : _map.getMap()[pos.Y][pos.X]) {
			if (e->getType() == "fire")
				return false;
		}
	return true;
}

ControlName BIAController::_bestEscape()
{
	auto goal = static_cast<ControlName>(rand() % 4);

	if (_isSafe(_getFuturePos(goal)))
		return goal;
	else
		return _bestEscape();
}

void BIAController::_fillTargetQueue()
{
	int x = _p->AEntity::getPosX();
	int y = _p->AEntity::getPosY();
	if (_getDangerLevel({x, y}, {0, 0}, 5)) {
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
