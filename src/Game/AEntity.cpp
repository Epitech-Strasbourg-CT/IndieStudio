/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#include "../../include/Game/AEntity.hpp"

AEntity::AEntity(const std::string &type) : _type(type)
{
}

void AEntity::update(EntitiesMap *)
{
}

void AEntity::updateRender()
{
}

const Vector2DI &AEntity::getMapPos() const
{
	return (_pos);
}

const Vector3DF &AEntity::getNodePos() const
{
	return (_node->getPosition());
}

void AEntity::dump(std::ostream &s) const
{
	struct AEntity::serialize ser = {
//		x: _pos.X,
//		y: _pos.Y,
	};
	char *se = new char[sizeof(ser)];
	memcpy(se, &ser, sizeof(ser));
	s << _type;
	s.write("\0", 1);
	s.write(se, sizeof(ser));
}

void AEntity::load(std::istream &s)
{
	struct AEntity::serialize ser{};
	auto *se = new char[sizeof(ser)];

	s.read(se, sizeof(ser));
	memcpy(&ser, se, sizeof(ser));
//	_pos.X = ser.x;
//	_pos.Y = ser.y;
}

void AEntity::collide(AEntity &)
{

}

void AEntity::extractAttrs(const std::vector<std::string> &)
{

}

std::vector<std::string> AEntity::getAttrs(const std::vector<std::string> &)
{
	return std::vector<std::string>();
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
