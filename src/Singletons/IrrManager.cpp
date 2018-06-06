/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/AssetsPool.hpp"

IrrManager IrrManager::_instance;

IrrManager::~IrrManager()
{
	_device->drop();
	_engine->drop();
}

IrrManager::IrrManager()
	: _width(800),
	  _height(600),
	  _master(1),
	  _effects(0.5),
	  _musics(1)
{
	_device = irr::createDevice(
		irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(_width, _height),
		32, false, false, false, nullptr);
	_driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
	_guienv = _device->getGUIEnvironment();
	_engine = irrklang::createIrrKlangDevice();
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

irrklang::ISoundEngine *IrrManager::getEngine() const
{
	return _engine;
}

IrrManager &IrrManager::getInstance()
{
	return _instance;
}

irr::core::vector2di IrrManager::getSize() const
{
	return {_width, _height};
}

irrklang::ik_f32 IrrManager::getMasterVolume() const
{
	return _master;
}

irrklang::ik_f32 IrrManager::getEffectsVolume() const
{
	return _effects;
}

irrklang::ik_f32 IrrManager::getMusicVolume() const
{
	return _musics;
}

void IrrManager::setMasterVolume(irrklang::ik_f32 vol)
{
	auto &manager = IrrManager::getInstance();

	_master = std::min<irrklang::ik_f32>(1, std::max<irrklang::ik_f32>(-1, vol));;
	manager.getEngine()->setSoundVolume(_master);
}

void IrrManager::setEffectsVolume(irrklang::ik_f32 vol)
{
	_effects = std::min<irrklang::ik_f32>(1, std::max<irrklang::ik_f32>(-1, vol));
	AssetsPool::getInstance().setVolume(AssetsPool::SFX, _effects);
}

void IrrManager::setMusicVolume(irrklang::ik_f32 vol)
{
	_musics = std::min<irrklang::ik_f32>(1, std::max<irrklang::ik_f32>(-1, vol));;
	AssetsPool::getInstance().setVolume(AssetsPool::MUSIC, _musics);
}
