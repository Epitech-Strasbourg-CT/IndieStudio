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
#include "../../../include/Game/ControllerFactory.hpp"

PlayerEntity::PlayerEntity(unsigned playerSkinId)
: ABombDropper(), AAnimatedEntity("player"), AMovable(), Controllable(),
_old(), _look(), _alive(true), _playerSkinId(playerSkinId), _reverse(1),
_reverseCycles(0), _id(playerSkinId)
{
	_correction.X = static_cast<irr::f32>(ENTITY_SIZE_X / 2);
	_correction.Y = static_cast<irr::f32>(ENTITY_SIZE_Y / 2);
	AMovable::setPosition(
		irr::core::vector2di(static_cast<irr::s32>(BORDERX / 2),
			static_cast<irr::s32>(BORDERY / 2)));
	_old = AMovable::getPosition();
	_look.X = (playerSkinId % 2 == 0) ? 1 : -1;
	_look.Y = (playerSkinId == 1 || playerSkinId == 2) ? 1 : -1;
	reloadSkin();
	selectAnimation("idle");
	addAllEvent();
}

void PlayerEntity::reloadSkin()
{
	cleanAnimationNodes();
	_node = addAnimationNode("idle", "player/link-idle.ms3d",
		"player/player" + std::to_string(_playerSkinId) + ".png");
	_node->setScale({4, 4, 4});
	_node = addAnimationNode("run", "player/link-run.ms3d",
		"player/player" + std::to_string(_playerSkinId) + ".png");
	_node->setScale({4, 4, 4});
}

void PlayerEntity::addAllEvent()
{
	addEvent(MOVE_UP, KEY_DOWN, [this]() {
		this->dirBottom(1 * this->_reverse);
	});
	addEvent(MOVE_DOWN, KEY_DOWN, [this]() {
		this->dirTop(1 * this->_reverse);
	});
	addEvent(MOVE_LEFT, KEY_DOWN, [this]() {
		this->dirRight(1 * this->_reverse);
	});
	addEvent(MOVE_RIGHT, KEY_DOWN, [this]() {
		this->dirLeft(1 * this->_reverse);
	});
	addEvent(DROP_BOMB, KEY_PRESSED, [this]() {
		this->dropBomb(AEntity::getPosX(), AEntity::getPosY());
	});
}

void PlayerEntity::update(EntitiesMap *map)
{
	updatePosition(map);
	Controllable::update(map);
	ABombDropper::update(map);
	AEntity::update(map);
	if (!_alive)
		map->erase(this);
	if (_reverseCycles == 0 && _reverse == -1)
		_reverse = 1;
	else if (_reverseCycles > 0)
		_reverseCycles--;
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
	_node->setRotation(irr::core::vector3df(0, static_cast<irr::f32>(dir), 0));
}

irr::core::vector2di PlayerEntity::getNewPosition()
{
	auto dirM = AMovable::getPosition() - _old;
	auto newEPos = AEntity::getPosition();
	newEPos.X -= (_old.X + dirM.X < 0);
	newEPos.X += (_old.X + dirM.X > BORDERX);
	newEPos.Y -= (_old.Y + dirM.Y < 0);
	newEPos.Y += (_old.Y + dirM.Y > BORDERY);
	return newEPos;

}

bool PlayerEntity::updatePosition(EntitiesMap *map)
{
	auto mPos = AMovable::getPosition();
	if (_old == mPos) {
		selectAnimation("idle");
		return false;
	}
	selectAnimation("run");
	auto ePos = AEntity::getPosition();
	auto mDir = mPos - _old;
	auto ePosNew = getNewPosition();
	auto dirP = ePosNew - ePos;
	auto diag = abs(dirP.X) + abs(dirP.Y) == 1;
	_look = mDir;
	if (ePos != ePosNew && diag && map->canMoveTo(ePosNew)) {
		if (dirP.X != 0)
			mPos.X = static_cast<int>(dirP.X > 0 ? 0 : BORDERX);
		if (dirP.Y != 0)
			mPos.Y = static_cast<int>(dirP.Y > 0 ? 0 : BORDERY);
		this->AMovable::setPosition(mPos);
		map->moveTo(this, ePosNew);
		_old = mPos - mDir;
	} else if (ePos != ePosNew && (!map->canMoveTo(ePosNew) || !diag))
		AMovable::setPosition(_old);
	else
		_old = mPos;
	return true;
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
	struct PlayerEntity::serialize ser = {_playerSkinId, _look.X, _look.Y,
		_alive, _controller->getType()};
	if (_controller)
		ser.ctType = _controller->getType();
	auto se = std::unique_ptr<char[]>(new char[sizeof(ser)]);
	memcpy(se.get(), &ser, sizeof(ser));
	s.write(se.get(), sizeof(ser));
}

void PlayerEntity::load(std::istream &s)
{
	AEntity::load(s);
	Controllable::load(s);
	struct PlayerEntity::serialize ser;
	auto se = std::unique_ptr<char[]>(new char[sizeof(ser)]);
	s.read(se.get(), sizeof(ser));
	memcpy(&ser, se.get(), sizeof(ser));
	_playerSkinId = ser.playerSkinId;
	_look.X = ser.lookX;
	_look.Y = ser.lookY;
	_alive = ser.alive;
	reloadSkin();
	ControllerFactory cf;
	auto c = cf.createController(ser.ctType, _playerSkinId);
	AController::bindEntityToController(*c.get(), *this);
	c.release();
}

void PlayerEntity::kill()
{
	_alive = false;
}

PlayerEntity::~PlayerEntity()
{
	AssetsPool::getInstance().loadSound(AssetsPool::DEATH, false)->setIsPaused(false);
	cleanAnimationNodes();
}

size_t PlayerEntity::getId()
{
	return _id;
}

void PlayerEntity::reverseDir()
{
	_reverseCycles = 180;
	_reverse = -1;
}
