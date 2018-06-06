/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** SaveManager.cpp
*/
#include "../../include/Game/SaveManager.hpp"
#include "../../include/Game/EntityFactory.hpp"
#include <fstream>

void SaveManager::save(EntitiesMap &map, const std::string &filename)
{
//	std::ofstream file(filename, std::ofstream::out);
//	if (!file.good())
//		throw std::runtime_error("Can't save the Entities");
//	auto entities = map.getList();
//	for (auto *n : entities)
//		file << *n;
}

void SaveManager::load(EntitiesMap &pool, const std::string &filename)
{
//	std::ifstream file(filename, std::ifstream::in);
//	if (!file.good())
//		throw std::runtime_error("Can't load the Entities");
//	std::string name;
//	EntityFactory fact;
//	std::cout << std::endl;
//	while (std::getline(file, name, '\0')) {
//		std::cout << name << std::endl;
//		auto e = fact.createEntity(name);
//		file >> *e;
//		pool.insert(*e);
//		e.release();
//	}
}
