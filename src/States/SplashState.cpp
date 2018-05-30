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

void SplashState::update()
{
	if (_endTime < gameManager.getCycles()) {
		//std::cerr << "POP!" << std::endl;
		stateMachine.pop();
	} else {
//		std::cerr << "Cycles : " << std::to_string(gameManager
//							 .getCycles())
//			  << " / " <<
//			  std::to_string(_endTime) << std::endl;
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
	_endTime = gameManager.getCycles() + 100;
	irr::scene::IAnimatedMeshSceneNode *node =
	gameManager.getSmgr()->addAnimatedMeshSceneNode(_mesh);
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
		n.remove();
	AState::unload();
}
