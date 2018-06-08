/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BlockEntity.cpp
*/

#include "../../../include/Game/Entities/BlockEntity.hpp"
#include "../../../include/Singletons/IrrManager.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"

BlockEntity::BlockEntity() : AEntity("block")
{
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("block/Block.obj");
	_stackable = false;
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialTexture(0, am.loadTexture("block/Brick.png"));
	_node->setScale({0.11, 0.11, 0.11});
}
