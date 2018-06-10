/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** UpSpeedBonus.cpp
*/

#include "../../../../include/Game/Bonus/UpSpeedBonus.hpp"

UpSpeedBonus::UpSpeedBonus(): ABonusEntity("upspeed_bonus", PURPLE)
{

}

void UpSpeedBonus::playerChanging(PlayerEntity *entity)
{
	entity->speedUp();
}
