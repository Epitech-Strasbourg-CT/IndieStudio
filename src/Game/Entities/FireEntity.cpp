/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** FireEntity.cpp
*/
#include "../../../include/Game/EntitiesMap.hpp"
#include "../../../include/Game/Entities/FireEntity.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Game/Entities/PotEntity.hpp"
#include "../../../include/Time.hpp"
#include "../../../include/Game/Entities/BombEntity.hpp"
#include "../../../include/Game/Entities/ABonusEntity.hpp"

FireEntity::FireEntity(const irr::core::vector2di &spread, size_t size)
	: AEntity("fire"), _spreadDir(spread), _spreadSize(size),
	_spreaded(false), _updateCycle(20)
{
	_stackable = true;
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("explosion/explode.obj");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setScale(irr::core::vector3df(3, 2, 3));
}

void FireEntity::spread(EntitiesMap *map)
{
	if (_spreadSize == 0 || _spreaded)
		return;
	auto pos = getPosition();
	if (_spreadDir.X == 0 && _spreadDir.Y == 0) {
		map->insert(new FireEntity({0, 1}, _spreadSize - 1), pos + irr::core::vector2di(0, 1));
		map->insert(new FireEntity({0, -1}, _spreadSize - 1), pos + irr::core::vector2di(0, -1));
		map->insert(new FireEntity({1, 0}, _spreadSize - 1), pos + irr::core::vector2di(1, 0));
		map->insert(new FireEntity({-1, 0}, _spreadSize - 1), pos + irr::core::vector2di(-1, 0));
	} else
		map->insert(new FireEntity(_spreadDir, _spreadSize - 1), pos + _spreadDir);
	_spreaded = true;
}

void FireEntity::update(EntitiesMap *map)
{
	this->spread(map);
	AEntity::update(map);
	if (_updateCycle == 0)
		map->erase(this);
	_updateCycle--;
}

void FireEntity::dump(std::ostream &s) const
{
	AEntity::dump(s);
	struct FireEntity::serialize ser = {_spreadDir.X, _spreadDir.Y,
		_spreadSize, _spreaded, _updateCycle};
	auto se = std::unique_ptr<char>(new char[sizeof(ser)]);
	memcpy(se.get(), &ser, sizeof(ser));
	s.write(se.get(), sizeof(ser));
}

void FireEntity::load(std::istream &s)
{
	AEntity::load(s);
	struct FireEntity::serialize ser;
	auto se = std::unique_ptr<char>(new char[sizeof(ser)]);
	s.read(se.get(), sizeof(ser));
	memcpy(&ser, se.get(), sizeof(ser));
	_spreadDir.X = ser.spreadDirX;
	_spreadDir.Y = ser.spreadDirY;
	_spreadSize = ser.spreadSize;
	_spreaded = ser.spreaded;
	_updateCycle = ser.updateCycle;
}

void FireEntity::collide(AEntity &entity)
{
	std::map<std::string, std::function<void(AEntity *aEntity)>>
	collisions = {
		{"pot",
			[this](AEntity *aEntity) {
				auto pot = dynamic_cast<PotEntity *>(aEntity);
				pot->breakMe();
				this->_spreaded = true;
				this->_spreadSize = 0;
			}
		}, {"bomb",
			[this](AEntity *aEntity) {
				auto bomb = dynamic_cast<BombEntity *>(aEntity);
				bomb->detonate();
			}
		}, {"Bonus",
			   [this](AEntity *aEntity) {
				   auto bonus = dynamic_cast<ABonusEntity *>(aEntity);
				   if (!_spreaded)
				        bonus->destroy();
			   }
		}, {"player",
			[this](AEntity *aEntity) {
				auto player = dynamic_cast<PlayerEntity *>(aEntity);
				player->kill();
			}
		}
	};
	if (collisions.count(entity.getType()) > 0)
		collisions[entity.getType()](&entity);
}

FireEntity::~FireEntity()
{
	_node->remove();
}
