/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AState.cpp
*/
#include <stdexcept>
#include <string>
#include "../../include/SplashState.hpp"
#include "../../include/Singletons.hpp"
#include "../../include/Time.hpp"

void SplashState::update()
{
	if (_endTime < Time::timestamp()) {
		stateMachine.pop();
	}
}

SplashState::SplashState()
{
	_mesh = gameManager.getSmgr()->getMesh("assets/sydney.md2");
	if (!_mesh)
		throw std::runtime_error("Mesh load error");
}

void SplashState::load()
{
	_endTime = Time::timestamp() + 3000;
	irr::scene::IAnimatedMeshSceneNode *node =
	gameManager.getSmgr()->addAnimatedMeshSceneNode(_mesh);
	_nodes.push_back(node);
	if (node)
	{
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		node->setMD2Animation(irr::scene::EMAT_STAND);
		node->setMaterialTexture( 0, gameManager.getDriver()->getTexture("assets/sydney.bmp") );
	}
	AState::load();
}

void SplashState::unload()
{
	for (auto &n : _nodes)
		n->remove();
	_nodes.clear();
	AState::unload();
}
