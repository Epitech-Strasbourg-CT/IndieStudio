/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AState.cpp
*/
#include <stdexcept>
#include <string>
#include "../../include/States/SplashState.hpp"
#include "../../include/Time.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/GameManager.hpp"
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/States/MenuState.hpp"
#include "../../include/States/BackgroundState.hpp"

void SplashState::update()
{
	if (_start + _duration < Time::timestamp()) {
		StateMachine::getInstance().push(new BackgroundState(_share), false);
		return;
	}
	GameManager::getInstance().getDriver()->draw2DImage(
	AssetsPool::getInstance().loadTexture("bomber.jpg"),
	irr::core::position2d<irr::s32>(0,0),
	irr::core::rect<irr::s32>(0,0,800,600),
	0,
	irr::video::SColor(255, 255, 255, 255),
	false);
}

void SplashState::load()
{
	auto cam = GameManager::getInstance().getSmgr()
	->addCameraSceneNode();
	if (!cam)
		throw std::runtime_error("Can't create a new Camera.");
	cam->setPosition(irr::core::vector3df(0, 0, -50));
	_nodes.push_back(cam);
	auto mesh = AssetsPool::getInstance().loadMesh("sydney.md2");
	auto n = GameManager::getInstance().getSmgr()->addMeshSceneNode(mesh);
	auto texture = AssetsPool::getInstance().loadTexture("sydney.bmp");


	_nodes.push_back(n);
	n->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	n->setMaterialTexture(0, texture);

	_start = Time::timestamp();
	AState::load();
}

void SplashState::unload()
{
	std::cout << "Unload Splash" << std::endl;
	for (auto &n : _nodes)
		n->remove();
	_nodes.clear();
	AState::unload();
}

SplashState::SplashState(AStateShare &_share)
: AState(_share),
_nodes(),
_start(),
_duration(1000)
{
}
