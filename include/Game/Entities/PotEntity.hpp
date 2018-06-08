/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PotEntity.hpp
*/

#pragma once

#include "../AEntity.hpp"
#include "../AMovable.hpp"
#include "../Controllable.hpp"

class PotEntity : public AEntity {
public:
	PotEntity();
	void updateRender() override;
	void breakMe();
	void update(EntitiesMap *map) override;
	virtual ~PotEntity();
private:
	struct serialize {
	};
	bool _broken;
};
