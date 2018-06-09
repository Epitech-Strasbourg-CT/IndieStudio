/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** GameState.cpp
*/

#include "../../include/States/GameState.hpp"
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/Game/SaveManager.hpp"
#include "../../include/Game/BKeyboardController.hpp"
#include "../../include/States/PauseState.hpp"
#include "../../include/States/TransitionEndGameState.hpp"

GameState::GameState(AStateShare &_share) : AState(_share), _inc(0)
{
	_share.pushMusic(AssetsPool::getInstance().loadSound(AssetsPool::GAME, true));
}

GameState::GameState(AStateShare &_share, std::string &filename) : GameState(_share)
{
	_share.popMusic(AssetsPool::GAME);
}

void GameState::update()
{
	animCam();
	if (getSharedResources().isKeyPressed(irr::KEY_ESCAPE))
		StateMachine::getInstance().push(new PauseState(getSharedResources()), false);
	else
		_share.getMap()->update();

	//TODO Call this when the game is finished
//	StateMachine::getInstance().push(new TransitionEndGameState(_share), false);
}

void GameState::load()
{
}

void GameState::updateRender()
{
	_share.getMap()->updateRender();
	AState::updateRender();
}

void GameState::animCam()
{
	auto step = static_cast<irr::f32>((2.0 * M_PI) / 1000.0);
	auto min = static_cast<irr::f32>(115);
	auto max = static_cast<irr::f32>(120);
	auto &cam = dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam"));
	auto camPos = cam.getPosition();

	_inc += step;
	camPos.Y = static_cast<irr::f32>((sinf(_inc) - -1.0) * (max - min) / (1.0 - -1.0) + min);
	cam.setPosition(camPos);
}

const std::string GameState::getName() const
{
	return "game";
}
