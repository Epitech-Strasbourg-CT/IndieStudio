/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PlayerEntity.hpp
*/

#pragma once

#include "../../Abstracts/ABombDropper.hpp"
#include "../AEntity.hpp"
#include "../AMovable.hpp"
#include "../Controllable.hpp"

#define ANGLE_SUP 180
#define BORDERX 10.0
#define BORDERY 10.0

class PlayerEntity : public ABombDropper,
                     public Controllable,
                     public AEntity,
                     public AMovable<int> {
public:
	PlayerEntity();
	void update(EntitiesMap *map) override;
	void updatePosition(EntitiesMap *map);
	void updateRender() override;
	void updateRenderDir();
	void updateRenderPosition();
	void dump(std::ostream &s) const;
	void load(std::istream &s);

private:
	struct serialize {
	};
	irr::core::vector2di _old;
	irr::core::vector2di _look;
};
