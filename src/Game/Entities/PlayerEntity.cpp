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

	addEvent(MOVE_UP, [this]() {
		//TODO tryMove with pool
		this->dirTop(1);
		auto EntityPos = this->AEntity::getPosition();
		auto MovablePos = this->AMovable::getPosition();
		if (MovablePos.Y > BORDERY) {
			std::cout << "case TOP\n";
			EntityPos.Y += 1;
			MovablePos.Y = 0;
			this->AMovable::setPosition(MovablePos);
			this->AEntity::setPosition(EntityPos);
		}
	});

	addEvent(MOVE_DOWN, [this]() {
		//TODO tryMove with pool
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

	addEvent(MOVE_LEFT, [this]() {
		//TODO tryMove with pool
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
	addEvent(MOVE_RIGHT, [this]() {
		//TODO tryMove with pool
		this->dirRight(1);
		auto EntityPos = this->AEntity::getPosition();
		auto MovablePos = this->AMovable::getPosition();
		if (MovablePos.X > BORDERX) {
			std::cout << "case RIGHT\n";
			EntityPos.X += 1;
			MovablePos.X = 0;
			this->AMovable::setPosition(MovablePos);
			this->AEntity::setPosition(EntityPos);
		}
	});
	// endregion
}

void PlayerEntity::update()
{
	Controllable::update();
}

void PlayerEntity::updateRender()
{
	auto nodePos = _node->getPosition();
	auto pos = AEntity::getPosition();
	irr::core::vector2di Opos = AMovable::getPosition();
	auto origin = getOrigin();

	if (origin.X + pos.X * BORDERX + Opos.X != nodePos.X ||
	    origin.Y + pos.Y * BORDERY + Opos.Y != nodePos.Y) {
		nodePos.X = origin.X + pos.X * BORDERX + Opos.X;
		nodePos.Y = origin.Y + pos.Y * BORDERY + Opos.Y;
		_node->setPosition(nodePos);
	}
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
