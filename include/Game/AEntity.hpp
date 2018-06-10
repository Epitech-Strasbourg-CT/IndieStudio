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
#include <ik_ISound.h>

#define ENTITY_SIZE_X 5.0
#define ENTITY_SIZE_Y 4.0

class EntitiesMap;

class AEntity : public ATrackable<int> {
public:
	explicit AEntity(const std::string &, int x = 0, int y = 0);
	virtual ~AEntity() = default;

	virtual void collide(AEntity &);
	virtual bool isStackable(const AEntity * = nullptr) const;
	bool isInsertable() const;

	virtual void update(EntitiesMap *);
	virtual void updateRender();
	irr::core::vector2d<float> calculateConvertedPosition() const;

	const std::string &getType() const;

	virtual void dump(std::ostream &s) const;
	virtual void load(std::istream &s);

	const irr::core::vector3df &getOrigin() const;
	void setOrigin(const irr::core::vector3df &vec);

	const irr::core::vector3df &getNodePosition() const;
	void setNodePosition(const irr::core::vector3df &vec);
	const irr::core::vector3df &getNodeRotation() const;
	void setNodeRotation(const irr::core::vector3df &vec);

private:
	struct serialize {
		irr::s32 x;
		irr::s32 y;
	};
	std::string _type;
	irr::core::vector3df _origin;
protected:
	irr::core::vector2df _correction;
	irr::scene::ISceneNode *_node;
	bool _stackable;
	bool _insertable;
};

std::ostream &operator<<(std::ostream &, const AEntity &);
AEntity &operator>>(std::istream &, AEntity &);
