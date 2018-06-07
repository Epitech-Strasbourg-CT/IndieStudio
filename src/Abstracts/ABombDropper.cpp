/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by thibrex
*/
#include "../../include/Abstracts/ABombDropper.hpp"

ABombDropper::ABombDropper() : _toDrop(), _maxBomb(3), _currentBomb(0)
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
	while (!_toDrop.empty()) {
		auto front = _toDrop.front();
		_updateBomb(map, std::get<0>(front), std::get<1>(front));
		_toDrop.pop();
	}
}

void ABombDropper::_updateBomb(EntitiesMap *map, int x, int y)
{
	if (_currentBomb < _maxBomb) {
		EntityFactory fac;
		auto bomb = fac.createEntity("bomb");
		map->insert(bomb.get(), {x, y});
		bomb.release();
//		_currentBomb += 1;
	}
}
