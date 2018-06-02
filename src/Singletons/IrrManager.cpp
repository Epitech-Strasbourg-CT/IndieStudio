/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include "../../include/Singletons/IrrManager.hpp"

IrrManager IrrManager::_instance;

IrrManager::~IrrManager()
{
	_device->drop();
}

IrrManager::IrrManager()
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

irr::IrrlichtDevice *IrrManager::getDevice() const
{
	return _device;
}

irr::video::IVideoDriver *IrrManager::getDriver() const
{
	return _driver;
}

irr::scene::ISceneManager *IrrManager::getSmgr() const
{
	return _smgr;
}

irr::gui::IGUIEnvironment *IrrManager::getGuienv() const
{
	return _guienv;
}

IrrManager &IrrManager::getInstance()
{
	return _instance;
}
