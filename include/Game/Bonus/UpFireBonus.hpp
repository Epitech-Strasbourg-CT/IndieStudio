/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** UpFireBonus.hpp
*/

#ifndef BOMBERMAN_UPFIREBONUS_HPP
	#define BOMBERMAN_UPFIREBONUS_HPP

	#include "../Entities/ABonusEntity.hpp"

class UpFireBonus : public ABonusEntity {
public:
	UpFireBonus();

	void playerChanging(PlayerEntity *entity) override;
};

#endif /* !BOMBERMAN_UPFIREBONUS_HPP */
