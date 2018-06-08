/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AState.cpp
*/

#include <iostream>
#include "../../include/Abstracts/AState.hpp"
#include "../../include/Singletons/IrrManager.hpp"

AState::AState(AStateShare &_share) : _share(_share)
{
}

bool AState::isEnable() const
{
	return _enable;
}

void AState::setEnable(bool _enable)
{
	AState::_enable = _enable;
}

bool AState::isLoaded() const
{
	return _loaded;
}

void AState::load()
{
	_loaded = true;
}

void AState::unload()
{
	_loaded = false;
}

AState::~AState()
{
	if (_loaded)
		unload();
}

void AState::transitionPop()
{
}

void AState::transitionPush(bool keep)
{
	static_cast<void>(keep);
}

void AState::addAlteredNode
(irr::scene::ISceneNode *n, std::function<void(irr::scene::ISceneNode *)> fct)
{
	if (_alteredNodes.count(n) > 0)
		throw std::runtime_error("Node is already Altered");
	_alteredNodes[n] = fct;
}

AStateShare &AState::getSharedResources() const
{
	return _share;
}

void AState::pushing(bool keep)
{

}

void AState::popping()
{
	for (auto &n : _alteredNodes)
		n.second(n.first);
}

void AState::draw()
{
	IrrManager::getInstance().getSmgr()->drawAll();
}

void AState::updateRender()
{

}

void AState::update()
{

}

