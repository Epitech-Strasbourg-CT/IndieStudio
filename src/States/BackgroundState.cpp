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
#include "../../include/States/GameState.hpp"

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
	_node->setPosition(
	irr::core::vector3df(0, -1, static_cast<irr::f32>(-47.38)));
	_node->setScale({1000, 1000, 1000});
	_share.addSharedNode("menu", _node);

	loadCharacter();
	loadSkyBox();
	loadMap();
	auto er = EventReceiver::getInstance();
	AState::load();
}

void BackgroundState::loadCharacter()
{
	auto smgr = IrrManager::getInstance().getSmgr();
	auto &assetsPool = AssetsPool::getInstance();
	irr::scene::IAnimatedMesh *mesh = dynamic_cast<irr::scene::IAnimatedMesh *>(assetsPool.loadMesh("player/link-idle.ms3d"));
	if (!mesh)
		throw std::runtime_error("Cannot instantiate menu player");

	for (auto i = 0; i < 4; i++) {
		_node = smgr->addAnimatedMeshSceneNode(mesh);
		_node->setMaterialTexture(0, assetsPool.loadTexture("player/player" + std::to_string(i + 1) + ".png"));
		_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_node->setMaterialType(irr::video::EMT_SOLID);
		_node->setScale({25, 25, 25});
		_node->setRotation({0, static_cast<irr::f32>(-100 + i * 20), 0});
		_node->setPosition({static_cast<irr::f32>(100 + i * 30), 20,
				    static_cast<irr::f32>(-300 - i * 20)});
		_share.addSharedNode("player" + std::to_string(i + 1), _node);
	}
}

void BackgroundState::loadSkyBox()
{
	auto driver = IrrManager::getInstance().getDriver();
	auto sb = IrrManager::getInstance().getSmgr()->addSkyBoxSceneNode(
	driver->getTexture("assets/textures/skybox/sky_up.png"),
	driver->getTexture("assets/textures/skybox/sky_down.jpg"),
	driver->getTexture("assets/textures/skybox/sky_left.png"),
	driver->getTexture("assets/textures/skybox/sky_right.png"),
	driver->getTexture("assets/textures/skybox/sky_front.png"),
	driver->getTexture("assets/textures/skybox/sky_back.png"));

	_share.addSharedNode("skybox", sb);
}

void BackgroundState::unload()
{
	_share.delSharedNode("menu");
	_share.delSharedNode("skybox");
	for (auto i = 0; i < 4; i++)
		_share.delSharedNode("player" + std::to_string(i + 1));
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
//	StateMachine::getInstance().push(new MenuState(_share), true);
	StateMachine::getInstance().push(new GameState(_share), true);
}

void BackgroundState::loadMap()
{
	auto smgr = IrrManager::getInstance().getSmgr();
	auto &assetsPool = AssetsPool::getInstance();
	auto *mesh = assetsPool.loadMesh("map/map.obj");
	if (!mesh)
		throw std::runtime_error("Cannot instantiate map");

	_node = smgr->addMeshSceneNode(mesh);
	_node->setPosition({700, 0, 600});
	_node->setScale({500, 500, 500});
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialType(irr::video::EMT_SOLID);
	_share.addSharedNode("map", _node);
}
