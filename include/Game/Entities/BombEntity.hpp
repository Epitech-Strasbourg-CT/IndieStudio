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
	void dump (std::ostream &s) const;
	void load(std::istream &s);
	virtual ~BombEntity();
	void detonate();
	void setRange(size_t _range);
private:
	struct serialize {
		size_t range;
		size_t updateCycle;
		bool exploded;
		bool autonomous;
	};

	size_t _range;
	size_t _updateCycle;
	bool _exploded;
	bool _autonomous;
};


#endif /* !BOMBERMAN_BOMBENTITY_HPP */
