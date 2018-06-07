/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PlayerEntity.hpp
*/

#pragma once

#include "../AEntity.hpp"
#include "../AMovable.hpp"
#include "../Controllable.hpp"

#define BORDERX 10.0
#define BORDERY 10.0

class PlayerEntity : public Controllable,
		     public AEntity,
		     public AMovable<int> {
public:
	PlayerEntity();
	void update(EntitiesMap *map) override;
	void updateRender() override;
	void dump(std::ostream &s) const;
	void load(std::istream &s);

private:
	struct serialize {
	};
	irr::core::vector2di _old;
};
