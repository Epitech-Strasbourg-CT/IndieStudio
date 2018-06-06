/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PlayerEntity.cpp
*/

#include "../../../include/Game/Entities/PlayerEntity.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Singletons/IrrManager.hpp"

PlayerEntity::PlayerEntity() : AEntity("player"), ATrackable(), Controllable()
{
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("player/link-idle.ms3d");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialTexture(0, am.loadTexture("player/player1.png"));
	_node->setScale({15, 15, 15});

	// region move

	addEvent(MOVE_LEFT/*MOVE_UP*/, [this]() {
		//TODO tryMove with pool
		this->_node->setRotation({0, 90, 0});
		this->dirTop(1);
		auto EntityPos = this->AEntity::getPosition();
		auto MovablePos = this->AMovable::getPosition();
		if (MovablePos.Y > BORDERY + 1) {
			std::cout << "case TOP\n";
			EntityPos.Y += 1;
			MovablePos.Y = 0;
			this->AMovable::setPosition(MovablePos);
			this->AEntity::setPosition(EntityPos);
		}
	});

	addEvent(MOVE_RIGHT/*MOVE_DOWN*/, [this]() {
		//TODO tryMove with pool
		this->_node->setRotation({0, 90 + 180, 0});
		this->dirBottom(1);
		auto EntityPos = this->AEntity::getPosition();
		auto MovablePos = this->AMovable::getPosition();
		if (MovablePos.Y < 0) {
			std::cout << "case DOWN\n";
			EntityPos.Y -= 1;
			MovablePos.Y = BORDERY;
			this->AMovable::setPosition(MovablePos);
			this->AEntity::setPosition(EntityPos);
		}
	});

	addEvent(MOVE_DOWN/*MOVE_LEFT*/, [this]() {
		//TODO tryMove with pool
		this->_node->setRotation({0, 0, 0});
		this->dirLeft(1);
		auto EntityPos = this->AEntity::getPosition();
		auto MovablePos = this->AMovable::getPosition();
		if (MovablePos.X < 0) {
			std::cout << "case LEFT\n";
			EntityPos.X -= 1;
			MovablePos.X = BORDERX;
			this->AMovable::setPosition(MovablePos);
			this->AEntity::setPosition(EntityPos);
		}
	});
	addEvent(MOVE_UP/*MOVE_RIGHT*/, [this]() {
		//TODO tryMove with pool
		this->_node->setRotation({0, 180, 0});
		this->dirRight(1);
		auto EntityPos = this->AEntity::getPosition();
		auto MovablePos = this->AMovable::getPosition();
		if (MovablePos.X > BORDERX + 1) {
			std::cout << "case RIGHT\n";
			EntityPos.X += 1;
			MovablePos.X = 0;
			this->AMovable::setPosition(MovablePos);
			this->AEntity::setPosition(EntityPos);
		}
	});
	// endregion
}

void PlayerEntity::updateRender()
{

	auto nodePos = _node->getPosition();
	auto pos = calculateConvertedPosition();
	irr::core::vector2di Opos = AMovable::getPosition();
	auto origin = getOrigin();

	Opos.X /= ENTITY_SIZE_X;
	Opos.Y /= ENTITY_SIZE_Y;
	if (origin.X + pos.X + Opos.X != nodePos.X ||
	    origin.Z + pos.Y + Opos.Y != nodePos.Z) {
		nodePos.Y = origin.Y;
		nodePos.X = origin.X + pos.X + Opos.X;
		nodePos.Z = origin.Z + pos.Y + Opos.Y;
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

void PlayerEntity::update(EntitiesMap *map)
{
	Controllable::update();
	AEntity::update(map);
}
