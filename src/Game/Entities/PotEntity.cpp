/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PotEntity.cpp
*/

#include "../../../include/Game/Entities/PotEntity.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Singletons/IrrManager.hpp"
#include "../../../include/Game/EntitiesMap.hpp"
#include "../../../include/Game/Entities/ABonusEntity.hpp"
#include "../../../include/Game/Bonus/UpBombBonus.hpp"
#include "../../../include/Game/Bonus/UpFireBonus.hpp"
#include "../../../include/Game/Bonus/InvertBonus.hpp"
#include "../../../include/Game/Bonus/ResetFireRangeBonus.hpp"
#include "../../../include/Game/Bonus/UpSpeedBonus.hpp"
#include "../../../include/Game/Bonus/IncorporelBonus.hpp"

const std::map<int, std::function<AEntity *()>> PotEntity::_gemGen = {
	{55, []() {
		return nullptr;
	}},
	{20, []() {
		return new IncorporelBonus();
	}},
	{20, []() {
		return new UpSpeedBonus();
	}},
	{20, []() {
		return new UpBombBonus();
	}},
	{10, []() {
		return new UpFireBonus();
	}},
	{10, []() {
		return new ResetFireRangeBonus();
	}},
	{5, []() {
		return new InvertBonus();
	}}
};

PotEntity::PotEntity() : AEntity("pot"), _broken(false)
{
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto mesh = am.loadMesh("block/Pot.dae");
	_stackable = false;
	_node = im.getSmgr()->addMeshSceneNode(mesh);
	_node->setScale({3.5, 3.5, 3.5});
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setRotation({-90, 0, 0});
}

void PotEntity::updateRender()
{
	AEntity::updateRender();
}

void PotEntity::breakMe()
{
	_broken = true;
}

void PotEntity::genRandomGem(EntitiesMap *map)
{
	auto sum = 0;
	for (auto &n : PotEntity::_gemGen)
		sum += n.first;
	auto floor = rand() % sum;
	AEntity *elem = 0;
	auto floorSeek = 0;
	for (auto &n : PotEntity::_gemGen) {
		floorSeek += n.first;
		if (floor < floorSeek) {
			elem = n.second();
			break;
		}
	}
	if (elem)
		map->insert(elem, getPosition());
}

void PotEntity::update(EntitiesMap *map)
{
	if (_broken) {
		genRandomGem(map);
		map->erase(this);
	}
	AEntity::update(map);
}

void PotEntity::dump(std::ostream &s) const
{
	AEntity::dump(s);
	struct PotEntity::serialize ser = {_broken};
	auto se = std::unique_ptr<char[]>(new char[sizeof(ser)]);
	memcpy(se.get(), &ser, sizeof(ser));
	s.write(se.get(), sizeof(ser));
}

void PotEntity::load(std::istream &s)
{
	AEntity::load(s);
	struct PotEntity::serialize ser;
	auto se = std::unique_ptr<char[]>(new char[sizeof(ser)]);
	s.read(se.get(), sizeof(ser));
	memcpy(&ser, se.get(), sizeof(ser));
	_broken = ser.broken;
}

bool PotEntity::isStackable(const AEntity *entity) const
{
	if (entity && entity->getType() == "player") {
		auto player = dynamic_cast<const PlayerEntity *>(entity);
		if (player)
			return player->isIncorporel();
	}
	return _stackable;
}

PotEntity::~PotEntity()
{
	AssetsPool::getInstance().loadSound(AssetsPool::POT, false)->setIsPaused(false);
	_node->remove();
}
