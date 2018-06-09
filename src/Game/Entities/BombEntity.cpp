/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BombEntity.cpp
*/

#include "../../../include/Game/Entities/BombEntity.hpp"
#include "../../../include/Game/EntitiesMap.hpp"
#include "../../../include/Singletons/IrrManager.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Time.hpp"
#include "../../../include/Game/Entities/FireEntity.hpp"

BombEntity::BombEntity()
: AEntity("bomb"),
_start(),
_timeout(3000),
_range(1),
_exploded(false),
_autonomous(false)
{
	_stackable = false;
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("bomb/bomb.obj");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialType(irr::video::EMT_SOLID);
	_node->setScale({2.5, 2.5, 2.5});
	_start = Time::timestamp();
}

bool BombEntity::hasExploded() const
{
	return _exploded;
}

void BombEntity::setAutonomous(bool _autonomous)
{
	_exploded = false;
	BombEntity::_autonomous = _autonomous;
}

void BombEntity::update(EntitiesMap *map)
{
	if (Time::timestamp() > _start + _timeout)
		explode(map);
	AEntity::update(map);
}

void  BombEntity::detonate()
{
	_timeout = 0;
}

void BombEntity::explode(EntitiesMap *map)
{
	if (_exploded)
		return;
	if (_autonomous) {
		map->insert(new FireEntity({0, 0}, 2), getPosition());
		map->erase(this);
	} else {
		map->insert(new FireEntity({0, 0}, 2), getPosition());
	}
	_exploded = true;
}

BombEntity::~BombEntity()
{
	_node->remove();
}

void BombEntity::setRange(size_t _range)
{
	BombEntity::_range = _range;
}
