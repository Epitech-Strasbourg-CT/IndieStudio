/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EntitiesPool.hpp
*/

#ifndef BOMBERMAN_ENTITIESPOOL_HPP
#define BOMBERMAN_ENTITIESPOOL_HPP

#include "AEntity.hpp"

class EntitiesPool {
public:
	EntitiesPool() = default;

	bool addEntity(AEntity &entity);
	bool delEntity(AEntity &entity);
	//?? getEntities();
	void update();
	void updateRender();
private:

};


#endif /* !BOMBERMAN_ENTITIESPOOL_HPP */
