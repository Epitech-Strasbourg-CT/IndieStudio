/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BackgroundState.cpp
*/

#include "../../include/States/BackgroundState.hpp"
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/States/MenuState.hpp"

BackgroundState::BackgroundState(AStateShare &_share) : AState(_share)
{
}

void BackgroundState::load()
{
	auto smgr = IrrManager::getInstance().getSmgr();
	auto &assetsPool = AssetsPool::getInstance();
	irr::scene::IMesh *mesh = assetsPool.loadMesh("menu/menu.obj");
	_node = smgr->addMeshSceneNode(mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialType(irr::video::EMT_SOLID);
	_node->setPosition(irr::core::vector3df(0,-1, -47.38));
	_node->setScale({1000, 1000, 1000});
	_share.addSharedNode("menu", _node);

	auto er = EventReceiver::getInstance();
	AState::load();
}

void BackgroundState::unload()
{
	_share.delSharedNode("menu");
	_node->remove();
	AState::unload();
}

void BackgroundState::transitionPop()
{
	AState::transitionPop();
	StateMachine::getInstance().pop();
}

void BackgroundState::transitionPush(bool keep)
{
	AState::transitionPush(keep);
	StateMachine::getInstance().push(new MenuState(_share), true);
}
