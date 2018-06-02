/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include "IEntity.hpp"

class EntityFactory {
public:
	EntityFactory();
	~EntityFactory();

	std::unique_ptr<IEntity> createEntity(const std::string &);
protected:
private:
	std::map<std::string, std::function<std::unique_ptr<IEntity>()>> _fac;
};
