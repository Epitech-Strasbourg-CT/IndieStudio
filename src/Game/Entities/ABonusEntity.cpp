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
	_node->remove();
}

void ABonusEntity::destroy()
{
	this->_destroyed = true;
}
