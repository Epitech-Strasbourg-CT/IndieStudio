/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BombEntity.cpp
*/

#include "../../../include/Game/Entities/BombEntity.hpp"
#include "../../../include/Singletons/IrrManager.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"

BombEntity::BombEntity(): AEntity("bomb")
{
	_stackable = false;
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("bomb/bomb.obj");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialType(irr::video::EMT_SOLID);
	_node->setScale({2, 2, 2});
}

bool BombEntity::hasExploded() const
{
	return false;
}

void BombEntity::updateRender()
{
	AEntity::updateRender();
}
