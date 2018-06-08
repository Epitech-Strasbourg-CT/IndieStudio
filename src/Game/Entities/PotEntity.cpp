/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PotEntity.cpp
*/

#include "../../../include/Game/Entities/PotEntity.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Singletons/IrrManager.hpp"

PotEntity::PotEntity() : AEntity("pot")
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
