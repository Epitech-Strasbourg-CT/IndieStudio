/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BombEntity.cpp
*/

#include "../../../include/Game/Entities/BombEntity.hpp"
#include "../../../include/Game/EntitiesMap.hpp"
#include "../../../include/Singletons/IrrManager.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Time.hpp"
#include "../../../include/Game/Entities/FireEntity.hpp"

BombEntity::BombEntity()
: AEntity("bomb"),
_range(1),
_updateCycle(180),
_exploded(false),
_autonomous(false)
{
	_stackable = false;
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("bomb/bomb.obj");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialType(irr::video::EMT_SOLID);
	_node->setScale({2.5, 2.5, 2.5});
	AssetsPool::getInstance().loadSound(AssetsPool::BDROP, false)->setIsPaused(
		false);
}

bool BombEntity::hasExploded() const
{
	return _exploded;
}

void BombEntity::setAutonomous(bool _autonomous)
{
	_exploded = false;
	BombEntity::_autonomous = _autonomous;
}

void BombEntity::update(EntitiesMap *map)
{
	if (_updateCycle == 0)
		explode(map);
	AEntity::update(map);
	_updateCycle--;
}

void BombEntity::dump(std::ostream &s) const
{
	AEntity::dump(s);
	struct BombEntity::serialize ser = {_range, _updateCycle, false,
		true};
	auto se = std::unique_ptr<char[]>(new char[sizeof(ser)]);
	memcpy(se.get(), &ser, sizeof(ser));
	s.write(se.get(), sizeof(ser));
}

void BombEntity::load(std::istream &s)
{
	AEntity::load(s);
	struct BombEntity::serialize ser;
	auto se = std::unique_ptr<char[]>(new char[sizeof(ser)]);
	s.read(se.get(), sizeof(ser));
	memcpy(&ser, se.get(), sizeof(ser));
	_range = ser.range;
	_updateCycle = ser.updateCycle;
	_exploded = ser.exploded;
	_autonomous = ser.autonomous;
}

void  BombEntity::detonate()
{
	_updateCycle = 0;
}

void BombEntity::explode(EntitiesMap *map)
{
	if (_exploded)
		return;
	if (_autonomous) {
		map->insert(new FireEntity({0, 0}, _range), getPosition());
		map->erase(this);
	} else {
		map->insert(new FireEntity({0, 0}, _range), getPosition());
	}
	_exploded = true;
}

BombEntity::~BombEntity()
{
	AssetsPool::getInstance().loadSound(AssetsPool::BBLOW, false)->setIsPaused(false);
	_node->remove();
}

void BombEntity::setRange(size_t _range)
{
	BombEntity::_range = _range;
}
