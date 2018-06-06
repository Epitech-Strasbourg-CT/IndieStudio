/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#include "../../include/Game/AEntity.hpp"

AEntity::AEntity(const std::string &type)
: ATrackable(), _type(type), _origin(), _node(), _stackable(true)
{
}

void AEntity::update(EntitiesMap *)
{
}

void AEntity::updateRender()
{
}

// region Save & load

void AEntity::dump(std::ostream &s) const
{
	struct AEntity::serialize ser = {_position.X, _position.Y};
	auto se = std::unique_ptr<char>(new char[sizeof(ser)]);
	memcpy(se.get(), &ser, sizeof(ser));
	s << _type;
	s.write("\0", 1);
	s.write(se.get(), sizeof(ser));
}

void AEntity::load(std::istream &s)
{
	struct AEntity::serialize ser {};
	auto se = std::unique_ptr<char>(new char[sizeof(ser)]);
	s.read(se.get(), sizeof(ser));
	memcpy(&ser, se.get(), sizeof(ser));
	setPosition({ser.x, ser.y});
}

std::ostream &operator<<(std::ostream &s, const AEntity &e)
{
	e.dump(s);
	return s;
}

AEntity &operator>>(std::istream &s, AEntity &e)
{
	e.load(s);
	return e;
}

// endregion

void AEntity::collide(AEntity &)
{
}

const Vector3DF &AEntity::getOrigin() const
{
	return _origin;
}

bool AEntity::isStackable() const
{
	return _stackable;
}
