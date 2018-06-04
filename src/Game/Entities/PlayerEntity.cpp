/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PlayerEntity.cpp
*/

#include "PlayerEntity.hpp"
#include "../../../include/Singletons/IrrManager.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"

PlayerEntity::PlayerEntity(AController &controller)
: AEntity("Player"),
Controllable(_controller)
{
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("sydney.md2");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialTexture(0, am.loadTexture("sydney.bmp"));
	_controller.registerControllable(this);
	addEvent(MOVE_UP, [this]() {
		this->dirTop(0.1);
	});
	addEvent(MOVE_DOWN, [this]() {
		this->dirBottom(0.1);
	});
	addEvent(MOVE_LEFT, [this]() {
		this->dirLeft(0.1);
	});
	addEvent(MOVE_RIGHT, [this]() {
		this->dirRight(0.1);
	});
}

void PlayerEntity::update()
{
	Controllable::update();
}
