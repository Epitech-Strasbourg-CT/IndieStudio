/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PlayerEntity.hpp
*/

#pragma once

#include "../../Abstracts/ABombDropper.hpp"
#include "../AEntity.hpp"
#include "../AMovable.hpp"
#include "../Controllable.hpp"
#include "AAnimatedEntity.hpp"

#define ANGLE_SUP 180
#define BORDERX 10.0
#define BORDERY 10.0

class PlayerEntity : public ABombDropper,
                     public Controllable,
                     public AAnimatedEntity,
                     public AMovable<int> {
public:
	PlayerEntity(unsigned playerSkinId = 1);
	virtual ~PlayerEntity();

	void reloadSkin();
	void reverseDir();
	void speedUp();
	void update(EntitiesMap *map) override;
	bool updatePosition(EntitiesMap *map);
	void updateRender() override;
	void updateRenderDir();
	void updateRenderPosition();
	void dump (std::ostream &s) const;
	void load(std::istream &s);
	void kill();
	bool isIncorporel() const;
	void setIncorporel();
	unsigned getPlayerSkinId() const;
private:
	struct serialize {
		unsigned playerSkinId;
		bool incorporel;
		int moveCoef;
		int reverseCycles;
		int lookX;
		int lookY;
		bool alive;
		ControllerType ctType;
	};

	void addAllEvent();
	unsigned _playerSkinId;
	irr::core::vector2di _old;
	irr::core::vector2di _look;
	irr::core::vector2di getNewPosition();
	bool _incorporel;
	bool _alive;
	int _moveCoef;
	int _reverseCycles;
};
