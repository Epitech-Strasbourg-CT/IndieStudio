/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PlayerEntity.cpp
*/

#include "../../../include/Game/Entities/PlayerEntity.hpp"
#include "../../../include/Singletons/IrrManager.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"

PlayerEntity::PlayerEntity()
: AEntity("Player"), Controllable()
{
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("sydney.md2");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialTexture(0, am.loadTexture("sydney.bmp"));
	addEvent(MOVE_UP, [this]() {
		this->dirTop(0.3);
	});
	addEvent(MOVE_DOWN, [this]() {
		this->dirBottom(0.3);
	});
	addEvent(MOVE_LEFT, [this]() {
		this->dirLeft(0.3);
	});
	addEvent(MOVE_RIGHT, [this]() {
		this->dirRight(0.3);
	});
}

void PlayerEntity::update()
{
	Controllable::update();
}

void PlayerEntity::updateRender()
{
	if (getPos() != _staticPosition) {
		auto pos = getOrigin();
		pos.X += getPos().X;
		pos.Y += getPos().Y;
		_node->setPosition(pos);
	}
	AEntity::updateRender();
}
