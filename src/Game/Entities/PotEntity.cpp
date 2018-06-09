/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PotEntity.cpp
*/

#include "../../../include/Game/Entities/PotEntity.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Singletons/IrrManager.hpp"
#include "../../../include/Game/EntitiesMap.hpp"
#include "../../../include/Game/Entities/ABonusEntity.hpp"
#include "../../../include/Game/Entities/Bonus/UpBombBonus.hpp"
#include "../../../include/Game/Entities/Bonus/UpFireBonus.hpp"
#include "../../../include/Game/Entities/Bonus/InvertBonus.hpp"
#include "../../../include/Game/Entities/Bonus/ResetFireRangeBonus.hpp"

const std::map<int, std::function<AEntity *()>> PotEntity::_gemGen = {
	{55, []() {
		return nullptr;
	}},
	{20, []() {
		return new UpBombBonus(GREEN);
	}},
	{10, []() {
		return new UpFireBonus(RED);
	}},
	{10, []() {
		return new ResetFireRangeBonus(BLUE);
	}},
	{5, []() {
		return new InvertBonus(YELLOW);
	}}
};

PotEntity::PotEntity() : AEntity("pot"), _broken(false)
{
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("block/Pot.dae");
	_stackable = false;
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setScale({3.5, 3.5, 3.5});
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setRotation({-90, 0, 0});
}

void PotEntity::updateRender()
{
	AEntity::updateRender();
}

void PotEntity::breakMe()
{
	_broken = true;
}

void PotEntity::genRandomGem(EntitiesMap *map)
{
	auto sum = 0;
	for (auto &n : PotEntity::_gemGen)
		sum += n.first;
	auto floor = rand() % sum;
	AEntity *elem = 0;
	auto floorSeek = 0;
	for (auto &n : PotEntity::_gemGen) {
		floorSeek += n.first;
		if (floor < floorSeek) {
			elem = n.second();
			break;
		}
	}
	if (elem)
		map->insert(elem, getPosition());
}

void PotEntity::update(EntitiesMap *map)
{
	if (_broken) {
		genRandomGem(map);
		map->erase(this);
	}
	AEntity::update(map);
}

PotEntity::~PotEntity()
{
	_node->remove();
}
