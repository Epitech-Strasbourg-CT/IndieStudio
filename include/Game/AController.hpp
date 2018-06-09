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

enum ControlName {
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

using ControlPair_e = std::pair<ControlName, ControlType>;

class AController {
public:
	virtual void updateInputs();
	virtual ~AController();
	static void bindEntityToController(AController &, Controllable &);
private:
	void registerControllable(Controllable *controllable);
protected:
	Controllable *_controllable = nullptr;
};


#endif /* !BOMBERMAN_ACONTROLLER_HPP */
