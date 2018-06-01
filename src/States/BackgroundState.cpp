/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BackgroundState.cpp
*/

#include "../../include/States/BackgroundState.hpp"
#include "../../include/Singletons/GameManager.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/States/MenuState.hpp"

void BackgroundState::update()
{
}

void BackgroundState::load()
{
	auto smgr = GameManager::getInstance().getSmgr();
	auto &assetsPool = AssetsPool::getInstance();
	irr::scene::IMesh *mesh = assetsPool.loadMesh("tree.obj");
	_node = smgr->addMeshSceneNode(mesh);
	auto texture = AssetsPool::getInstance().loadTexture("tree.png");
	_node->setMaterialTexture(0, texture);
	_node->setPosition(irr::core::vector3df(0,0, -47));
	AState::load();
}

void BackgroundState::unload()
{
	_node->remove();
	AState::unload();
}

void BackgroundState::transitionPop()
{
	AState::transitionPop();
	StateMachine::getInstance().pop();
}

void BackgroundState::transitionPush()
{
	AState::transitionPush();
	StateMachine::getInstance().push(new MenuState(_share), true);
}

BackgroundState::BackgroundState(AStateShare &_share) : AState(_share)
{
}
