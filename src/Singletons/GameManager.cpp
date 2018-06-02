/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include "../../include/Singletons/GameManager.hpp"

GameManager GameManager::_instance;

GameManager::~GameManager()
{
	_device->drop();
}

GameManager::GameManager()
: _width(800),
_height(600)
{
	_device = irr::createDevice(
	irr::video::EDT_OPENGL,
	irr::core::dimension2d<irr::u32>(_width, _height),
	32, false, false, false, nullptr);
	_driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
	_guienv = _device->getGUIEnvironment();
}

irr::IrrlichtDevice *GameManager::getDevice() const
{
	return _device;
}

irr::video::IVideoDriver *GameManager::getDriver() const
{
	return _driver;
}

irr::scene::ISceneManager *GameManager::getSmgr() const
{
	return _smgr;
}

irr::gui::IGUIEnvironment *GameManager::getGuienv() const
{
	return _guienv;
}

GameManager &GameManager::getInstance()
{
	return _instance;
}
