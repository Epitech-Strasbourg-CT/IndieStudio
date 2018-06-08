/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** FireEntity.cpp
*/
#include "../../../include/Game/EntitiesMap.hpp"
#include "../../../include/Game/Entities/FireEntity.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"

int FireEntity::insertion = 0;

FireEntity::FireEntity(const irr::core::vector2di &spread, size_t size)
: AEntity("Fire"), _spreadDir(spread), _spreadSize(size), _spreaded(false)
{
	FireEntity::insertion += 1;
	std::cout << "Fire : " << this << " " << FireEntity::insertion << std::endl;
	_stackable = true;
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("bomb/bomb.obj");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialType(irr::video::EMT_SOLID);
	_node->setScale({2, 2, 2});
//	_stackable = true;
//	auto &im = IrrManager::getInstance();
//	auto &am = AssetsPool::getInstance();
//	auto mesh = am.loadMesh("rupee/rupee.obj");
//	_node = im.getSmgr()->addMeshSceneNode(mesh);
//	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//	_node->setScale({0.1, 0.1, 0.1});
//	_node->setMaterialTexture(0, am.loadTexture("rupee/Rupee.0.png"));
}

void FireEntity::spread(EntitiesMap *map)
{
	if (_spreadSize == 0 || _spreaded)
		return;
	auto pos = getPosition();
	if (_spreadDir.X == 0 && _spreadDir.Y == 0) {
		map->insert(new FireEntity({0, 1}, _spreadSize - 1), pos + irr::core::vector2di(0, 1));
		map->insert(new FireEntity({0, -1}, _spreadSize - 1), pos + irr::core::vector2di(0, -1));
		map->insert(new FireEntity({1, 0}, _spreadSize - 1), pos + irr::core::vector2di(1, 0));
		map->insert(new FireEntity({-1, 0}, _spreadSize - 1), pos + irr::core::vector2di(-1, 0));
	} else
		map->insert(new FireEntity(_spreadDir, _spreadSize - 1), pos + _spreadDir);
	_spreaded = true;
}

void FireEntity::update(EntitiesMap *map)
{
	this->spread(map);
	AEntity::update(map);
}
