/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AIChooseState.cpp
*/

#include <iostream>
#include "../../include/States/AIChooseState.hpp"

AIChooseState::AIChooseState(AStateShare &_share) : AState(_share), _trav({170, 52, -300})
{
	_trav.init(dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam")));
	_trav.setFinalTime(200);
	_trav.setFolow(0.04);
	_trav.setEndFollow(0.04);
	_trav.setEndExactitude(5);
	_trav.push(0, _share.getSharedNode("cam").getPosition());
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
