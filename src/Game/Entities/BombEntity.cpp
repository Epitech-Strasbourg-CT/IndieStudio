/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BombEntity.cpp
*/

#include "../../../include/Game/Entities/BombEntity.hpp"

BombEntity::BombEntity(): AEntity("Bomb")
{
}

bool BombEntity::hasExploded() const
{
	return false;
}

void BombEntity::updateRender()
{
//	AEntity::updateRender();
}
