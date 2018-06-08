/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AStateShare.cpp
*/

#include <iostream>
#include "../../include/Abstracts/AStateShare.hpp"
#include "../../include/Singletons/EventReceiver.hpp"

AStateShare::AStateShare(): _sharedNodes(), _isKeyDown(), _stateIA(4), _map()
{
	EventReceiver::getInstance().registerEvent(0, irr::EET_KEY_INPUT_EVENT,
        [this](const irr::SEvent &ev) {
		auto key = ev.KeyInput.Key;
	        this->_isKeyDown[ev.KeyInput.Key] = ev.KeyInput.PressedDown;
		this->_isKeyReleased[key] = !ev.KeyInput.PressedDown;
		return true;
	});
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

	if (_sharedNodes.count(key) <= 0)
		ret = false;
	else
		_sharedNodes.erase(key);
	return ret;
}

irr::scene::ISceneNode &AStateShare::getSharedNode(const std::string &key)
{
	if (_sharedNodes.count(key) <= 0 || _sharedNodes[key] == nullptr)
		throw std::runtime_error("Invalid shared node request");
	return *_sharedNodes[key];
}

bool AStateShare::isKeyDown(irr::EKEY_CODE keyCode) const
{
	if (_isKeyDown.count(keyCode) > 0)
		return _isKeyDown.at(keyCode);
	return false;
}

bool AStateShare::isKeyReleased(irr::EKEY_CODE keyCode)
{
	bool res = false;
	if (_isKeyReleased.count(keyCode) > 0) {
		res = _isKeyReleased.at(keyCode);
		_isKeyReleased[keyCode] = false;
	}
	return res;
}

bool AStateShare::setIAState(std::vector<int> const &stateIA)
{
	_stateIA = stateIA;
	return true;
}
EntitiesMap *AStateShare::getMap() const
{
	if (_map == nullptr)
		throw std::runtime_error("Map isn't load");
	return _map;
}

std::vector<int> AStateShare::getIAState()
{
	return _stateIA;
}


void AStateShare::setMap(EntitiesMap *map)
{
	AStateShare::_map = map;
}

