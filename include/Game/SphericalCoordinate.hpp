/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** SphericalCoordinate.hpp
*/

#ifndef BOMBERMAN_SPHERICALCOORDINATE_HPP
	#define BOMBERMAN_SPHERICALCOORDINATE_HPP

	#include <irrlicht.h>

class SphericalCoordinate {
public:
	SphericalCoordinate();
	SphericalCoordinate(irr::f32 inc, irr::f32 azimuth, irr::f32 rayon);
	SphericalCoordinate(irr::f32 inc, irr::f32 azimuth, irr::f32 rayon, irr::core::vector3df origin);
	irr::core::vector3df calc();
	void setInc(irr::f32 inc);
	void setAzimuth(irr::f32 azimuth);
	void setRayon(irr::f32 rayon);
	void addInc(irr::f32 inc);
	void addAzimuth(irr::f32 azimuth);
	void addRayon(irr::f32 rayon);
	void setOrigin(irr::core::vector3df const &origin);

	irr::f32 getInc();
	irr::f32 getAzimuth();
	irr::f32 getRayon();

private:
	irr::f32 _inc;
	irr::f32 _azimuth;
	irr::f32 _rayon;
	irr::core::vector3df _origin;
};

#endif /* !BOMBERMAN_SPHERICALCOORDINATE_HPP */
