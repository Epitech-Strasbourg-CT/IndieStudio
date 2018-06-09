/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EntitiesPool.cpp
*/

#include "../../include/Game/EntitiesMap.hpp"
#include "../../include/Game/Entities/PotEntity.hpp"
#include "../../include/Game/BKeyboardController.hpp"
#include "../../include/Game/Entities/PlayerEntity.hpp"
#include "../../include/Game/Entities/BlockEntity.hpp"
#include "../../include/Game/BIAController.hpp"

const std::unordered_map<char, std::function<AEntity *(EntitiesMap &, const std::vector<int> &)>>
	EntitiesMap::_generationMap = {{'X', [](EntitiesMap &, const std::vector<int> &) {
	return new BlockEntity();
}}, {'1', [](EntitiesMap &map, const std::vector<int> &IAState) {
	static unsigned id = 0;
	id += 1;
	if (IAState.size() >= id && IAState.at(id-1)) {
		auto *controller = new BKeyboardController(id);

		controller->registerBind(irr::KEY_UP, MOVE_UP, KEY_DOWN);
		controller->registerBind(irr::KEY_DOWN, MOVE_DOWN, KEY_DOWN);
		controller->registerBind(irr::KEY_LEFT, MOVE_LEFT, KEY_DOWN);
		controller->registerBind(irr::KEY_RIGHT, MOVE_RIGHT, KEY_DOWN);
		controller->registerBind(irr::KEY_SPACE, DROP_BOMB,
			KEY_PRESSED);
		EntityFactory fac;
		PlayerEntity *player = new PlayerEntity((id < 5 ? id : 1));
		AController::bindEntityToController(*controller, *player);
		return player;
	} else {
		auto *controller = new BIAController(map, id);

		PlayerEntity *player = new PlayerEntity((id < 5 ? id : 1));
		AController::bindEntityToController(*controller, *player);
		return player;
	}
}}, {'0', [](EntitiesMap &, const std::vector<int> &) {
	AEntity *e = nullptr;
	if ((rand() % 6) < 4)
		e = new PotEntity();
	return e;
}}};

const std::vector<std::string> EntitiesMap::_mapTemplate = {
	"XXXXXXXXXXXXXXXXXXX", "X1 0000000000000 1X", "X X0X0X0X0X0X0X0X X",
	"X00000000000000000X", "X0X0X0X0X0X0X0X0X0X", "X00000000000000000X",
	"X0X0X0X0X0X0X0X0X0X", "X00000000000000000X", "X0X0X0X0X0X0X0X0X0X",
	"X00000000000000000X", "X0X0X0X0X0X0X0X0X0X", "X00000000000000000X",
	"X X0X0X0X0X0X0X0X X", "X1 0000000000000 1X", "XXXXXXXXXXXXXXXXXXX",};

bool EntitiesMap::generate(const std::vector<int> &IAState)
{
	for (size_t y = 0; y < HEIGHT; y++) {
		for (size_t x = 0; x < WIDTH; x++) {
			auto type = _mapTemplate[y][x];
			AEntity *e = nullptr;
			if (EntitiesMap::_generationMap.count(type) > 0)
				e = EntitiesMap::_generationMap.at(type)(*this,
					IAState);
			if (e) {
				insert(e,
					{static_cast<irr::s32>(WIDTH - (x + 1)),
						static_cast<irr::s32>(y)});
			}
		}
	}
	return true;
}

// region List

bool EntitiesMap::insert(AEntity *e, const irr::core::vector2di &v)
{
	auto fct = [e](const InsertTrans &d) {
		return (d.e == e);
	};
	if (std::find_if(_toInsert.begin(), _toInsert.end(), fct)  != _toInsert.end())
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
	std::vector<std::unique_ptr<AEntity>> trash;

	for (auto &n : _toInsert) {
		auto x = n.v.X;
		auto y = n.v.Y;
		if (!canInsertTo(n.v)) {
			std::cout << "GO TRASH : " << n.e->getType() << std::endl;
			trash.push_back(std::unique_ptr<AEntity>(n.e));
			continue;
		}
		for (auto &s : _map[y][x]) {
			s->collide(*(n.e));
			n.e->collide(*(s.get()));
		}
		_map[y][x].push_back(std::unique_ptr<AEntity>(n.e));
		n.e->setPosition(n.v);
	}
	_toInsert.clear();
}

void EntitiesMap::updateErase()
{
	for (auto &n : _toErase) {
		auto e = n.e;
		auto x = n.e->getPosition().X;
		auto y = n.e->getPosition().Y;
		if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
			continue;
		auto &list = _map[y][x];
		auto finder = [e](const std::unique_ptr<AEntity> &p) {
			return (e == p.get());
		};
		auto elem = std::find_if(list.begin(), list.end(), finder);
		if (elem != list.end())
			list.erase(elem);
	}
	_toErase.clear();
}

void EntitiesMap::updateMove()
{
	for (auto &n : _toMove) {
		auto e = n.e;
		auto ox = n.e->getPosition().X;
		auto oy = n.e->getPosition().Y;
		if (ox < 0 || ox >= WIDTH || oy < 0 || oy >= HEIGHT)
			continue;
		auto dx = n.v.X;
		auto dy = n.v.Y;
		if (dx < 0 || dx >= WIDTH || dy < 0 || dy >= HEIGHT)
			continue;
		auto &list = _map[oy][ox];
		auto finder = [e](const std::unique_ptr<AEntity> &p) {
			return (e == p.get());
		};
		auto elem = std::find_if(list.begin(), list.end(), finder);
		if (elem != list.end()) {
			for (auto &s : _map[dy][dx]) {
				s->collide(*(n.e));
				n.e->collide(*(s.get()));
			}
			elem->release();
			list.erase(elem);
			_map[dy][dx].push_back(std::unique_ptr<AEntity>(n.e));
			n.e->setPosition(n.v);
		}
	}
	_toMove.clear();
}

bool EntitiesMap::canInsertTo(const irr::core::vector2di &v)
{
	if (v.X < 0 || v.X >= WIDTH || v.Y < 0 || v.Y >= HEIGHT)
		return false;
	for (auto &n : _map[v.Y][v.X])
		if (!n->isInsertable())
			return false;
	return true;
}

bool EntitiesMap::canMoveTo(const irr::core::vector2di &v)
{
	if (v.X < 0 || v.X >= WIDTH || v.Y < 0 || v.Y >= HEIGHT)
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
}

void EntitiesMap::updateRender()
{
	for (auto &n : _map)
		for (auto &eList : n)
			for (auto &e : eList)
				e->updateRender();
}

void EntitiesMap::update()
{
	updateInsert();
	for (auto &n : _map)
		for (auto &eList : n)
			for (auto &e : eList)
				e->update(this);
	updateErase();
	updateMove();
	updateInsert();
}

EntitiesMap::EMap &EntitiesMap::getMap()
{
	return _map;
}
