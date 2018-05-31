/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AssetsPool.cpp
*/

#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/Singletons/GameManager.hpp"

AssetsPool AssetsPool::_meshPool("assets/models/", "assets/");

AssetsPool &AssetsPool::getInstance()
{
	return _meshPool;
}

AssetsPool::AssetsPool(const std::string &rootModelPath,
const std::string &rootTexturesPath)
: _rootModelPath(rootModelPath),
_rootTexturePath(rootTexturesPath),
_meshs(),
_textures()
{
}

irr::video::ITexture *AssetsPool::loadTexture(const std::string &file)
{
	irr::io::path path = std::string(_rootTexturePath + file).c_str();
	if (_meshs.count(file) > 0)
		return _textures.at(file);
	irr::video::ITexture *texture =
	GameManager::getInstance().getDriver()->getTexture(path);
	if (!texture)
		throw std::runtime_error("Can't load texture " + file);
	_textures[file] = texture;
	return texture;
}

irr::scene::IMesh *AssetsPool::loadMesh(const std::string &file)
{
	irr::io::path path = std::string(_rootModelPath + file).c_str();
	if (_meshs.count(file) > 0)
		return _meshs.at(file);
	irr::scene::IMesh *mesh = GameManager::getInstance().getSmgr
	()->getMesh(path);
	if (!mesh)
		throw std::runtime_error("Can't load mesh " + file);
	_meshs[file] = mesh;
	return mesh;
}