/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AssetsPool.hpp
*/

#ifndef BOMBERMAN_MESHPOOL_HPP
#define BOMBERMAN_MESHPOOL_HPP

#include <irrlicht.h>
#include <string>
#include <map>

class AssetsPool {
public:
	static AssetsPool &getInstance();

	irr::scene::IMesh *loadMesh(const std::string &file);
	irr::video::ITexture *loadTexture(const std::string &file);
private:
	AssetsPool(const std::string &rootModelPath,
	const std::string &rootTextures);

	std::string _rootModelPath;
	std::string _rootTexturePath;
	std::map<std::string, irr::scene::IMesh *> _meshs;
	std::map<std::string, irr::video::ITexture *> _textures;

	static AssetsPool _meshPool;
};


#endif /* !BOMBERMAN_MESHPOOL_HPP */
