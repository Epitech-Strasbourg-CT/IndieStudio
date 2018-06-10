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
	BIAController(size_t id);

	void updateInputs(EntitiesMap *map) override;
	ControllerType getType() const override;
private:
	void _fillTargetQueue(ControlName c);
	void _goToTarget();
	bool _onTarget();
	int _getDangerLevel(irr::core::vector2di pos, irr::core::vector2di dir, int r);
	bool _isSafe(irr::core::vector2di pos);
	bool _bomb(ControlName c);
	bool _move(ControlName c);
	irr::core::vector2di _getFuturePos(ControlName c);
	std::vector<ControlName> _genBestEscapeMoves();
	ControlName _bestEscape();

	size_t _id;
	ControlName _targetMove;
	bool _alreadyMove;
	irr::core::vector2di _targetPos;
	irr::core::vector2di _spawnPos;
	std::queue<ControlName> _targetQueue;
	PlayerEntity *_p;
	EntitiesMap *_map;
};
