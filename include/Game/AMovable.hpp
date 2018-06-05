/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AMovable.hpp
*/

#ifndef BOMBERMAN_AMOVABLE_HPP
#define BOMBERMAN_AMOVABLE_HPP

#include "ATrackable.hpp"
#include <irrlicht.h>

template <typename T> class AMovable : public virtual ATrackable<T> {
public:
	AMovable()
	{
	}

	~AMovable() = default;
	void dirLeft(T val)
	{
		ATrackable<T>::_pos.X -= val;
	}

	void dirRight(T val)
	{
		ATrackable<T>::_pos.X += val;
	}

	void dirTop(T val)
	{
		ATrackable<T>::_pos.Y += val;
	}

	void dirBottom(T val)
	{
		ATrackable<T>::_pos.Y -= val;
	}

	AMovable &operator=(irr::core::vector2d<T> &other)
	{
		ATrackable<T>::_pos.X = other.X;
		ATrackable<T>::_pos.Y = other.Y;
		return *this;
	}

	irr::core::vector2d<T> operator+=(irr::core::vector2d<T> &other)
	{
		ATrackable<T>::_pos.X += other.X;
		ATrackable<T>::_pos.Y += other.Y;
		return ATrackable<T>::_pos;
	}

	irr::core::vector2d<T> operator-=(irr::core::vector2d<T> &other)
	{
		ATrackable<T>::_pos.X += other.X;
		ATrackable<T>::_pos.Y += other.Y;
		return ATrackable<T>::_pos;
	}
};

#endif /* !BOMBERMAN_AMOVABLE_HPP */