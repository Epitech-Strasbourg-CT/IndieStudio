/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PlayerEntity.cpp
*/

#include "../../../include/Game/Entities/PlayerEntity.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Singletons/IrrManager.hpp"

PlayerEntity::PlayerEntity()
: AEntity("player"),
AMovable(),
Controllable(),
_old(AMovable::getPosition())
{
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("player/link-idle.ms3d");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialTexture(0, am.loadTexture("player/player1.png"));
	_node->setScale({15, 15, 15});
	// region move

	addEvent(MOVE_UP, [this]() {
		this->dirTop(1);
	});
	addEvent(MOVE_DOWN, [this]() {
		this->dirBottom(1);
	});
	addEvent(MOVE_LEFT, [this]() {
		this->dirLeft(1);
	});
	addEvent(MOVE_RIGHT, [this]() {
		this->dirRight(1);
	});
	// endregion
}


void PlayerEntity::update(EntitiesMap *map)
{
	if (_old != AMovable::getPosition()) {
		auto EntityPos = this->AEntity::getPosition();
		auto MovablePos = this->AMovable::getPosition();
		if (MovablePos.X > BORDERX) {
			EntityPos.X += 1;
			MovablePos.X = 0;
		}
		this->AMovable::setPosition(MovablePos);
		this->AEntity::setPosition(EntityPos);
	}
	Controllable::update();
	AEntity::update(map);
}

void PlayerEntity::updateRender()
{
	auto nodePos = _node->getPosition();
	auto pos = calculateConvertedPosition();
	irr::core::vector2di Opos = AMovable::getPosition();
	irr::core::vector2df Rpos {};
	auto origin = getOrigin();

	Rpos.X = static_cast<irr::f32>(ENTITY_SIZE_X / BORDERX * static_cast<float>(Opos.X));
	Rpos.Y = static_cast<irr::f32>(ENTITY_SIZE_Y / BORDERY * static_cast<float>(Opos.Y));
	if (origin.X + pos.X + Rpos.X != nodePos.X ||
	    origin.Z + pos.Y + Rpos.Y != nodePos.Z) {
		nodePos.Y = origin.Y;
		nodePos.X = origin.X + pos.X + Rpos.X - _correction.X;
		nodePos.Z = origin.Z + pos.Y + Rpos.Y - _correction.Y;
		_node->setPosition(nodePos);
	}
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
