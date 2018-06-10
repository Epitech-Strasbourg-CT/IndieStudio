/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** InvertBonus.cpp
*/

#include "../../../../include/Game/Bonus/InvertBonus.hpp"

InvertBonus::InvertBonus() : ABonusEntity("invert_bonus", YELLOW)
{
}

void InvertBonus::playerChanging(PlayerEntity *entity)
{
	entity->reverseDir();
}
