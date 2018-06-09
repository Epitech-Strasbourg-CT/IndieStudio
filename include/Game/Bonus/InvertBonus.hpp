/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** InvertBonus.hpp
*/

#ifndef BOMBERMAN_INVERTBONUS_HPP
	#define BOMBERMAN_INVERTBONUS_HPP

	#include "../Entities/ABonusEntity.hpp"

class InvertBonus : public ABonusEntity {
public:
	InvertBonus();

	void playerChanging(PlayerEntity *entity) override;
};

#endif /* !BOMBERMAN_INVERTBONUS_HPP */
