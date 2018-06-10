/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** UpSpeedBonus.hpp
*/

#ifndef BOMBERMAN_UPSPEEDBONUS_HPP
#define BOMBERMAN_UPSPEEDBONUS_HPP


#include "../Entities/ABonusEntity.hpp"

class UpSpeedBonus : public ABonusEntity  {
public:
	UpSpeedBonus();

	void playerChanging(PlayerEntity *entity) override;
};


#endif /* !BOMBERMAN_UPSPEEDBONUS_HPP */
