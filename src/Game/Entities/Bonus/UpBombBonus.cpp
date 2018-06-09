/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** UpBombBonus.cpp
*/

#include "../../../../include/Game/Bonus/UpBombBonus.hpp"

UpBombBonus::UpBombBonus() : ABonusEntity("bomb_bonus", GREEN)
{
}

void UpBombBonus::playerChanging(PlayerEntity *entity)
{
	entity->upMaxBomb();
}
