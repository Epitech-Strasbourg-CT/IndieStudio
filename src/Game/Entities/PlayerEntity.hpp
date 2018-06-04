/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PlayerEntity.hpp
*/

#ifndef BOMBERMAN_PLAYERENTITY_HPP
#define BOMBERMAN_PLAYERENTITY_HPP

#include "../../../include/Game/AEntity.hpp"
#include "../../../include/Game/Movable.hpp"
#include "../../../include/Game/Controllable.hpp"

class PlayerEntity
: public AEntity, public AMovable<float>, public Controllable {
public:
	PlayerEntity(AController &_controller);

protected:
	void update() override;
};


#endif /* !BOMBERMAN_PLAYERENTITY_HPP */
