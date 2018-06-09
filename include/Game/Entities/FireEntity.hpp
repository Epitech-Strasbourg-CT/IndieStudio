/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** FireEntity.hpp
*/

#ifndef BOMBERMAN_FIREENTTITY_HPP
#define BOMBERMAN_FIREENTTITY_HPP

#include "../../../include/Game/AEntity.hpp"

class FireEntity : public AEntity {
public:
	FireEntity(const irr::core::vector2di &spread = {0, 0}, size_t size = 0);
	void update(EntitiesMap *map) override;
	void dump (std::ostream &s) const;
	void load(std::istream &s);
	void spread(EntitiesMap *map);
	void collide(AEntity &entity) override;
	virtual ~FireEntity();
private:
	struct serialize {
		int spreadDirX;
		int spreadDirY;
		size_t spreadSize;
		bool spreaded;
		size_t updateCycle;
	};

	irr::core::vector2di _spreadDir;
	size_t _spreadSize;
	bool _spreaded;
	size_t _updateCycle;
};


#endif /* !BOMBERMAN_FIREENTTITY_HPP */
