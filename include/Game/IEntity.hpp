/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#pragma once

#include <iostream>

class IEntity {
public:
	virtual ~IEntity() = default;
	virtual void dump(std::ostream &) const = 0;
	virtual void save(std::istream &) = 0;
protected:
private:
};

std::ostream &operator<<(std::ostream &, const IEntity &);
IEntity &operator>>(std::istream &, IEntity &);
