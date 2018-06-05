/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BombEntity.cpp
*/

#include "BombEntity.hpp"

BombEntity::BombEntity(): AEntity("Bomb")
{

}

void BombEntity::collide(AEntity &entity)
{
	AEntity::collide(entity);
}

void BombEntity::update(EntitiesMap *map)
{
	AEntity::update(map);
}

void BombEntity::updateRender()
{
	AEntity::updateRender();
}
