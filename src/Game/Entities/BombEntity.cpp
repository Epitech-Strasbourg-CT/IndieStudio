/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BombEntity.cpp
*/

#include "../../../include/Game/Entities/BombEntity.hpp"
#include "../../../include/Singletons/IrrManager.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"

BombEntity::BombEntity(): AEntity("Bomb")
{
	_stackable = false;
	_correction.X = static_cast<irr::f32>(ENTITY_SIZE_X * 6 / 4);
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("bomb/bomb.obj");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setScale({10, 10, 10});
}

bool BombEntity::hasExploded() const
{
	return false;
}

void BombEntity::updateRender()
{
	AEntity::updateRender();
}
