/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AStateShare.cpp
*/

#include <iostream>
#include "../../include/Abstracts/AStateShare.hpp"
#include "../../include/Singletons/EventReceiver.hpp"

AStateShare::AStateShare(): _sharedNodes(), _isKeyDown(), _stateIA(4), _map(),
_sphereCoor(), _func()
{
	EventReceiver::getInstance().registerEvent(0, irr::EET_KEY_INPUT_EVENT,
        [this](const irr::SEvent &ev) {
		auto key = ev.KeyInput.Key;
	        this->_isKeyDown[key] = ev.KeyInput.PressedDown;
		this->_isKeyPressed[key] = ev.KeyInput.PressedDown;
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

bool AStateShare::isKeyPressed(irr::EKEY_CODE keyCode)
{
	bool res = false;
	if (_isKeyPressed.count(keyCode) > 0) {
		res = _isKeyPressed.at(keyCode);
		_isKeyPressed[keyCode] = false;
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

const std::vector<int> &AStateShare::getIAState() const
{
	return _stateIA;
}


void AStateShare::setMap(EntitiesMap *map)
{
	AStateShare::_map = map;
}

void AStateShare::pushMusic(irrklang::ISound *sound)
{
	if (!_music.empty())
		_music.top()->setIsPaused(true);
	_music.push(sound);
	_music.top()->setIsPaused(false);
}

void
AStateShare::addCoor(std::string const &name, irr::core::vector3df const &coor)
{
	if (_coor.count(name) == 0)
		_coor[name] = coor;
}

void AStateShare::popMusic(AssetsPool::Assets asset)
{
	AssetsPool::getInstance().unloadSound(asset, _music.top());
	_music.pop();
	if (!_music.empty())
		_music.top()->setIsPaused(false);
}

void AStateShare::delCoor(std::string const &name)
{
	if (_coor.count(name) > 0)
		_coor.erase(name);
}

irr::core::vector3df AStateShare::getCoor(std::string const &name)
{
	irr::core::vector3df coor;

	if (_coor.count(name) != 0)
		coor = _coor[name];
	return coor;
}

bool AStateShare::addSphereCoor(std::string const &name, SphericalCoordinate const *coor)
{
	bool ret = true;

	if (_sphereCoor.count(name) != 0)
		ret = false;
	else
		_sphereCoor[name] = coor;
	return ret;
}

bool AStateShare::delSphereCoor(std::string const &name)
{
	bool ret = true;

	if (_sphereCoor.count(name) <= 0)
		ret = false;
	else
		_sphereCoor.erase(name);
	return ret;
}

SphericalCoordinate const *AStateShare::getSphereCoor(std::string const &name)
{
	if (_sphereCoor.count(name) <= 0)
		throw std::runtime_error("Invalid get sphere coordinate request");
	return _sphereCoor[name];
}

bool AStateShare::addFunc(std::string const &name, std::function<void()> func)
{
	bool ret = true;

	if (_func.count(name) != 0)
		ret = false;
	else
		_func[name] = func;
	return ret;
}

bool AStateShare::delFunc(std::string const &name)
{
	bool ret = true;

	if (_func.count(name) <= 0)
		ret = false;
	else
		_func.erase(name);
	return ret;
}

std::function<void()> AStateShare::getFunc(std::string const &name)
{
	if (_func.count(name) <= 0)
		throw std::runtime_error("Invalid get func request");
	return _func[name];
}
