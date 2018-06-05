/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** SaveManager.hpp
*/

#pragma once

#include "EntitiesMap.hpp"

class SaveManager {
public:
	SaveManager() = default;
	static void save(EntitiesMap &, const std::string &);
	static void load(EntitiesMap &, const std::string &);
protected:
private:
};
