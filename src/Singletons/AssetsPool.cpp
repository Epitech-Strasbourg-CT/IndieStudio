/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AssetsPool.cpp
*/

#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/Singletons/IrrManager.hpp"

AssetsPool AssetsPool::_meshPool("assets/models/", "assets/textures/");

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
	IrrManager::getInstance().getDriver()->getTexture(path);
	if (!texture)
		throw std::runtime_error("Can't load textures " + file);
	_textures[file] = texture;
	return texture;
}

irr::scene::IMesh *AssetsPool::loadMesh(const std::string &file)
{
	irr::io::path path = std::string(_rootModelPath + file).c_str();
	if (_meshs.count(file) > 0)
		return _meshs.at(file);
	irr::scene::IMesh *mesh = IrrManager::getInstance().getSmgr
	()->getMesh(path);
	if (!mesh)
		throw std::runtime_error("Can't load mesh " +
		std::string(_rootModelPath + file));
	_meshs[file] = mesh;
	return mesh;
}