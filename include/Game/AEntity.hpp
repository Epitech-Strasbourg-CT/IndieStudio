/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#pragma once

#include <iostream>
#include <irrlicht.h>
#include <regex>

using Vector3DF = irr::core::vector3df;
using Vector2DF = irr::core::vector2df;

using Vector3DI = irr::core::vector3di;
using Vector2DI = irr::core::vector2di;

class EntitiesMap;

class AEntity {
public:
	explicit AEntity(const std::string & = "entity");
	virtual ~AEntity() = default;
	void collide(AEntity &);
	void update(EntitiesMap *);
	virtual void updateRender();
	void dump(std::ostream &s) const;
	void load(std::istream &s);

	Vector2DI getMapPos() const;
	void setMapPos(const Vector2DI &position);

	const Vector2DF &getStaticPos() const;
	void setStaticPos(const Vector2DF &position);

	const Vector3DF &getOrigin() const;


private:
	struct serialize {
//		irr::s32 x;
//		irr::s32 y;
	};
	std::string _type;
	Vector3DF _origin;

protected:
	Vector2DF _staticPosition;
	irr::scene::ISceneNode *_node;
};

std::ostream &operator<<(std::ostream &, const AEntity &);
AEntity &operator>>(std::istream &, AEntity &);

