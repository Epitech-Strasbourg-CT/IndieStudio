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
	irr::scene::ISceneNode *node = smgr->addMeshSceneNode(mesh);
	auto texture = AssetsPool::getInstance().loadTexture("tree.png");
	node->setMaterialTexture(0, texture);
	node->setPosition(irr::core::vector3df(0,0, -47));
	AState::load();
	StateMachine::getInstance().push(new MenuState, true);
}

void BackgroundState::unload()
{
	AState::unload();
}
