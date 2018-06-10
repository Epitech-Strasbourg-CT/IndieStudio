/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#include "../../include/Game/EntityFactory.hpp"
#include "../../include/Game/Entities/PlayerEntity.hpp"
#include "../../include/Game/Entities/BlockEntity.hpp"
#include "../../include/Game/Entities/PotEntity.hpp"
#include "../../include/Game/Entities/FireEntity.hpp"
#include "../../include/Game/Entities/ABonusEntity.hpp"
#include "../../include/Game/Bonus/InvertBonus.hpp"
#include "../../include/Game/Bonus/ResetFireRangeBonus.hpp"
#include "../../include/Game/Bonus/UpBombBonus.hpp"
#include "../../include/Game/Bonus/UpFireBonus.hpp"

EntityFactory::EntityFactory() : _fac({{"entity", [](unsigned) {
	return std::unique_ptr<AEntity>(new AEntity("entity"));
}}, {"player", [](unsigned playerSkinId) {
	return std::unique_ptr<PlayerEntity>(new PlayerEntity(playerSkinId));
}}, {"block", [](unsigned) {
	return std::unique_ptr<BlockEntity>(new BlockEntity());
}}, {"bomb", [](unsigned) {
	return std::unique_ptr<BombEntity>(new BombEntity());
}}, {"pot", [](unsigned) {
	return std::unique_ptr<PotEntity>(new PotEntity());
}}, {"fire", [](unsigned) {
	return std::unique_ptr<FireEntity>(new FireEntity());
}}, {"invert_bonus", [](unsigned) {
	return std::unique_ptr<InvertBonus>(new InvertBonus());
}}, {"reduce_bonus", [](unsigned) {
	return std::unique_ptr<ResetFireRangeBonus>(new ResetFireRangeBonus());
}}, {"bomb_bonus", [](unsigned) {
	return std::unique_ptr<UpBombBonus>(new UpBombBonus());
}}, {"fire_bonus", [](unsigned) {
	return std::unique_ptr<UpFireBonus>(new UpFireBonus());
}},})
{
}

std::unique_ptr<AEntity> EntityFactory::createEntity(const std::string &name,
	unsigned playerSkinId)
{
	if (_fac.find(name) != _fac.end()) {
		return _fac.at(name)(playerSkinId);
	} else
		throw std::runtime_error("entity not implemented yet");
}
