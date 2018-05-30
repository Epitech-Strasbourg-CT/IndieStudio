/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AState.cpp
*/

#include <iostream>
#include "../../include/AState.hpp"

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
	std::cerr << "unload splash" << std::endl;
}

AState::~AState()
{
	if (_loaded)
		unload();
}

