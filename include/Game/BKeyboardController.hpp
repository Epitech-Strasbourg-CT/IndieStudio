/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BKeyboardController.hpp
*/

#ifndef BOMBERMAN_KEYBOARDCONTROLLER_HPP
#define BOMBERMAN_KEYBOARDCONTROLLER_HPP

#include "Controllable.hpp"

class BKeyboardController : public AController {
public:
	BKeyboardController();
	void registerBind(irr::EKEY_CODE code, ControlName_e c);
	void unregisterBind(irr::EKEY_CODE code);
private:
	std::unordered_map
	<irr::EKEY_CODE, ControlName_e>
	_binds;
};


#endif /* !BOMBERMAN_KEYBOARDCONTROLLER_HPP */
