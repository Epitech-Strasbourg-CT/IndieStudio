/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BIAController.cpp
*/

#include <iostream>
#include <map>
#include <thread>
#include <vector>
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
		_controllable->callBind(DROP_BOMB, KEY_PRESSED);
	}
	if (rand() % 200 == 0)
		_controllable->callBind(DROP_BOMB, KEY_PRESSED);

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
	std::map<ControlName, std::vector<int>> a = {{NONE, {0, 0}},
		{MOVE_DOWN, {0, 1}}, {MOVE_UP, {0, -1}}, {MOVE_LEFT, {1, 0}},
		{MOVE_RIGHT, {-1, 0}}};
	auto realX = _p->AEntity::getPosX() + a[c][0];
	auto realY = _p->AEntity::getPosY() + a[c][1];
	return {realX, realY};
};

bool BIAController::_move(ControlName c)
{
	auto pos = _getFuturePos(c);
	_targetPos[0] = pos.X;
	_targetPos[1] = pos.Y;
	_targetMove = c;
	return true;
}

void BIAController::_goToTarget()
{
	if (!_onTarget() && _targetMove != NONE)
		_controllable->callBind(_targetMove, KEY_DOWN);
	else if (!_targetQueue.empty()) {
		_move(_targetQueue.front());
		_targetQueue.pop();
	}
}

int BIAController::_getDangerLevel(irr::core::vector2di pos,
	irr::core::vector2di dir, int r
)
{
	if (r < 0)
		return false;
	if (dir.X == 0 && dir.Y == 0) {
		return (_getDangerLevel(pos, {1, 0}, 6) +
			_getDangerLevel(pos, {-1, 0}, 6) +
			_getDangerLevel(pos, {0, 1}, 6) +
			_getDangerLevel(pos, {0, -1}, 6));
	}
	if (pos.Y >= 0 && pos.X >= 0 && _map.getMap().size() > pos.Y &&
		_map.getMap()[pos.Y].size() > pos.X)
		for (auto &e : _map.getMap()[pos.Y][pos.X]) {
			if (e->getType() == "bomb")
				return r;
			else if (e->getType() == "block" ||
				e->getType() == "pot")
				return 0;
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

std::vector<ControlName> BIAController::_genBestEscapeMoves()
{
	std::vector<ControlName> allMoves = {MOVE_UP, NONE, MOVE_LEFT, MOVE_RIGHT,
		MOVE_DOWN};
	std::vector<ControlName> res;

	while (!allMoves.empty()) {
		auto i = rand() % allMoves.size();
		res.push_back(allMoves[i]);
		allMoves.erase(allMoves.begin() + i);
	}
	return res;
}

ControlName BIAController::_bestEscape()
{
	std::vector<ControlName> moves = _genBestEscapeMoves();
	for (int i = 0; i < moves.size(); ++i) {
		if (!_map.canMoveTo(_getFuturePos(moves[i])) ||
			!_isSafe(_getFuturePos(moves[i]))) {
			moves.erase(moves.begin() + i);
			i -= 1;
		}
	}
	std::cout << "[";
	for (auto &e : moves)
		std::cout << e << ",";
	std::cout << "]" << std::endl;
	if (moves.empty())
		return NONE;
	std::cout << "[";
	for (auto &e : moves)
		std::cout << _getDangerLevel(_getFuturePos(e), {0, 0}, 0) << ",";
	std::cout << "]" << std::endl;
	int bestMov = 0;
	int bestSafety = _getDangerLevel(_getFuturePos(moves[0]), {0, 0}, 0);

	for (int i = 1; i < moves.size(); ++i) {
		auto c = moves[i];
		auto futurePos = _getFuturePos(c);
		auto newSafety = _getDangerLevel(futurePos, {0, 0}, 0);
		if (newSafety < bestSafety && _isSafe(futurePos)) {
			bestMov = i;
			bestSafety = newSafety;
		}
	}
	auto x = _p->AEntity::getPosX();
	auto y = _p->AEntity::getPosY();
	std::cout << "Pending: " << _targetQueue.size() << std::endl;
	std::cout << "On pos: " << x << "," << y << std::endl;
	std::cout << "Current danger level: " << _getDangerLevel(_getFuturePos(NONE), {0, 0}, 0) << std::endl;
	std::cout << "Forecast danger level: " << bestSafety << std::endl;
	std::cout << "Forecast move: " << moves[bestMov] << std::endl;
	return moves[bestMov];
}

void BIAController::_fillTargetQueue()
{
	auto c = _bestEscape();
	while (!_targetQueue.empty())
		_targetQueue.pop();
	_targetQueue.push(c);
	std::cout << std::endl;
}
