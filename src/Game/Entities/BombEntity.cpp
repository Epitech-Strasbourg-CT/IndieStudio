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

BombEntity::BombEntity()
: AEntity("Bomb"),
_start(),
_timeout(3000),
_exploded(false),
_autonomous(false)
{
	_stackable = false;
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	//auto mesh = am.loadMesh("bomb/bomb.obj");
	auto mesh = am.loadMesh("rupees/rupee.obj");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	//_node->setMaterialType(irr::video::EMT_SOLID);
	_node->setScale({0.1, 0.1, 0.1});
	_node->setRotation({90, 0, 0});
	_node->setMaterialTexture(0, AssetsPool::getInstance().loadTexture("rupees/Rupee.0.png"));
	_start = Time::timestamp();
}

bool BombEntity::hasExploded() const
{
	return _exploded;
}

void BombEntity::setAutonomous(bool _autonomous)
{
	BombEntity::_autonomous = _autonomous;
}



void BombEntity::update(EntitiesMap *map)
{
	if (Time::timestamp() > _start + _timeout)
		explode(map);
	AEntity::update(map);
}

void BombEntity::explode(EntitiesMap *map)
{
//	if (_autonomous) {
//		map->erase(this);
//	} else {
		_exploded = true;
//	}
}

BombEntity::~BombEntity()
{
	_node->remove();
}
