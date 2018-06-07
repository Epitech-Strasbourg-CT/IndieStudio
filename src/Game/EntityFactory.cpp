/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#include "../../include/Game/EntityFactory.hpp"
#include "../../include/Game/Entities/PlayerEntity.hpp"
#include "../../include/Game/Entities/BlockEntity.hpp"

EntityFactory::EntityFactory() : _fac({{"entity", []() {
	return std::unique_ptr<AEntity>(new AEntity("entity"));
}}, {"player", []() {
	return std::unique_ptr<PlayerEntity>(new PlayerEntity());
}}, {"block", []() {
	return std::unique_ptr<BlockEntity>(new BlockEntity());
}}, {"bomb", []() {
	return std::unique_ptr<BombEntity>(new BombEntity());
}},})
{
}

EntityFactory::~EntityFactory()
{
}

std::unique_ptr<AEntity> EntityFactory::createEntity(const std::string &name)
{
	if (_fac.find(name) != _fac.end()) {
		return _fac.at(name)();
	} else
		throw std::runtime_error("entity not implemented yet");
}
