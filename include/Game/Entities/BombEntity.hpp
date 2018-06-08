/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BombEntity.hpp
*/

#ifndef BOMBERMAN_BOMBENTITY_HPP
#define BOMBERMAN_BOMBENTITY_HPP


#include "../AEntity.hpp"

class BombEntity : public AEntity {
public:
	BombEntity();
	bool hasExploded() const;
	void setAutonomous(bool _utonomous);
	void explode(EntitiesMap *map);
	void update(EntitiesMap *map) override;
	virtual ~BombEntity();

private:
	size_t _start;
	size_t _timeout;
	bool _exploded;
	bool _autonomous;
};


#endif /* !BOMBERMAN_BOMBENTITY_HPP */
