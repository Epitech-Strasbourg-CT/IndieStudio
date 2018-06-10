/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** TransitionToMenuState.cpp
*/

#include "../../include/States/TransitionToMenuState.hpp"
#include "../../include/Singletons/StateMachine.hpp"

TransitionToMenuState::TransitionToMenuState(AStateShare &_share) : AState(_share),
_trav(dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam")), {450, 0, 100}, 2)
{
	_trav.setEndExactitude(0.1);
	_trav.push(30, {500, 150, 800});
	_trav.push(30, {300, 200, 650});
	_trav.push(30, {100, 250, 500});
	_trav.push(30, {-100, 300, 0});
	_trav.push(70, _share.getCoor("menu"));
	_share.delCoor("menu");
}

void TransitionToMenuState::update()
{
	if (_trav.isFinished() == 2) {
		StateMachine::getInstance().popUntil("menu");
		_share.popMusic(AssetsPool::GAME);
		return;
	}
	_trav.update(dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam")));
	AState::update();
}

const std::string TransitionToMenuState::getName() const
{
	return "transitionToMenu";
}
