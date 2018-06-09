/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by thibrex
*/

#include "../../include/Game/ControllerFactory.hpp"
#include "../../include/Game/BKeyboardController.hpp"
#include "../../include/Game/BIAController.hpp"

ControllerFactory::ControllerFactory() : _fac(
	{{IA, [](size_t id) {
		return std::unique_ptr<BIAController>(
			new BIAController(id));
	}}, {PLAYER, [](size_t id) {
		return std::unique_ptr<BKeyboardController>(
			new BKeyboardController(id));
	}}})
{
}

std::unique_ptr<AController> ControllerFactory::createController(
	ControllerType type, size_t id
)
{
	if (_fac.find(type) != _fac.end()) {
		return _fac.at(type)(id);
	} else
		throw std::runtime_error("controller not implemented yet");
}
