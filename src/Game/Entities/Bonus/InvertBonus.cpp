/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** InvertBonus.cpp
*/

#include "../../../../include/Game/Bonus/InvertBonus.hpp"

InvertBonus::InvertBonus(RupeeColor color) : ABonusEntity(color)
{
}

void InvertBonus::playerChanging(PlayerEntity *entity)
{
	entity->setReverse();
}
