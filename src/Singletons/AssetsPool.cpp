/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AssetsPool.cpp
*/

#include <iostream>
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/PathManager.hpp"


const std::vector<AssetsPool::soundInfo> AssetsPool::_sounds = {
	{
		AssetsPool::MUSIC,
		"assets/sounds/MenuSong.mp3",
		&IrrManager::getMusicVolume
	},
	{
		AssetsPool::MUSIC,
		"assets/sounds/GameSong.mp3",
		&IrrManager::getMusicVolume
	},
	{
		AssetsPool::MUSIC,
		"assets/sounds/Victory.mp3",
		&IrrManager::getMusicVolume
	},
	{
		AssetsPool::SFX,
		"assets/sounds/MenuSelect.mp3",
		&IrrManager::getEffectsVolume
	},
	{
		AssetsPool::SFX,
		"assets/sounds/MenuCursormove.mp3",
		&IrrManager::getEffectsVolume
	},
	{
		AssetsPool::SFX,
		"assets/sfx/BombBlow.mp3",
		&IrrManager::getEffectsVolume
	},
	{
		AssetsPool::SFX,
		"assets/sfx/BombDrop.mp3",
		&IrrManager::getEffectsVolume
	},
	{
		AssetsPool::SFX,
		"assets/sfx/GetRupee.mp3",
		&IrrManager::getEffectsVolume
	},
	{
		AssetsPool::SFX,
		"assets/sfx/LinkDeath.mp3",
		&IrrManager::getEffectsVolume
	},
	{
		AssetsPool::SFX,
		"assets/sfx/PotShatter.mp3",
		&IrrManager::getEffectsVolume
	}
};

AssetsPool AssetsPool::_meshPool("assets/models/", "assets/textures/");

AssetsPool::~AssetsPool()
{
	for (int asset = MENU; asset < FINAL; ++asset) {
		for (size_t i = 0; i < _sModule[asset].size(); ++i) {
			_sModule[asset][i]->stop();
			_sModule[asset][i]->drop();
			_sModule[asset].erase(_sModule[asset].begin() + i);
		}
	}
}

AssetsPool &AssetsPool::getInstance()
{
	_meshPool._sModule.resize(AssetsPool::FINAL);
	return _meshPool;
}

AssetsPool::AssetsPool(const std::string &rootModelPath,
	const std::string &rootTexturesPath
) : _rootModelPath(rootModelPath), _rootTexturePath(rootTexturesPath), _meshs(),
    _textures()
{
}

irr::video::ITexture *AssetsPool::loadTexture(const std::string &file)
{
	irr::io::path path = PathManager::getExecPath(_rootTexturePath + file).c_str();
	if (_meshs.count(file) > 0)
		return _textures.at(file);
	irr::video::ITexture *texture = IrrManager::getInstance().getDriver()->getTexture(
		path);
	if (!texture)
		throw std::runtime_error("Can't load textures " + file);
	_textures[file] = texture;
	return texture;
}

irr::scene::IMesh *AssetsPool::loadMesh(const std::string &file)
{
	irr::io::path path = PathManager::getExecPath(std::string(_rootModelPath + file)).c_str();
	if (_meshs.count(file) > 0)
		return _meshs.at(file);
	irr::scene::IMesh *mesh = IrrManager::getInstance().getSmgr()->getMesh(
		path);
	if (!mesh)
		throw std::runtime_error("Can't load mesh " +
		                         std::string(_rootModelPath + file));
	_meshs[file] = mesh;
	return mesh;
}

irrklang::ISound *AssetsPool::loadSound(const AssetsPool::Assets asset,
	bool loop
)
{
	auto engine = IrrManager::getInstance().getEngine();
	auto &instance = IrrManager::getInstance();
	auto module = engine->play2D(PathManager::getExecPath(_sounds.at(asset).name).c_str(), loop, true,
	                             false);
	if (!module)
		throw std::runtime_error("Unable to load " + PathManager::getExecPath(_sounds.at(asset).name));
	module->setVolume((instance.*(_sounds.at(asset).vol))());
	module->setIsPaused(true);
	_sModule[asset].push_back(module);
	return module;
}

void AssetsPool::unloadSound(AssetsPool::Assets asset, irrklang::ISound *module)
{
	for (size_t i = 0; i < _sModule[asset].size(); ++i)
		if (_sModule[asset][i] == module) {
			_sModule[asset][i]->stop();
			_sModule[asset][i]->drop();
			_sModule[asset].erase(_sModule[asset].begin() + i);
			break;
		}
}

void AssetsPool::setVolume(AssetsPool::Types type, irrklang::ik_f32 vol)
{
	for (size_t i = 0; i < _sounds.size(); ++i)
		if (_sounds[i].type == type)
			for (size_t j = 0; j < _sModule[i].size(); ++j)
				_sModule[i][j]->setVolume(vol);
}

void AssetsPool::cleanSound()
{
	for (int asset = MENU; asset < FINAL; ++asset) {
		for (size_t i = 0; i < _sModule[asset].size(); ++i) {
			if (_sModule[asset][i]->isFinished()) {
				_sModule[asset][i]->stop();
				_sModule[asset][i]->drop();
				_sModule[asset].erase(_sModule[asset].begin() + i);
			}
		}
	}
}
