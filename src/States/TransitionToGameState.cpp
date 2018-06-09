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

TransitionToGameState::TransitionToGameState(AStateShare &_share, const std::string &saveName) : AState(_share),
_trav(dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam")),
{690, 60, 690}, static_cast<irr::f32>(1.1)), _emap()
{
	if (saveName.empty())
		_emap.generate(_share.getIAState());
	else {
	//	SaveManager::save(_emap, saveManager);
	}
	_emap.updateInsert();
	_trav.setFolow(static_cast<irr::f32>(0.04));
	_trav.setEndFollow(static_cast<irr::f32>(0.01));
	_trav.setAccelEndFollow(static_cast<irr::f32>(0.002));
	_trav.setEndExactitude(static_cast<irr::f32>(0.1));
	_trav.push(30, {-100, 150, 0});
	_trav.push(30, {100, 190, 500});
	_trav.push(30, {300, 150, 650});
	_trav.push(30, {500, 150, 800});
	_trav.push(50, {690, 100, 715});
}

void TransitionToGameState::transitionPop()
{
	_share.setMap(nullptr);
	AState::transitionPop();
}

void TransitionToGameState::transitionPush(bool keep)
{
	_share.setMap(&_emap);
	AState::transitionPush(keep);
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

void TransitionToGameState::updateRender()
{
	_emap.updateRender();
	AState::updateRender();
}
