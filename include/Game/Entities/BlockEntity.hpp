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
	void updateRender() override;

private:
	struct serialize {
	};
};
