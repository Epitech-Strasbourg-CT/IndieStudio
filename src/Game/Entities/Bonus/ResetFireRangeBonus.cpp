/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** ResetFireRangeBonus.cpp
*/

#include "../../../../include/Game/Bonus/ResetFireRangeBonus.hpp"

ResetFireRangeBonus::ResetFireRangeBonus() : ABonusEntity("reduce_bonus", BLUE)
{
}

void ResetFireRangeBonus::playerChanging(PlayerEntity *entity)
{
	entity->resetFireRange();
}
