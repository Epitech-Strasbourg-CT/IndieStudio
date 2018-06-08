/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** TransitionEndGameState.cpp
*/

#include "../../include/States/TransitionEndGameState.hpp"

TransitionEndGameState::TransitionEndGameState(AStateShare &_share) : AState(_share),
_trav(dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam")), {675, 80, 400}, 1)
{
	_trav.push(50, {675, 75, 610});
	_trav.push(50, {675, 80, 555});
}

void TransitionEndGameState::update()
{
	_trav.update(dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam")));
	AState::update();
}
