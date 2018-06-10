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

BIAController::BIAController(size_t id) : _alreadyMove(false),
	_id(id), _targetPos(0, 0), _spawnPos(0, 0)
{
}

void BIAController::updateInputs(EntitiesMap *map)
{
	_map = map;
	_p = dynamic_cast<PlayerEntity *>(_controllable);
	if (!_p || !_map)
		return;
	if (!_alreadyMove && _targetPos.X == 0 && _targetPos.Y == 0) {
		_alreadyMove = true;
		_spawnPos.X = _p->AEntity::getPosX();
		_spawnPos.Y = _p->AEntity::getPosY();
		_targetPos.X = _p->AEntity::getPosX();
		_targetPos.Y = _p->AEntity::getPosY();
	}
	auto c = _bestEscape();
	_bomb(c);
	_fillTargetQueue(c);
	_goToTarget();
}

bool BIAController::_onTarget()
{
	return _p->AEntity::getPosX() == _targetPos.X &&
		_p->AEntity::getPosY() == _targetPos.Y &&
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
	_targetPos.X = pos.X;
	_targetPos.Y = pos.Y;
	_targetMove = c;
	return true;
}

void BIAController::_goToTarget()
{
	if (!_onTarget() && _targetMove != NONE && _isSafe(_targetPos))
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
		return (_getDangerLevel(pos, {1, 0}, 3) +
			_getDangerLevel(pos, {-1, 0}, 3) +
			_getDangerLevel(pos, {0, 1}, 3) +
			_getDangerLevel(pos, {0, -1}, 3));
	}
	if (pos.Y >= 0 && pos.X >= 0 && _map->getMap().size() > pos.Y &&
		_map->getMap()[pos.Y].size() > pos.X)
		for (auto &e : _map->getMap()[pos.Y][pos.X]) {
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
	if (pos.Y >= 0 && pos.X >= 0 && _map->getMap().size() > pos.Y &&
		_map->getMap()[pos.Y].size() > pos.X)
		for (auto &e : _map->getMap()[pos.Y][pos.X]) {
			if (e->getType() == "fire")
				return false;
		}
	return true;
}

std::vector<ControlName> BIAController::_genBestEscapeMoves()
{
	std::vector<ControlName> allMoves = {MOVE_UP, NONE, MOVE_LEFT,
		MOVE_RIGHT, MOVE_DOWN};
	std::vector<ControlName> res;
	while (!allMoves.empty()) {
		auto i = rand() % allMoves.size();
		if (_map->canMoveTo(_getFuturePos(allMoves[i])) &&
			_isSafe(_getFuturePos(allMoves[i]))) {
			res.push_back(allMoves[i]);
		}
		allMoves.erase(allMoves.begin() + i);
	}
	return res;
}

ControlName BIAController::_bestEscape()
{
	std::vector<ControlName> moves = _genBestEscapeMoves();
//	std::cout << "[";
//	for (auto &e : moves)
//		std::cout << e << ",";
//	std::cout << "]" << std::endl;
	if (moves.empty())
		return NONE;
//	std::cout << "[";
//	for (auto &e : moves)
//		std::cout << _getDangerLevel(_getFuturePos(e), {0, 0}, 0)
//			<< ",";
//	std::cout << "]" << std::endl;
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
//	std::cout << "Pending: " << _targetQueue.size() << std::endl;
//	std::cout << "Spawn pos: " << _spawnPos.X << "," << _spawnPos.Y << std::endl;
//	std::cout << "On pos: " << x << "," << y << std::endl;
//	std::cout << "Current danger level: "
//		<< _getDangerLevel(_getFuturePos(NONE), {0, 0}, 0) << std::endl;
//	std::cout << "Forecast danger level: " << bestSafety << std::endl;
//	std::cout << "Forecast move: " << moves[bestMov] << std::endl;
	return moves[bestMov];
}

void BIAController::_fillTargetQueue(ControlName c)
{

	while (!_targetQueue.empty())
		_targetQueue.pop();
	_targetQueue.push(c);
//	std::cout << std::endl;
}

bool BIAController::_bomb(ControlName c)
{
	auto x = _p->AEntity::getPosX();
	auto y = _p->AEntity::getPosY();
	if (x == _spawnPos.X && y == _spawnPos.Y)
		return false;
	if (rand() % 250 || c == NONE)
		return false;
	_controllable->callBind(DROP_BOMB, KEY_PRESSED);
	return true;
}

ControllerType BIAController::getType() const
{
	return IA;
}
