/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#pragma once

#include "ATrackable.hpp"
#include <iostream>
#include <irrlicht.h>
#include <regex>

using Vector3DF = irr::core::vector3df;
using Vector2DF = irr::core::vector2df;

using Vector3DI = irr::core::vector3di;
using Vector2DI = irr::core::vector2di;

class EntitiesMap;

class AEntity : public ATrackable<int> {
public:
	explicit AEntity(const std::string & = "entity");
	virtual ~AEntity() = default;

	virtual void collide(AEntity &);
	bool isStackable() const;

	virtual void update(EntitiesMap *);
	virtual void updateRender();

	virtual void dump(std::ostream &s) const;
	virtual void load(std::istream &s);


	const Vector3DF &getOrigin() const;

private:
	struct serialize {
		irr::s32 x;
		irr::s32 y;
	};
	std::string _type;
	Vector3DF _origin;

protected:
	irr::scene::ISceneNode *_node;
	bool _stackable;
};

std::ostream &operator<<(std::ostream &, const AEntity &);
AEntity &operator>>(std::istream &, AEntity &);
