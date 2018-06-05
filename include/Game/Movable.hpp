/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AMovable.hpp
*/

#ifndef BOMBERMAN_AMOVABLE_HPP
	#define BOMBERMAN_AMOVABLE_HPP

	#include <irrlicht.h>

template<typename T>
class AMovable {
public:
	AMovable() : _pos()
	{
	}

	~AMovable() = default;
	void dirLeft(T val)
	{
		_pos.X -= val;
	}

	void dirRight(T val)
	{
		_pos.X += val;
	}

	void dirTop(T val)
	{
		_pos.Y += val;
	}

	void dirBottom(T val)
	{
		_pos.Y -= val;
	}

	AMovable &operator=(irr::core::vector2d<T> &other)
	{
		_pos.X = other.X;
		_pos.Y = other.Y;
		return *this;
	}

	irr::core::vector2d<T> operator+=(irr::core::vector2d<T> &other)
	{
		_pos.X += other.X;
		_pos.Y += other.Y;
		return _pos;
	}

	irr::core::vector2d<T> operator-=(irr::core::vector2d<T> &other)
	{
		_pos.X += other.X;
		_pos.Y += other.Y;
		return _pos;
	}

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

private:
	irr::core::vector2d<T> _pos;
};

#endif /* !BOMBERMAN_AMOVABLE_HPP */