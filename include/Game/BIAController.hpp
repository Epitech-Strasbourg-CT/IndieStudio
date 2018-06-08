/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BKeyboardController.hpp
*/

#pragma once

#include "Controllable.hpp"

class BIAController : public AController {
public:
	BIAController(size_t id);

	void updateInputs() override;
private:
	size_t _id;
};
