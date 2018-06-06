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

#define BORDERX 30
#define BORDERY 30

class PlayerEntity : public Controllable,
		     public AEntity,
		     public AMovable<int> {
public:
	PlayerEntity();
	void update();
	void updateRender() override;
	void dump(std::ostream &s) const;
	void load(std::istream &s);

private:
	struct serialize {
	};
};
