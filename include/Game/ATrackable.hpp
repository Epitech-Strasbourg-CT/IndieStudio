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
	ATrackable() : _position()
	{
	}

	virtual ~ATrackable() = default;

	const irr::core::vector2d<T> &getPosition() const
	{
		return _position;
	}

	T getPosX()
	{
		return _position.X;
	}

	T getPosY()
	{
		return _position.Y;
	}

	void setPosition(const irr::core::vector2d<T> &_pos)
	{
		ATrackable::_position = _pos;
	}

protected:
	irr::core::vector2d<T> _position;
};
