/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** GameState.cpp
*/

#include <algorithm>
#include "../../include/States/GameState.hpp"
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/Game/SaveManager.hpp"
#include "../../include/Game/BKeyboardController.hpp"
#include "../../include/States/PauseState.hpp"
#include "../../include/States/PodiumState.hpp"

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
	static size_t nbPlayerTot = 4;

	animCam();
	if (getSharedResources().isKeyPressed(irr::KEY_ESCAPE))
		StateMachine::getInstance().push(new PauseState(getSharedResources()), false);
	else {
		auto nbPlayer = _share.getMap()->update();
		auto podium = _share.getMap()->getPodium();
		if (nbPlayer == 1) {
			addLastPlayerDead(podium);
			StateMachine::getInstance().push(new PodiumState(_share), false);
		}
		if (nbPlayer < nbPlayerTot) {
			for (auto i = 4 - nbPlayerTot; i < (nbPlayerTot - nbPlayer) + (4 - nbPlayerTot); i++) {
				addDeadPlayer(podium[i], i);
			}
			nbPlayerTot = nbPlayer;
		}
	}
//			StateMachine::getInstance().push(new TransitionEndGameState(_share), false);
	AssetsPool::getInstance().cleanSound();
	//TODO Call this when the game is finished
}

void GameState::addDeadPlayer(int idPlayer, int rank)
{
	irr::scene::IAnimatedMeshSceneNode *mesh = IrrManager::getInstance().getSmgr()->addAnimatedMeshSceneNode(
	dynamic_cast<irr::scene::IAnimatedMesh *>(AssetsPool::getInstance().loadMesh("player/link-happy.ms3d")));
	mesh->setMaterialTexture(0, AssetsPool::getInstance().loadTexture("player/player" + std::to_string(idPlayer + 1) + "-happy.png"));
	mesh->setScale({4, 4, 4});
	mesh->setRotation({0, 90, 0});
	mesh->setPosition({static_cast<irr::f32>(685 + rank * -6), 65, 640});
	mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	mesh->setMaterialType(irr::video::EMT_SOLID);
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
	auto step = static_cast<irr::f32>((2.0 * 3.1415) / 1000.0);
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

void GameState::addLastPlayerDead(std::vector<int> podium)
{
	std::vector<int> id = {0, 1, 2, 3};
	auto iterator = id.begin();

	for (auto elem : podium) {
		std::remove_if(id.begin(), id.end(), [elem](int val) { return elem == val; });
		iterator += 1;
	}
	addDeadPlayer(id[0], 3);
}
