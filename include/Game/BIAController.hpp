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
	void registerBind(irr::EKEY_CODE code, ControlName_e c, ControlType_e t);
	void unregisterBind(irr::EKEY_CODE code, ControlType_e t);
	void updateInputs() override;
private:
	std::unordered_map<irr::EKEY_CODE, ControlName_e>
	&_getBinds(ControlType_e t);

	size_t _id;
	std::unordered_map<irr::EKEY_CODE, ControlName_e> _bindsDown;
	std::unordered_map<irr::EKEY_CODE, ControlName_e> _bindsPressed;
	std::unordered_map<irr::EKEY_CODE, ControlName_e> _bindsReleased;
	std::unordered_map<irr::EKEY_CODE, bool> _isKeyDown;
	std::unordered_map<irr::EKEY_CODE, bool> _isKeyPressed;
	std::unordered_map<irr::EKEY_CODE, bool> _isKeyRelease;
};


#endif /* !BOMBERMAN_KEYBOARDCONTROLLER_HPP */
