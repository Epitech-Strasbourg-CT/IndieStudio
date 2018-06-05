/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** ATrackable.hpp
*/

#pragma once

#include <irrlicht.h>

template <typename T> class ATrackable {
public:
	ATrackable() : _pos()
	{
	}

	virtual ~ATrackable() = default;

	irr::core::vector2d<T> getPos()
	{
		return _pos;
	}

	T getPosX()
	{
		return _pos.X;
	}

	T getPosY()
	{
		return _pos.Y;
	}

protected:
	irr::core::vector2d<T> _pos;
};
