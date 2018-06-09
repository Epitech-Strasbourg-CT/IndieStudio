/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** UpBombBonus.hpp
*/

#ifndef BOMBERMAN_UPBOMBBONUS_HPP
	#define BOMBERMAN_UPBOMBBONUS_HPP

	#include "../ABonusEntity.hpp"

class UpBombBonus : public ABonusEntity {
public:
	UpBombBonus(RupeeColor color);
	void playerChanging(PlayerEntity *entity);

};

#endif /* !BOMBERMAN_UPBOMBBONUS_HPP */
