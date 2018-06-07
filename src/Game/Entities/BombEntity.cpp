/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BombEntity.cpp
*/

#include "../../../include/Game/Entities/BombEntity.hpp"

BombEntity::BombEntity(int x, int y): AEntity("Bomb", x, y)
{
	std::cout << "bombe posée!" << std::endl;
}

bool BombEntity::hasExploded() const
{
	return false;
}
