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
#include "AEntity.hpp"

#define HEIGHT 15
#define WIDTH 19

class EntitiesMap {
public:
	EntitiesMap() = default;

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
};


#endif /* !BOMBERMAN_ENTITIESPOOL_HPP */
