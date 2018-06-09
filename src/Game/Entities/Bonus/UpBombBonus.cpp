/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** UpBombBonus.cpp
*/

#include "../../../../include/Game/Entities/Bonus/UpBombBonus.hpp"


UpBombBonus::UpBombBonus(RupeeColor color) : ABonusEntity(color)
{
}

void UpBombBonus::playerChanging(PlayerEntity *entity)
{
	entity->upMaxBomb();
}
