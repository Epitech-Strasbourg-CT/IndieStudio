/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BlockEntity.cpp
*/

#include "../../../include/Game/Entities/BlockEntity.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"
#include "../../../include/Singletons/IrrManager.hpp"

BlockEntity::BlockEntity() : AEntity("block")
{
}

void BlockEntity::update()
{
}

void BlockEntity::updateRender()
{
	if (getPos() != _staticPosition) {
		auto pos = getOrigin();
		pos.X += getPos().X;
		pos.Y += getPos().Y;
		_node->setPosition(pos);
	}
	AEntity::updateRender();
}

void BlockEntity::dump(std::ostream &s) const
{
	AEntity::dump(s);
	struct BlockEntity::serialize ser = {};
	auto se = std::unique_ptr<char>(new char[sizeof(ser)]);
	memcpy(se.get(), &ser, sizeof(ser));
	s.write(se.get(), sizeof(ser));
}

void BlockEntity::load(std::istream &s)
{
	AEntity::load(s);
	struct BlockEntity::serialize ser;
	auto se = std::unique_ptr<char>(new char[sizeof(ser)]);
	s.read(se.get(), sizeof(ser));
	memcpy(&ser, se.get(), sizeof(ser));
}
