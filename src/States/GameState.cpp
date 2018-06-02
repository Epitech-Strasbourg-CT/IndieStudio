/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** GameState.cpp
*/

#include "../../include/States/GameState.hpp"
#include "../../include/Singletons/GameManager.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/AssetsPool.hpp"

void GameState::update()
{
	if (_share.isKeyDown(irr::KEY_RIGHT)) {
		auto pos = _node->getPosition();
		pos.X += 0.1;
		_node->setPosition(pos);
	}

}

GameState::GameState(AStateShare &_share) : AState(_share)
{
}

void GameState::load()
{
	auto &er = EventReceiver::getInstance();
	auto &gm = GameManager::getInstance();
	auto &ap = AssetsPool::getInstance();

	auto &n = _share.getSharedNode("tree");
	n.setVisible(false);
	addAlteredNode(&n, [](irr::scene::ISceneNode *n) {
		n->setVisible(true);
	});
	auto mesh = ap.loadMesh("sydney.md2");
	_node = gm.getSmgr()->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialTexture(0, ap.loadTexture("sydney.bmp"));
	AState::load();
}

void GameState::unload()
{
	AState::unload();
}

void GameState::transitionPop()
{
	AState::transitionPop();
}

void GameState::transitionPush()
{
	AState::transitionPush();
}
