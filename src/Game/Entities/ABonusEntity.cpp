/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** ABonusEntity.cpp
*/

#include "../../../include/Game/Entities/ABonusEntity.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Game/Entities/FireEntity.hpp"

ABonusEntity::ABonusEntity(const std::string &name, RupeeColor color)
: AEntity(name),  _destroyed(false)
{
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("rupee/rupee.obj");
	_stackable = true;
	_insertable = true;
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	auto rupee = "rupee/Rupee." + std::to_string(color) + ".png";
	_node->setMaterialTexture(0, am.loadTexture(rupee));
	_node->setScale(irr::core::vector3df(
		static_cast<irr::f32 >(0.033),
		static_cast<irr::f32 >(0.02),
		static_cast<irr::f32 >(0.033)));
}

void ABonusEntity::update(EntitiesMap *map)
{
	AEntity::update(map);
	if (_destroyed)
		map->erase(this);
}

void ABonusEntity::dump(std::ostream &s) const
{
	AEntity::dump(s);
	struct ABonusEntity::serialize ser = {_destroyed};
	auto se = std::unique_ptr<char[]>(new char[sizeof(ser)]);
	memcpy(se.get(), &ser, sizeof(ser));
	s.write(se.get(), sizeof(ser));
}

void ABonusEntity::load(std::istream &s)
{
	AEntity::load(s);
	struct ABonusEntity::serialize ser;
	auto se = std::unique_ptr<char[]>(new char[sizeof(ser)]);
	s.read(se.get(), sizeof(ser));
	memcpy(&ser, se.get(), sizeof(ser));
	_destroyed = ser.destroyed;
}

void ABonusEntity::collide(AEntity &entity)
{
	std::map<std::string, std::function<void(AEntity *aEntity)>>
		collisions = {
		{"player",
			[this](AEntity *aEntity) {
				auto p = dynamic_cast<PlayerEntity *>(aEntity);
				this->playerChanging(p);
				this->destroy();
			}
		}

	};
	if (collisions.count(entity.getType()) > 0)
		collisions[entity.getType()](&entity);
	AEntity::collide(entity);
}

ABonusEntity::~ABonusEntity()
{
	AssetsPool::getInstance().loadSound(AssetsPool::RUPEE, false)->setIsPaused(false);
	_node->remove();
}

void ABonusEntity::destroy()
{
	this->_destroyed = true;
}
