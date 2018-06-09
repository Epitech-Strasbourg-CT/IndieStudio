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
#include <ik_ISound.h>
#include <functional>
#include <vector>
#include "IrrManager.hpp"

class AssetsPool {
public:
	static AssetsPool &getInstance();
	~AssetsPool();
	enum Assets {
		MENU = 0,
		GAME,
		SELECT,
		CURSOR,
		FINAL
	};

	enum Types {
		SFX,
		MUSIC,
	};

	struct soundInfo {
		AssetsPool::Types type;
		std::string name;
		irrklang::ik_f32 (IrrManager::*vol)(void) const;
	};

	irr::scene::IMesh *loadMesh(const std::string &file);
	irr::video::ITexture *loadTexture(const std::string &file);

	irrklang::ISound *loadSound(AssetsPool::Assets, bool);
	void unloadSound(AssetsPool::Assets, irrklang::ISound *);
	void setVolume(AssetsPool::Types, irrklang::ik_f32);
	void cleanSound();
private:
	AssetsPool(const std::string &rootModelPath,
	const std::string &rootTextures);

	std::string _rootModelPath;
	std::string _rootTexturePath;
	std::map<std::string, irr::scene::IMesh *> _meshs;
	std::map<std::string, irr::video::ITexture *> _textures;
	std::vector<std::vector<irrklang::ISound *>> _sModule;

	//FIXME CONST STATIC
	static const std::vector<soundInfo> _sounds;
	static AssetsPool _meshPool;
};


#endif /* !BOMBERMAN_MESHPOOL_HPP */
