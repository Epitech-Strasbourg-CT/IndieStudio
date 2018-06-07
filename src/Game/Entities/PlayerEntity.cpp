/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PlayerEntity.cpp
*/

#include "../../../include/Game/Entities/PlayerEntity.hpp"
#include "../../../include/Game/EntitiesMap.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Singletons/IrrManager.hpp"

PlayerEntity::PlayerEntity()
	: ABombDropper(), AEntity("player"), AMovable(), Controllable(),
	_old(AMovable::getPosition()), _look(1, 0)
{
	_correction.X = static_cast<irr::f32>(ENTITY_SIZE_X / 2);
	_correction.Y = static_cast<irr::f32>(ENTITY_SIZE_Y / 2);
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("player/link-idle.ms3d");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialTexture(0, am.loadTexture("player/player1.png"));
	_node->setScale({15, 15, 15});
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
	addEvent(DROP_BOMB, [this]() {
		this->dropBomb(AMovable::getPosX(), AMovable::getPosY());
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
	ABombDropper::update(map);
	AEntity::update(map);
}

void PlayerEntity::updateRenderPosition()
{
	auto nodePos = _node->getPosition();
	auto pos = calculateConvertedPosition();
	irr::core::vector2di Opos = AMovable::getPosition();
	irr::core::vector2df Rpos{};
	auto origin = getOrigin();

	Rpos.X = static_cast<irr::f32>
	(ENTITY_SIZE_X / BORDERX * static_cast<float>(Opos.X));
	Rpos.Y = static_cast<irr::f32>
	(ENTITY_SIZE_Y / BORDERY * static_cast<float>(Opos.Y));
	if (origin.X + pos.X + Rpos.X != nodePos.X ||
		origin.Z + pos.Y + Rpos.Y != nodePos.Z) {
		nodePos.Y = origin.Y;
		nodePos.X = origin.X + pos.X + Rpos.X - _correction.X;
		nodePos.Z = origin.Z + pos.Y + Rpos.Y - _correction.Y;
		_node->setPosition(nodePos);
	}
}

void PlayerEntity::updateRenderDir()
{
	auto dir = atan2(-_look.Y, _look.X) * 180.0 / 3.1415;
	dir += ANGLE_SUP;
	_node->setRotation({0, dir, 0});
}

void PlayerEntity::updatePosition(EntitiesMap *map)
{
	auto mPos = AMovable::getPosition();
	auto ePos = AEntity::getPosition();
	if (_old != mPos) {
		auto dirM = mPos - _old;
		auto newEPos = AEntity::getPosition();
		newEPos.X -= (_old.X + dirM.X < 0);
		newEPos.X += (_old.X + dirM.X > BORDERX);
		newEPos.Y -= (_old.Y + dirM.Y < 0);
		newEPos.Y += (_old.Y + dirM.Y > BORDERY);
		_look = dirM;
		if (ePos != newEPos && map->canMoveTo(newEPos)) {
			auto dirP = newEPos - ePos;
			if (dirP.X != 0)
				mPos.X = static_cast<int>(dirP.X > 0 ? 0 :
					BORDERX);
			if (dirP.Y != 0)
				mPos.Y = static_cast<int>(dirP.Y > 0 ? 0 :
					BORDERY);
			this->AMovable::setPosition(mPos);
			map->moveTo(this, newEPos);
		} else if (ePos != newEPos && !map->canMoveTo(newEPos))
			AMovable::setPosition(_old);
		else
			_old = mPos;
	}
}

void PlayerEntity::updateRender()
{
	updateRenderDir();
	updateRenderPosition();
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
