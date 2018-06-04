/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#pragma once

#include <iostream>
#include <irrlicht.h>

using Vector3DF = irr::core::vector3df;
using Vector2DF = irr::core::vector2df;

using Vector3DI = irr::core::vector3di;
using Vector2DI = irr::core::vector2di;

class AEntity {
public:
	AEntity();
	virtual ~AEntity() = default;
	void operator<<(const std::string &str);
	void operator>>(const std::string &str) const;
	void collide(AEntity &);
	void update();
	void updateRender();
	const Vector2DI &getPos() const;
protected:
private:
	std::string _type;
	irr::scene::ISceneNode *_node;
	Vector2DI _pos;
};
