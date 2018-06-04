/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** SaveManager.cpp
*/
#include <fstream>
#include "../../include/Game/SaveManager.hpp"


void SaveManager::save(EntitiesMap &map, const std::string &filename)
{
    std::ofstream file(filename, std::ofstream::out);

    if (!file.good())
        throw std::runtime_error("Can't save the Entities");

//     string entity;
    //auto entities = map.getEntities();
    //for (auto &n : entities){
    // n >> file;
    //}
}

void SaveManager::load(EntitiesMap &pool, const std::string &filename)
{
    std::ifstream file(filename, std::ifstream::in);

    if (!file.good())
        throw std::runtime_error("Can't load the Entities");
//     string entity;
//     EntityFactory fact;
    //while (auto &n : entities){
    //     
    // pool.insert(fact.createEntity())
    //}
}