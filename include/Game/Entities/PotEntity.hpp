/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PotEntity.hpp
*/

#pragma once

#include <map>
#include "../AEntity.hpp"
#include "../AMovable.hpp"
#include "../Controllable.hpp"

class PotEntity : public AEntity {
public:
	PotEntity();
	void updateRender() override;
	void breakMe();
	void update(EntitiesMap *map) override;
	void dump (std::ostream &s) const;
	void load(std::istream &s);
	virtual ~PotEntity();
private:
	struct serialize {
		bool broken;
	};

	bool _broken;
	static const std::map<int, std::function<AEntity *()>> _gemGen;
	void genRandomGem(EntitiesMap *map);
};
