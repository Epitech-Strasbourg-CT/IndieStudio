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
	AEntity(const std::string &);
	virtual ~AEntity() = default;
	void collide(AEntity &);
	void update(EntitiesMap *);
	void updateRender();
	std::vector<std::string> getAttrs(const std::vector<std::string> &);
	void extractAttrs(const std::vector<std::string> &);
	const Vector2DI &getMapPos() const;
	const Vector3DF &getNodePos() const;
	void dump(std::ostream &s) const;
	void load(std::istream &s);

protected:
	irr::scene::ISceneNode *_node;
	Vector2DI _pos;
private:
	struct serialize {
		irr::s32 x;
		irr::s32 y;
	};

	std::string _type;
};

std::ostream &operator<<(std::ostream &, const AEntity &);
AEntity &operator>>(std::istream &, AEntity &);
