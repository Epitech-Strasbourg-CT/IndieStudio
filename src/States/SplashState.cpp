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
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/States/MenuState.hpp"
#include "../../include/States/BackgroundState.hpp"

void SplashState::update()
{
	if (_start + _duration < Time::timestamp()) {
		StateMachine::getInstance().push(new BackgroundState(_share), false);
		return;
	}
}

void SplashState::load()
{
	auto cam = IrrManager::getInstance().getSmgr()
	->addCameraSceneNode();
	if (!cam)
		throw std::runtime_error("Can't create a new Camera.");
	cam->setPosition(irr::core::vector3df(0, 0, -50));
	_nodes.push_back(cam);
	_start = Time::timestamp();
	AState::load();
}

void SplashState::unload()
{
	AState::unload();
}

SplashState::SplashState(AStateShare &_share)
: AState(_share),
_nodes(),
_start(),
_duration(1000)
{
}

void SplashState::draw()
{
	IrrManager::getInstance().getDriver()->draw2DImage(
	AssetsPool::getInstance().loadTexture("logo.png"),
	irr::core::position2d<irr::s32>(0,0),
	irr::core::rect<irr::s32>(0,0,500,200),
	0,
	irr::video::SColor(255, 255, 255, 255),
	false);
	AState::draw();
}
