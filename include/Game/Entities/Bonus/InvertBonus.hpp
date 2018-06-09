/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** InvertBonus.hpp
*/

#ifndef BOMBERMAN_INVERTBONUS_HPP
	#define BOMBERMAN_INVERTBONUS_HPP

	#include "../ABonusEntity.hpp"

class InvertBonus : public ABonusEntity {
public:
	InvertBonus(RupeeColor color);

	void playerChanging(PlayerEntity *entity) override;
};

#endif /* !BOMBERMAN_INVERTBONUS_HPP */
