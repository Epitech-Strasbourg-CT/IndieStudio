/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BombEntity.hpp
*/

#ifndef BOMBERMAN_BOMBENTITY_HPP
#define BOMBERMAN_BOMBENTITY_HPP


#include "../../../include/Game/AEntity.hpp"

class BombEntity : public AEntity {
public:
	BombEntity();

	void collide(AEntity &entity) override;

	void update(EntitiesMap *map) override;

	void updateRender() override;
};


#endif /* !BOMBERMAN_BOMBENTITY_HPP */
