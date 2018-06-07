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

GameState::GameState(AStateShare &_share) : AState(_share)
{
	auto mycam = IrrManager::getInstance().getSmgr()->addCameraSceneNodeFPS();
	auto pos = mycam->getPosition();
	pos.Y = 300;
	pos.Z = -300;
	mycam->setPosition(pos);
	_emap.generate();
}

GameState::GameState(AStateShare &_share, std::string &filename) : GameState(_share)
{
//	SaveManager::save(_emap, filename);
}

void GameState::update()
{
	_emap.update();
}

void GameState::load()
{
}

void GameState::updateRender()
{
	_emap.updateRender();
	AState::updateRender();
}
