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
	ABonusEntity(const std::string &name, RupeeColor color);
	virtual ~ABonusEntity();

	void collide(AEntity &entity) override;
	void update(EntitiesMap *map) override;
	void dump (std::ostream &s) const;
	void load(std::istream &s);
	void destroy();
	virtual void playerChanging(PlayerEntity *entity) = 0;
	void updateRender() override;
private:
	struct serialize {
		bool destroyed;
	};

	bool _destroyed;
};


#endif /* !BOMBERMAN_BONUSENTITY_HPP */
