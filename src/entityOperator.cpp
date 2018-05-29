/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#include "IEntity.hpp"

std::ostream &operator<<(std::ostream &s, const IEntity &e)
{
	e.dump(s);
	return s;
}

IEntity &operator>>(std::istream &s, IEntity &e)
{
	e.save(s);
	return e;
}
