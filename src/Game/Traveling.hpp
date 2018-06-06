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
	Traveling(const irr::core::vector3df &finalLook);

	~Traveling();
	void push(size_t time, const irr::core::vector3df &coor);
	void update(irr::scene::ICameraSceneNode &cam);
	void init(irr::scene::ICameraSceneNode &cam);
	int isFinished();
	void setFinalTime(size_t final);
	void setFolow(irr::f32 len);
	void setEndExactitude(irr::f32 endExac);
	void setEndFollow(irr::f32 len);

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

	irr::scene::ISceneNode *_cube;

	void moveCameraToEnd(irr::scene::ICameraSceneNode &cam);
};

#endif /* !BOMBERMAN_TRAVELING_HPP */
