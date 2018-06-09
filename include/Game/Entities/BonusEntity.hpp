/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BonusEntity.hpp
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

class BonusEntity: public AEntity {
public:
	explicit BonusEntity(RupeeColor color);
	void collide(AEntity &entity) override;
	virtual void playerChanging(PlayerEntity *entity);
	void update(EntitiesMap *map) override;
	virtual ~BonusEntity();
	void destroy();
private:
	bool _destroyed;
};


#endif /* !BOMBERMAN_BONUSENTITY_HPP */
