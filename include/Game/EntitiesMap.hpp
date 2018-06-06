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
	EntitiesMap();

	bool insert(AEntity &entity);
	bool erase(AEntity &entity);
	std::vector<AEntity *> const &getEntities(irr::core::vector2di &);
	bool generate();
	void clean();
	void update();
	void updateRender();
	std::set<AEntity *> getList() const;
	std::map<irr::core::vector2di, std::vector<AEntity *>> const &getMap();
private:
	void remove(AEntity &);

	std::list<AEntity *> _pending;
	std::map<irr::core::vector2di, std::vector<AEntity *>> _map;
	static const std::vector<std::string> _mapTemplate;
	static const std::unordered_map<char, std::function<AEntity *()>>
	_generationMap;
};


#endif /* !BOMBERMAN_ENTITIESPOOL_HPP */
