/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by thibrex
*/

#pragma once

#include <memory>
#include <map>
#include "AController.hpp"
#include "EntitiesMap.hpp"

class ControllerFactory {
	public:
	ControllerFactory();
	~ControllerFactory() = default;

	std::unique_ptr<AController> createController(ControllerType type,
		size_t id
	);

	protected:
	private:
	std::map<ControllerType, std::function<std::unique_ptr<AController>(
		size_t id
	)>> _fac;
};


