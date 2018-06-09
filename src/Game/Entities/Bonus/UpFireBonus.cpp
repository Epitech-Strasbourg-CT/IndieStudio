/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** UpFireBonus.cpp
*/

#include "../../../../include/Game/Bonus/UpFireBonus.hpp"

UpFireBonus::UpFireBonus(RupeeColor color) : ABonusEntity(color)
{
}

void UpFireBonus::playerChanging(PlayerEntity *entity)
{
	entity->upFireRange();
}
