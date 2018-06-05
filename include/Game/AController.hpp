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

class Controllable;

enum ControlName_e {
	MOVE_UP,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_DOWN,
	DROP_BOMB,
};

class AController {
public:
	void registerControllable(Controllable *controllable);
	virtual ~AController();
protected:
	Controllable *_controllable = nullptr;
};


#endif /* !BOMBERMAN_ACONTROLLER_HPP */
