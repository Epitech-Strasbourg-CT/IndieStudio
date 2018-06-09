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
	AMovable() : _reverse(1)
	{
	}

	~AMovable() = default;
	void dirLeft(T val)
	{
		ATrackable<T>::_position.X -= val * _reverse;
	}

	void dirRight(T val)
	{
		ATrackable<T>::_position.X += val * _reverse;
	}

	void dirTop(T val)
	{
		ATrackable<T>::_position.Y += val * _reverse;
	}

	void dirBottom(T val)
	{
		ATrackable<T>::_position.Y -= val * _reverse;
	}

	void setReverse()
	{
		_reverse *= -1;
	}

	AMovable &operator=(irr::core::vector2d<T> &other)
	{
		ATrackable<T>::_position.X = other.X * _reverse;
		ATrackable<T>::_position.Y = other.Y * _reverse;
		return *this;
	}

	irr::core::vector2d<T> operator+=(irr::core::vector2d<T> &other)
	{
		ATrackable<T>::_position.X += other.X * _reverse;
		ATrackable<T>::_position.Y += other.Y * _reverse;
		return ATrackable<T>::_position;
	}

	irr::core::vector2d<T> operator-=(irr::core::vector2d<T> &other)
	{
		ATrackable<T>::_position.X += other.X * _reverse;
		ATrackable<T>::_position.Y += other.Y * _reverse;
		return ATrackable<T>::_position;
	}

private:
	int _reverse;
};

#endif /* !BOMBERMAN_AMOVABLE_HPP */