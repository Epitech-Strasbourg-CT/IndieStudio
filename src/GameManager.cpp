/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include "../include/GameManager.hpp"

GameManager::~GameManager()
{
	_device->drop();
}

GameManager::GameManager()
{
	_device = irr::createDevice(
	irr::video::EDT_SOFTWARE,
	irr::core::dimension2d<irr::u32>(640, 480),
	16, false, false, false, 0);
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

size_t GameManager::getCycles() const
{
	return _cycles;
}

void GameManager::resetCycles()
{
	_cycles = 0;
}

void GameManager::upCycles()
{
	_cycles += 1;
}
