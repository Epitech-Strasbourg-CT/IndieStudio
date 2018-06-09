/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** ABonusEntity.hpp
*/

#ifndef BOMBERMAN_BONUSENTITY_HPP
	#define BOMBERMAN_BONUSENTITY_HPP

	#include "../AEntity.hpp"
	#include "PlayerEntity.hpp"

enum RupeeColor{
	GREEN = 0,
	BLUE,
	RED,
	GRAY,
	YELLOW,
	PURPLE
};

class ABonusEntity : public AEntity {
public:
	ABonusEntity(RupeeColor color);
	virtual ~ABonusEntity();

	void collide(AEntity &entity) override;
	void update(EntitiesMap *map) override;
	void destroy();
	virtual void playerChanging(PlayerEntity *entity) = 0;
private:
	bool _destroyed;
};


#endif /* !BOMBERMAN_BONUSENTITY_HPP */
