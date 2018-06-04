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
		for (auto &k : i.second);
			//k->update();
}

void EntitiesMap::updateRender()
{
	for (auto &i : _map)
		for (auto &k : i.second);
			//k->updateRender();
}

bool EntitiesMap::generate()
{
	return true;
}

void EntitiesMap::clean()
{
	for (auto i : _pending)
		remove(*i);
	_pending.clear();
	//std::queue<AEntity &>().swap(_queue);
};

std::list<AEntity *> const &EntitiesMap::getList()
{
	return _pending;
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
