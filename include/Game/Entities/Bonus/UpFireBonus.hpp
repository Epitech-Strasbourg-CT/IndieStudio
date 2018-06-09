/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** UpFireBonus.hpp
*/

#ifndef BOMBERMAN_UPFIREBONUS_HPP
	#define BOMBERMAN_UPFIREBONUS_HPP

	#include "../ABonusEntity.hpp"

class UpFireBonus : public ABonusEntity {
public:
	UpFireBonus(RupeeColor color);

	void playerChanging(PlayerEntity *entity) override;
};

#endif /* !BOMBERMAN_UPFIREBONUS_HPP */
