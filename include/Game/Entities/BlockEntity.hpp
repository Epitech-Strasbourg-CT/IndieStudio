/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BlockEntity.hpp
*/

#pragma once

#include "../AEntity.hpp"
#include "../AMovable.hpp"
#include "../Controllable.hpp"

class BlockEntity : public AEntity {
public:
	BlockEntity();
	void update();
	void updateRender() override;
	void dump(std::ostream &s) const;
	void load(std::istream &s);

private:
	struct serialize {
	};
};
