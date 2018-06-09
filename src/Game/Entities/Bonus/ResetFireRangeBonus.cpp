/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** ResetFireRangeBonus.cpp
*/

#include "../../../../include/Game/Bonus/ResetFireRangeBonus.hpp"

ResetFireRangeBonus::ResetFireRangeBonus(RupeeColor color) : ABonusEntity(color)
{
}

void ResetFireRangeBonus::playerChanging(PlayerEntity *entity)
{
	entity->resetFireRange();
}
