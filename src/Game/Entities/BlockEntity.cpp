/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BlockEntity.cpp
*/

#include "../../../include/Game/Entities/BlockEntity.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Singletons/IrrManager.hpp"

BlockEntity::BlockEntity() : AEntity("Pot")
{
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("pot/Pot.dae");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialTexture(0, am.loadTexture("pot/Pot.png"));
	_node->setScale({15, 15, 15});
	_node->setRotation({-90, 0, 0});
}

void BlockEntity::updateRender()
{
	AEntity::updateRender();
}
