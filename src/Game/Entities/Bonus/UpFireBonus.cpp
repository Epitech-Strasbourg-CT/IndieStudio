/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** UpFireBonus.cpp
*/

#include "../../../../include/Game/Bonus/UpFireBonus.hpp"

UpFireBonus::UpFireBonus() : ABonusEntity("fire_bonus", RED)
{
}

void UpFireBonus::playerChanging(PlayerEntity *entity)
{
	entity->upFireRange();
}
