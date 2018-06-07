/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#pragma once

#include "AEntity.hpp"
#include <algorithm>
#include <functional>
#include <map>
#include <memory>

class EntityFactory {
	public:
	EntityFactory();
	~EntityFactory();

	std::unique_ptr<AEntity> createEntity(const std::string &);

	protected:
	private:
	std::map<std::string, std::function<std::unique_ptr<AEntity>()>> _fac;
};
