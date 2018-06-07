/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AIChooseState.cpp
*/

#include <iostream>
#include "../../include/States/AIChooseState.hpp"

AIChooseState::AIChooseState(AStateShare &_share) : AState(_share),
_trav(dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam")), {170, 52, -300}, 0.1)
{
	_trav.setFinalTime(60);
	_trav.setFolow(0.04);
	_trav.setEndFollow(0.04);
	_trav.setEndExactitude(5);
	_trav.setAccelEndFollow(0.01);
//	_trav.push(50, {0, 0, 0});
//	_trav.push(50, {130, 70, -500});
//	_trav.push(50, {100, 120, -400});
	_trav.push(50, {100, 40, -400});
}

void AIChooseState::update()
{
	auto &cam = dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam"));

//	std::cout << cam.getPosition().X << " " << cam.getPosition().Y << " " << cam.getPosition().Z << std::endl;
//	cam.setPosition({100, 40, -400});
//	cam.setTarget({450, 100, 100});
	_trav.update(cam);
//	std::cout << _trav.isFinished() << std::endl;
	AState::update();
}
