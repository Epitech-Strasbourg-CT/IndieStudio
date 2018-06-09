/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AController.hpp
*/

#ifndef BOMBERMAN_ACONTROLLER_HPP
#define BOMBERMAN_ACONTROLLER_HPP

#include <irrlicht.h>
#include <unordered_map>
#include "EntitiesMap.hpp"

class Controllable;

enum ControlName {
	NONE,
	MOVE_UP,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_DOWN,
	DROP_BOMB,
};

enum ControlType {
	KEY_DOWN,
	KEY_PRESSED,
	KEY_RELEASED,
};

enum ControllerType {
	IA = 0,
	PLAYER = 1,
};

using ControlPair = std::pair<ControlName, ControlType>;

class AController {
public:
	virtual void updateInputs(EntitiesMap *map);
	virtual ~AController();
	static void bindEntityToController(AController &, Controllable &);
	virtual ControllerType getType() const = 0;
private:
	void registerControllable(Controllable *controllable);
protected:
	Controllable *_controllable = nullptr;
};


#endif /* !BOMBERMAN_ACONTROLLER_HPP */
