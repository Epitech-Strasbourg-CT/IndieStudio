/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BKeyboardController.hpp
*/

#pragma once

#include <vector>
#include "Controllable.hpp"
#include "Entities/PlayerEntity.hpp"
#include "../Game/EntitiesMap.hpp"

class BIAController : public AController {
public:
	BIAController(EntitiesMap &map, size_t id);

	void updateInputs() override;
private:
	void _fillTargetQueue();
	void _goToTarget();
	bool _onTarget();
	bool _move(ControlName_e c);

	size_t _id;
	ControlName_e _targetMove;
	bool _alreadyMove;
	std::vector<int> _targetPos;
	std::queue<ControlName_e> _targetQueue;
	PlayerEntity *_p;
	EntitiesMap &_map;
};
