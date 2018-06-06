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
		return new BlockEntity();
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

// region List

bool EntitiesMap::insert(AEntity *e, const irr::core::vector2di &v)
{
	auto fct = [e](const InsertTrans &d) {
		return (d.e == e);
	};
	if (std::find_if(
	_toInsert.begin(), _toInsert.end(), fct)  != _toInsert.end())
		return false;
	InsertTrans data = {e, v};
	_toInsert.push_back(data);
	return false;
}

bool EntitiesMap::erase(AEntity *e)
{
	auto fct = [e](const EraseTrans &d) {
		return (d.e == e);
	};
	if (std::find_if(
		_toErase.begin(), _toErase.end(), fct)  != _toErase.end())
		return false;
	EraseTrans data = {e};
	_toErase.push_back(data);
	return true;
}

bool EntitiesMap::moveTo(AEntity *e, const irr::core::vector2di &v)
{
	auto fct = [e](const MoveTrans &d) {
		return (d.e == e);
	};
	if (std::find_if(
		_toMove.begin(), _toMove.end(), fct)  != _toMove.end())
		return false;
	MoveTrans data = {e, v};
	_toMove.push_back(data);
	return true;
}


void EntitiesMap::updateInsert()
{
	for (auto &n : _toInsert)
		std::cout << "INSERT" << std::endl;
	_toInsert.clear();
}

void EntitiesMap::updateErase()
{
	for (auto &n : _toErase)
		std::cout << "ERASE" << std::endl;
	_toErase.clear();

}

void EntitiesMap::updateMove()
{
	for (auto &n : _toMove)
		std::cout << "MOVE" << std::endl;
	_toErase.clear();
}

bool EntitiesMap::canMoveTo(AEntity *e, const irr::core::vector2di &v)
{
	if (v.X < 0 || v.X > WIDTH || v.Y < 0 || v.Y > HEIGHT)
		return false;
	for (auto &n : _map[v.Y][v.X])
		if (!n->isStackable())
			return false;
	return true;
}

//endregion

EntitiesMap::EntitiesMap()
: _map()
{
	_map.resize(HEIGHT);
	for (auto &n : _map)
		n.resize(WIDTH);
	generate();
}

bool EntitiesMap::generate()
{
	for (size_t y = 0; y < HEIGHT; y++) {
		for (size_t x = 0; x < WIDTH; x++) {
			auto type = _mapTemplate[y][x];
			AEntity *e = nullptr;
			if (EntitiesMap::_generationMap.count(type) <= 0)
				e = EntitiesMap::_generationMap.at(type)();
			if (e)
				insert(e);
		}
	}
	return true;
}
