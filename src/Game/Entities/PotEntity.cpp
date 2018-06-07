/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PotEntity.cpp
*/

#include "../../../include/Game/Entities/PotEntity.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Singletons/IrrManager.hpp"

PotEntity::PotEntity() : AEntity("Pot")
{
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("block/Pot.dae");
	_stackable = false;
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	//_node->setMaterialTexture(0, am.loadTexture("block/Pot.png"));
	_node->setScale({15, 15, 15});
	_node->setRotation({-90, 0, 0});
}

void PotEntity::updateRender()
{
	AEntity::updateRender();
}
