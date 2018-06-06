/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AIChooseState.cpp
*/

#include <iostream>
#include "../../include/States/AIChooseState.hpp"

AIChooseState::AIChooseState(AStateShare &_share) : AState(_share)
{

}

void AIChooseState::update()
{
	auto &cam = dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam"));

	//std::cout << cam.getPosition().X << " " << cam.getPosition().Y << " " << cam.getPosition().Z << std::endl;
	cam.setPosition({100, 40, -400});
	cam.setTarget({450, 100, 100});
	AState::update();
}
