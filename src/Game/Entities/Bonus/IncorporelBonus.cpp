/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** IncorporelBonus.cpp
*/

#include "../../../../include/Game/Bonus/IncorporelBonus.hpp"

IncorporelBonus::IncorporelBonus(): ABonusEntity("incorporel_bonus", GRAY)
{

}

void IncorporelBonus::playerChanging(PlayerEntity *entity)
{
	entity->setIncorporel();
}
