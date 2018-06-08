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

enum ControlType_e {
	KEY_DOWN,
	KEY_PRESSED,
	KEY_RELEASED,
};

using ControlPair_e = std::pair<ControlName_e, ControlType_e>;

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
