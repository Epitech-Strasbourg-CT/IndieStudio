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

PotEntity::PotEntity() : AEntity("pot"), _broken(false)
{
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("block/Pot.dae");
	_stackable = false;
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setScale({4, 4, 4});
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

void PotEntity::update(EntitiesMap *map)
{
	if (_broken)
		map->erase(this);
	AEntity::update(map);
}

PotEntity::~PotEntity()
{
	//free((void *)1);
	//std::cout << "DELETE POT" << std::endl;
	_node->remove();
}
