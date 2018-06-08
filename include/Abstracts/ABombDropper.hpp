/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by thibrex
*/
#pragma once

#include <vector>
#include <queue>
#include "../../include/Game/EntitiesMap.hpp"
#include "../../include/Game/EntityFactory.hpp"
#include "../Game/Entities/BombEntity.hpp"

class ABombDropper {
	public:
	ABombDropper();
	virtual ~ABombDropper() = default;
	virtual void update(EntitiesMap *);

	protected:
	void dropBomb(int x, int y);
	unsigned getMaxBomb() const;
	void setMaxBomb(unsigned maxBomb);

	private:
	void _updateBomb(EntitiesMap *map, int x, int y);

	std::queue<std::pair<int, int>> _toDrop;
	unsigned _maxBomb;
	unsigned _currentBomb;
	std::vector<BombEntity *> _watchingBombs;
};


