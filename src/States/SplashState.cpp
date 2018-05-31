/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AState.cpp
*/
#include <stdexcept>
#include <string>
#include "../../include/SplashState.hpp"
#include "../../include/Time.hpp"
#include "../../include/StateMachine.hpp"
#include "../../include/GameManager.hpp"

void SplashState::update()
{
	if (_endTime < Time::timestamp()) {
		StateMachine::getInstance().pop();
	}
}

SplashState::SplashState()
{
}

void SplashState::load()
{
	auto manager = GameManager::getInstance().getSmgr();
	auto texture = GameManager::getInstance().getDriver()->getTexture("assets/bomber.jpg");

	_endTime = Time::timestamp() + 3000;

	manager->addCameraSceneNodeFPS();
	auto ok = manager->getGeometryCreator()->createCubeMesh
	(irr::core::vector3df(10, 10, 10));

	auto mdr = manager->addMeshSceneNode(ok);
	mdr->setPosition(irr::core::vector3df(10, 10, 0));

	_mesh = manager->getGeometryCreator()->createPlaneMesh
	(irr::core::dimension2d<irr::f32>(200, 200));

	_node = manager->addMeshSceneNode(_mesh);

	_node->setMaterialFlag
	(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);

	_node->setPosition(irr::core::vector3df(0, 0, 0));

	_node->setMaterialTexture(0, texture);

	AState::load();
}

void SplashState::unload()
{
	AState::unload();
}
