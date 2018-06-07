/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BKeyboardController.hpp
*/

#ifndef BOMBERMAN_KEYBOARDCONTROLLER_HPP
#define BOMBERMAN_KEYBOARDCONTROLLER_HPP

#include <unordered_map>
#include "Controllable.hpp"

class BKeyboardController : public AController {
public:
	BKeyboardController(size_t id);
	void registerBind(irr::EKEY_CODE code, ControlName_e c);
	void unregisterBind(irr::EKEY_CODE code);
	void updateInputs() override;
private:
	size_t _id;
	std::unordered_map
	<irr::EKEY_CODE, ControlName_e>
	_binds;
	std::unordered_map<irr::EKEY_CODE, bool> _isKeyDown;
};


#endif /* !BOMBERMAN_KEYBOARDCONTROLLER_HPP */
