/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** IncorporelBonus.hpp
*/

#ifndef BOMBERMAN_INCORPORELBONUS_HPP
#define BOMBERMAN_INCORPORELBONUS_HPP


#include "../Entities/ABonusEntity.hpp"

class IncorporelBonus : public ABonusEntity {
public:
	IncorporelBonus();
	void playerChanging(PlayerEntity *entity) override;
};


#endif /* !BOMBERMAN_INCORPORELBONUS_HPP */
