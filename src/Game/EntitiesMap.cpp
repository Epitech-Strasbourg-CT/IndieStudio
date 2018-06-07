/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EntitiesPool.cpp
*/

#include "../../include/Game/EntitiesMap.hpp"
#include "../../include/Game/Entities/BlockEntity.hpp"

const std::unordered_map<char, std::function<AEntity *()>>
EntitiesMap::_generationMap = {
	{'X', []() {
		return nullptr;
	}},
	{'0', [](){
		return nullptr;
	}}
};

const std::vector<std::string> EntitiesMap::_mapTemplate = {
	"XXXXXXXXXXXXXXXXXXX",
	"X1 0000000000000 2X",
	"X X0X0X0X0X0X0X0X X",
	"X00000000000000000X",
	"X0X0X0X0X0X0X0X0X0X",
	"X00000000000000000X",
	"X0X0X0X0X0X0X0X0X0X",
	"X00000000000000000X",
	"X0X0X0X0X0X0X0X0X0X",
	"X00000000000000000X",
	"X0X0X0X0X0X0X0X0X0X",
	"X00000000000000000X",
	"X X0X0X0X0X0X0X0X X",
	"X3 0000000000000 4X",
	"XXXXXXXXXXXXXXXXXXX",
};

bool EntitiesMap::insert(AEntity *e, const irr::core::vector2di &v)
{
	return false;
}

bool EntitiesMap::erase(AEntity *e)
{
	return false;
}

bool EntitiesMap::moveTo(AEntity *e, const irr::core::vector2di &v)
{
	return false;
}

bool EntitiesMap::canMoveTo(AEntity *e, const irr::core::vector2di &v)
{
	return false;
}

bool EntitiesMap::generate()
{
	return false;
}

void EntitiesMap::update()
{
}

void EntitiesMap::updateRender()
{
}
