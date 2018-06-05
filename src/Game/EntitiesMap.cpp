/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EntitiesPool.cpp
*/

#include "../../include/Game/EntitiesMap.hpp"

bool EntitiesMap::insert(AEntity &entity)
{
	bool res = false;
	if (entity.getMapPos().X < WIDTH && entity.getMapPos().Y < HEIGHT) {
		_map[entity.getMapPos()].push_back(&entity);
		res = true;
	}
	return res;
}

bool EntitiesMap::erase(AEntity &entity)
{
	bool res = false;
	if (entity.getMapPos().X < WIDTH && entity.getMapPos().Y < HEIGHT) {
		for (auto &i : _map[entity.getMapPos()])
			if (&entity == i) {
				_pending.push_back(&entity);
				res = true;
			}
	}
	return res;
}

void EntitiesMap::update()
{
	for (auto &i : _map)
		for (auto &k : i.second)
			k->update(this);
}

void EntitiesMap::updateRender()
{
	for (auto &i : _map)
		for (auto &k : i.second)
			k->updateRender();
}

bool EntitiesMap::generate()
{
	
}

void EntitiesMap::clean()
{
	for (auto i : _pending)
		remove(*i);
	_pending.clear();
};

std::vector<AEntity *> const &EntitiesMap::getEntities(irr::core::vector2di &pos) {
	if (pos.X < WIDTH && pos.Y < HEIGHT)
		return _map[pos];
	throw 
		std::runtime_error("Out of map position.");
}

std::set<AEntity *> EntitiesMap::getList() const
{
	std::set<AEntity *> res;

	for (auto &i : _map)
		for (auto &k : i.second)
			res.insert(k);
	return res;
}

std::map<irr::core::vector2di, std::vector<AEntity *>> const &EntitiesMap::getMap()
{
	return _map;
}

void EntitiesMap::remove(AEntity &entity)
{
	auto tmp = _map[entity.getMapPos()];

	for (int i = 0; i < tmp.size(); ++i)
		if (&entity == tmp[i])
			tmp.erase(tmp.begin() + i);
}
