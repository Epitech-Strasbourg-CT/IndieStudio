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

class PlayerEntity;

class EntitiesMap {
public:
	using EMap = std::vector<std::vector
	        <std::vector<std::unique_ptr<AEntity>>>>;

	EntitiesMap();

	bool insert(AEntity *e, const irr::core::vector2di &v = {0, 0});
	bool erase(AEntity *e);
	bool moveTo(AEntity *e, const irr::core::vector2di &v);
	bool canMoveTo(const irr::core::vector2di &v, const AEntity *entity = nullptr);
	bool canInsertTo(const irr::core::vector2di &v);

	EMap &getMap();

	void updateInsert();
	void updateErase();
	void updateMove();

	bool generate(const std::vector<int> &IAState);

	size_t update();
	void updateRender();

	static PlayerEntity *generatePlayer(unsigned playerSkinId, bool ia);

	std::vector<int> getPodium();
	int getPodiumN(int n);
	void setPodium(const std::vector<int> &orderDie);


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
	std::vector<int> _orderDie;
	static const std::vector<std::string> _mapTemplate;
	static const std::unordered_map<char, std::function<AEntity *(
		const std::vector<int> &
	)>> _generationMap;
};


#endif /* !BOMBERMAN_ENTITIESPOOL_HPP */
