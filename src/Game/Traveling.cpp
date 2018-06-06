/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** Traveling.cpp
*/

#include <iostream>
#include "Traveling.hpp"
#include "../../include/Singletons/IrrManager.hpp"

Traveling::Traveling(irr::core::vector3df const &finalLook) : _coor(),
_startPoint(), _point(), _finalLook(finalLook), _needMoveCamToPoint(true),
_needMovePoint(true), _cur(0), _finalTime(60), _follow(0.1), _endExac(5), _endFollow(0.1)
{
	_cube = IrrManager::getInstance().getSmgr()->addCubeSceneNode();
	_cube->setVisible(false);
}

Traveling::~Traveling()
{
}

void Traveling::init(irr::scene::ICameraSceneNode &cam)
{
	auto targetPos = cam.getPosition();
	std::cout << cam.getTarget().X << " " << cam.getTarget().Y << " " << cam.getTarget().Z << std::endl;
	irr::core::vector3df vect({
				  (cam.getTarget().X - cam.getPosition().X) * static_cast<irr::f32>(0.5),
				  (cam.getTarget().Y - cam.getPosition().Y) * static_cast<irr::f32>(0.5),
				  (cam.getTarget().Z - cam.getPosition().Z) * static_cast<irr::f32>(0.5)
  	});
//	std::cout << vect.X << " " << vect.Y << " " << vect.Z << std::endl;
	targetPos += vect;
	_cube->setPosition(targetPos);
	cam.setTarget(targetPos);
	_startPoint = targetPos;
	_point = targetPos;
//	_point = cam.getPosition();
}

void Traveling::push(size_t time, irr::core::vector3df const &coor)
{
	_coor.emplace_back(time, coor);
}

void Traveling::update(irr::scene::ICameraSceneNode &cam)
{
	if (_coor.size() == 1) {
		if (_needMoveCamToPoint)
			movePointToEnd(cam);
		if (_needMovePoint)
			moveCameraToEnd(cam);
		return;
	}
	movePoint(cam);
}

void Traveling::movePoint(irr::scene::ICameraSceneNode &cam)
{
	irr::core::vector3df c1;
	if (_coor[0].first == 0)
		c1 = _startPoint;
	else
		c1 = _coor[0].second;
	auto c2 = _coor[1];
	auto time = c2.first;
	irr::core::vector3df vect({
				  (c2.second.X - c1.X) / static_cast<irr::f32>(time),
				  (c2.second.Y - c1.Y) / static_cast<irr::f32>(time),
				  (c2.second.Z - c1.Z) / static_cast<irr::f32>(time)
				  });
//	std::cout << vect.X << " " << vect.Y << " " << vect.Z << std::endl;
	_point += vect;
	_cube->setPosition(_point);
	_cur += 1;
	cam.setTarget(_point);
	camFollowPoint(cam);
	if (_cur == time) {
		_coor.erase(_coor.begin());
		_cur = 0;
	}
}
void Traveling::camFollowPoint(irr::scene::ICameraSceneNode &cam)
{
	auto camPos = cam.getPosition();
	irr::core::vector3df vect({
				  static_cast<irr::f32>((_point.X - camPos.X) * _follow),
				  static_cast<irr::f32>((_point.Y - camPos.Y) * _follow),
				  static_cast<irr::f32>((_point.Z - camPos.Z) * _follow)
	});

	camPos += vect;
	cam.setPosition(camPos);
}

void Traveling::movePointToEnd(irr::scene::ICameraSceneNode &cam)
{
	auto c1 = _coor[0].second;
	irr::core::vector3df vect({
				  (_finalLook.X - c1.X) / static_cast<irr::f32>(_finalTime),
				  (_finalLook.Y - c1.Y) / static_cast<irr::f32>(_finalTime),
				  (_finalLook.Z - c1.Z) / static_cast<irr::f32>(_finalTime)
	});

	_point += vect;
	_cur += 1;
	if (_cur == _finalTime) {
		_needMoveCamToPoint = false;
		_cur = 0;
	}
	_cube->setPosition(_point);
	cam.setTarget(_point);
}

void Traveling::moveCameraToEnd(irr::scene::ICameraSceneNode &cam)
{
	auto c2 = _coor[0];
	auto camPos = cam.getPosition();
	irr::core::vector3df vect({
				  (c2.second.X - camPos.X) * static_cast<irr::f32>(_endFollow),
				  (c2.second.Y - camPos.Y) * static_cast<irr::f32>(_endFollow),
				  (c2.second.Z - camPos.Z) * static_cast<irr::f32>(_endFollow)
	});
	if (isVectSupEq((c2.second - camPos), -_endExac) && isVectInfEq((c2.second - camPos), _endExac))
		_needMovePoint = false;
	camPos += vect;
	cam.setPosition(camPos);
}

void Traveling::setFinalTime(size_t final)
{
	_finalTime = final;
}

int Traveling::isFinished()
{
	auto ret = 0;

	if (_coor.size() == 1 && !_needMovePoint) {
		ret += 1;
		if (!_needMoveCamToPoint)
			ret += 1;
	}
	return ret;
}

void Traveling::setFolow(irr::f32 len)
{
	if (len < 0 || len > 1)
		return;
	_follow = len;
}

bool Traveling::isVectSupEq(irr::core::vector3df const &vect, irr::f32 val)
{
	return vect.X >= val && vect.Y >= val && vect.Z >= val;
}

bool Traveling::isVectInfEq(irr::core::vector3df const &vect, irr::f32 val)
{
	return vect.X <= val && vect.Y <= val && vect.Z <= val;
}

void Traveling::setEndExactitude(irr::f32 endExac)
{
	if (endExac < 0)
		return;
	_endExac = endExac;
}

void Traveling::setEndFollow(irr::f32 len)
{
	if (len < 0 || len > 1)
		return;
	_endFollow = len;
}
