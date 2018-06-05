/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PlayerEntity.cpp
*/

#include "../../../include/Game/Entities/PlayerEntity.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Singletons/IrrManager.hpp"

PlayerEntity::PlayerEntity() : AEntity("player"), Controllable()
{
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("sydney.md2");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialTexture(0, am.loadTexture("sydney.bmp"));
	addEvent(MOVE_UP, [this]() { this->dirTop(0.3); });
	addEvent(MOVE_DOWN, [this]() { this->dirBottom(0.3); });
	addEvent(MOVE_LEFT, [this]() { this->dirLeft(0.3); });
	addEvent(MOVE_RIGHT, [this]() { this->dirRight(0.3); });
}

void PlayerEntity::update()
{
	Controllable::update();
}

void PlayerEntity::updateRender()
{
	AEntity::updateRender();
}

void PlayerEntity::dump(std::ostream &s) const
{
	AEntity::dump(s);
	Controllable::dump(s);
	struct PlayerEntity::serialize ser = {};
	auto se = std::unique_ptr<char>(new char[sizeof(ser)]);
	memcpy(se.get(), &ser, sizeof(ser));
	s.write(se.get(), sizeof(ser));
}

void PlayerEntity::load(std::istream &s)
{
	AEntity::load(s);
	Controllable::load(s);
	struct PlayerEntity::serialize ser;
	auto se = std::unique_ptr<char>(new char[sizeof(ser)]);
	s.read(se.get(), sizeof(ser));
	memcpy(&ser, se.get(), sizeof(ser));
}
