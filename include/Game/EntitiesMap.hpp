/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EntitiesPool.hpp
*/

#ifndef BOMBERMAN_ENTITIESMAP_HPP
#define BOMBERMAN_ENTITIESMAP_HPP

#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include "AEntity.hpp"

#define HEIGHT 15
#define WIDTH 19


class EntitiesMap {
public:
	EntitiesMap() = default;

	bool insert(AEntity *e, const irr::core::vector2di &v = {0, 0});
	bool erase(AEntity *e);
	bool moveTo(AEntity *e, const irr::core::vector2di &v);
	bool canMoveTo(AEntity *e, const irr::core::vector2di &v);


	bool generate();

	void update();
	void updateRender();

private:

	std::list<AEntity *> _toErase;
	std::list<AEntity *> _toMove;

	std::vector<std::vector<std::vector<std::unique_ptr<AEntity>>>> _map;

	static const std::vector<std::string>
	_mapTemplate;
	static const std::unordered_map<char, std::function<AEntity *()>>
	_generationMap;
};


#endif /* !BOMBERMAN_ENTITIESPOOL_HPP */
