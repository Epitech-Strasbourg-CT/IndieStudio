/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** SphericalCoordinate.cpp
*/

#include "SphericalCoordinate.hpp"

SphericalCoordinate::SphericalCoordinate() :  _inc(0), _azimuth(0), _rayon(0), _origin()
{
}

SphericalCoordinate::SphericalCoordinate(irr::f32 inc, irr::f32 azimuth,
irr::f32 rayon) : _inc(inc), _azimuth(azimuth), _rayon(rayon), _origin()
{
}

SphericalCoordinate::SphericalCoordinate(irr::f32 inc, irr::f32 azimuth,
irr::f32 rayon, irr::core::vector3df origin) : _inc(inc), _azimuth(azimuth), _rayon(rayon), _origin(origin)
{
}

irr::core::vector3df SphericalCoordinate::calc()
{
	irr::core::vector3df ret = {
		_rayon * sinf(_azimuth) * sinf(_inc),
		_rayon * cosf(_azimuth),
		_rayon * sinf(_azimuth) * cosf(_inc)
	};
	ret.X += _origin.X;
	ret.Y += _origin.Y;
	ret.Z += _origin.Z;
	return ret;
}

void SphericalCoordinate::setInc(irr::f32 inc)
{
	_inc = inc;
}

void SphericalCoordinate::setAzimuth(irr::f32 azimuth)
{
	_azimuth = azimuth;
}

void SphericalCoordinate::setRayon(irr::f32 rayon)
{
	_rayon = rayon;
}

void SphericalCoordinate::addInc(irr::f32 inc)
{
	_inc += inc;
}

void SphericalCoordinate::addAzimuth(irr::f32 azimuth)
{
	_azimuth += azimuth;
}

void SphericalCoordinate::addRayon(irr::f32 rayon)
{
	_rayon += rayon;
}

void SphericalCoordinate::setOrigin(irr::core::vector3df const &origin)
{
	_origin = origin;
}

irr::f32 SphericalCoordinate::getInc()
{
	return _inc;
}

irr::f32 SphericalCoordinate::getAzimuth()
{
	return _azimuth;
}

irr::f32 SphericalCoordinate::getRayon()
{
	return _rayon;
}
