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

FireEntity::FireEntity(const irr::core::vector2di &spread, size_t size)
: AEntity("Fire"), _spreadDir(spread), _spreadSize(size), _spreaded(false), _duration(200)
{
	_start = Time::timestamp();
	_stackable = true;
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("explosion/explode.obj");
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	auto texture =
	AssetsPool::getInstance().loadTexture("explosion/explode.jpg");
	_node->setMaterialTexture(0, texture);
	_node->setScale(irr::core::vector3df(3, 2, 3));
}

void FireEntity::spread(EntitiesMap *map)
{
	if (_spreadSize == 0 || _spreaded)
		return;
	//std::cout << "SPREAD " << " " << this->_spreadDir.X << " "<< this->_spreadDir.Y<< std::endl;
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
	if (_start + _duration < Time::timestamp())
		map->erase(this);
}

void FireEntity::collide(AEntity &entity)
{
	std::map<std::string, std::function<void(AEntity *aEntity)>>
	collisions = {
		{"pot",
			[this](AEntity *aEntity) {
				auto pot = dynamic_cast<PotEntity *>(aEntity);
				pot->breakMe();
				//std::cout << "COLLIDE " << this << " " << this->_spreadDir.X << " "<< this->_spreadDir.Y << std::endl;
				this->_spreaded = true;
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
