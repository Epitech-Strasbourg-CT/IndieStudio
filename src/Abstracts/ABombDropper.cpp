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
//	for (auto i = 0 ; i < _bombs.size() ; ++i) {
//		if (_bombs[i].hasExploded()) {
//			std::cout << "A bomb has exploded!" << std::endl;
//			_currentBomb -= 1;
//			_bombs.erase(_bombs.begin() + i);
//			i -= 1;
//		}
//
//	}
	if (_currentBomb < _maxBomb) {
		EntityFactory fac;
		auto bomb = fac.createEntity("bomb");
		bomb->setPosition({x, y});
		map->insert(bomb.get(), {x, y});
		_currentBomb += 1;
	}
}
