/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EntitiesPool.hpp
*/

#ifndef BOMBERMAN_ENTITIESMAP_HPP
	#define BOMBERMAN_ENTITIESMAP_HPP

#include <functional>
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
	using EMap = std::vector<std::vector
	        <std::vector<std::unique_ptr<AEntity>>>>;

	EntitiesMap();

	bool insert(AEntity *e, const irr::core::vector2di &v = {0, 0});
	bool erase(AEntity *e);
	bool moveTo(AEntity *e, const irr::core::vector2di &v);
	bool canMoveTo(const irr::core::vector2di &v);

	EMap &getMap();

	void updateInsert();
	void updateErase();
	void updateMove();

	bool generate();

	void update();
	void updateRender();


private:

	EMap _map;

	struct MoveTrans {
		AEntity *e;
		irr::core::vector2di v;
	};

	struct EraseTrans {
		AEntity *e;
	};

	struct InsertTrans {
		AEntity *e;
		irr::core::vector2di v;
	};

	std::list<struct EraseTrans> _toErase;
	std::list<struct InsertTrans> _toInsert;
	std::list<struct MoveTrans> _toMove;

	static const std::vector<std::string>
	_mapTemplate;
	static const std::unordered_map<char, std::function<AEntity *()>>
	_generationMap;
	bool canInsertTo(const irr::core::vector2di &v);
};


#endif /* !BOMBERMAN_ENTITIESPOOL_HPP */
