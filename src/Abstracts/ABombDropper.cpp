/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by thibrex
*/
#include "../../include/Abstracts/ABombDropper.hpp"

ABombDropper::ABombDropper()
: _toDrop(),
_maxBomb(3),
_range(1),
_currentBomb(0),
_watchingBombs()
{
}

void ABombDropper::dropBomb(int x, int y)
{
	_toDrop.emplace(x, y);
}

void ABombDropper::setMaxBomb(unsigned maxBomb)
{
	_maxBomb = maxBomb;
}

unsigned ABombDropper::getMaxBomb() const
{
	return _maxBomb;
}

void ABombDropper::update(EntitiesMap *map)
{
	auto it = _watchingBombs.begin();

	while (it != _watchingBombs.end())
		if ((*it)->hasExploded()) {
			map->erase(*it);
			it = _watchingBombs.erase(it);
			_currentBomb -= 1;
		} else
			it++;
	while (!_toDrop.empty()) {
		auto front = _toDrop.front();
		auto pos = irr::core::vector2di(front.first, front.second);
		if (map->canMoveTo(pos))
			_updateBomb(map, std::get<0>(front), std::get<1>(front));
		_toDrop.pop();
	}
}

void ABombDropper::_updateBomb(EntitiesMap *map, int x, int y)
{
	if (_currentBomb < _maxBomb) {
		EntityFactory fac;
		auto bomb = fac.createEntity("bomb");
		dynamic_cast<BombEntity *>(bomb.get())->setRange(_range);
		map->insert(bomb.get(), {x, y});
		_watchingBombs.push_back(dynamic_cast<BombEntity *>(bomb.get()));
		bomb.release();
		_currentBomb += 1;
	}
}

void ABombDropper::upFireRange()
{
	_range += 1;
}

void ABombDropper::upMaxBomb()
{
	_maxBomb += 1;
}

ABombDropper::~ABombDropper()
{
	for (auto &n : _watchingBombs)
		n->setAutonomous(true);
}

void ABombDropper::resetFireRange()
{
	_range = 1;
}
