/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** Traveling.hpp
*/

#ifndef BOMBERMAN_TRAVELING_HPP
	#define BOMBERMAN_TRAVELING_HPP

	#include <irrlicht.h>
	#include <vector>

class Traveling {
public:
	Traveling(irr::scene::ICameraSceneNode &cam, const irr::core::vector3df &finalLook, irr::f32 startPointRatio = 0.5);
	~Traveling();
	void push(size_t time, const irr::core::vector3df &coor);
	void update(irr::scene::ICameraSceneNode &cam);
	int isFinished();
	void setFinalTime(size_t final);
	void setFolow(irr::f32 len);
	void setEndExactitude(irr::f32 endExac);
	void setEndFollow(irr::f32 len);
	void setAccelEndFollow(irr::f32 accel);

private:
	void movePoint(irr::scene::ICameraSceneNode &cam);
	void camFollowPoint(irr::scene::ICameraSceneNode &cam);
	void movePointToEnd(irr::scene::ICameraSceneNode &cam);
	bool isVectSupEq(irr::core::vector3df const &vect, irr::f32 val);
	bool isVectInfEq(irr::core::vector3df const &vect, irr::f32 val);
	std::vector<std::pair<size_t, irr::core::vector3df>> _coor;
	irr::core::vector3df _startPoint;
	irr::core::vector3df _point;
	irr::core::vector3df _finalLook;
	bool _needMoveCamToPoint;
	bool _needMovePoint;
	size_t _cur;
	size_t _finalTime;
	irr::f32 _follow;
	irr::f32 _endExac;
	irr::f32 _endFollow;
	irr::f32 _accelEndFollow;
	irr::f32 _startPointRatio;

	irr::scene::ISceneNode *_cube;

	void moveCameraToEnd(irr::scene::ICameraSceneNode &cam);
};

#endif /* !BOMBERMAN_TRAVELING_HPP */
