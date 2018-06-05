/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PlayerEntity.hpp
*/

#ifndef BOMBERMAN_PLAYERENTITY_HPP
#define BOMBERMAN_PLAYERENTITY_HPP

#include "../AEntity.hpp"
#include "../Movable.hpp"
#include "../Controllable.hpp"

class PlayerEntity
: public Controllable, public AMovable<float>, public AEntity  {
public:
	PlayerEntity();
	void update();
	void updateRender() override;
};


#endif /* !BOMBERMAN_PLAYERENTITY_HPP */
