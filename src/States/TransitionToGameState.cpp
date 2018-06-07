/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** TransitionToGameState.cpp
*/

#include <iostream>
#include "../../include/States/TransitionToGameState.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/States/GameState.hpp"

TransitionToGameState::TransitionToGameState(AStateShare &_share) : AState(
_share), _trav(dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam")), {690, 60, 685}, 1.1)
{
	_trav.setFolow(0.04);
	_trav.setEndFollow(0.01);
	_trav.setAccelEndFollow(0.002);
	_trav.setEndExactitude(0.1);
	_trav.push(30, {-100, 150, 0});
	_trav.push(30, {100, 190, 500});
	_trav.push(30, {300, 150, 650});
	_trav.push(30, {500, 150, 800});
	_trav.push(50, {690, 130, 720});
}

void TransitionToGameState::update()
{
	auto &cam = dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam"));

	if (_trav.isFinished() == 2) {
		auto &sm = StateMachine::getInstance();
		sm.push(new GameState(_share), false);
	} else
		_trav.update(cam);
}

