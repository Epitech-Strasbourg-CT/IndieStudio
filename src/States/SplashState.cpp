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

irr::video::ITexture *texture;

void SplashState::update()
{
	GameManager::getInstance().getDriver()->draw2DImage(
	texture,
	irr::core::position2d<irr::s32>(0,0),
	irr::core::rect<irr::s32>(0,0,800,600),
	0,
	irr::video::SColor(255, 255, 255, 255),
	false);
}

SplashState::SplashState() : _mesh(nullptr), _node(nullptr)
{
}

void SplashState::load()
{
	GameManager::getInstance().getSmgr()->addCameraSceneNode();
	texture = GameManager::getInstance().getDriver()
	->getTexture("assets/bomber.jpg");
	GameManager::getInstance().getDriver()->makeColorKeyTexture(
	texture, irr::core::position2d<irr::s32>(0, 0));

	auto mdr = GameManager::getInstance().getDriver()
	->getTexture("assets/models/sydney.bmp");
	_mesh = AssetsPool::getInstance().loadMesh("sydney.md2");
	_node = GameManager::getInstance().getSmgr()->addMeshSceneNode(_mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialTexture(0, mdr);
	AState::load();
}

void SplashState::unload()
{
	AState::unload();
}
