/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AStateShare.cpp
*/

#include <iostream>
#include "../../include/Abstracts/AStateShare.hpp"

AStateShare::AStateShare(): _sharedNodes()
{
}

bool AStateShare::addSharedNode
(const std::string &key, irr::scene::ISceneNode *node)
{
	bool ret = true;

	if (_sharedNodes.count(key) != 0)
		ret = false;
	else
		_sharedNodes[key] = node;
	return ret;
}

bool AStateShare::delSharedNode(const std::string &key)
{
	bool ret = true;

	if (_sharedNodes.count(key) != 0)
		ret = false;
	else
		_sharedNodes.erase(key);
	return ret;
}

irr::scene::ISceneNode &AStateShare::getSharedNode(const std::string &key)
{
	return *_sharedNodes[key];
}

