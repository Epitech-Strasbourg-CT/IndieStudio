/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AStateShare.hpp
*/

#include <string>
#include <ISceneNode.h>
#include <map>
#include <vector>
#include <ik_ISound.h>
#include "../Game/EntitiesMap.hpp"
#include "../Singletons/AssetsPool.hpp"

#ifndef BOMBERMAN_ASTATESHARE_HPP
#define BOMBERMAN_ASTATESHARE_HPP

class AStateShare {
public:
	AStateShare();
	bool setIAState(std::vector<int> const &stateIA);
	const std::vector<int> &getIAState() const;
	bool addSharedNode(const std::string &, irr::scene::ISceneNode *);
	bool delSharedNode(const std::string &);
	irr::scene::ISceneNode &getSharedNode(const std::string &);
	bool isKeyDown(irr::EKEY_CODE keyCode) const;
	bool isKeyPressed(irr::EKEY_CODE keyCode);
	bool isKeyReleased(irr::EKEY_CODE keyCode);
	void pushMusic(irrklang::ISound *);
	void popMusic(AssetsPool::Assets);
	EntitiesMap *getMap() const;
	void setMap(EntitiesMap *map);
	void addCoor(std::string const &name, irr::core::vector3df const &coor);
	void delCoor(std::string const &name);
	irr::core::vector3df getCoor(std::string const &name);

private:
	std::map<std::string, irr::scene::ISceneNode *> _sharedNodes;
	std::map<irr::EKEY_CODE, bool> _isKeyDown;
	std::map<irr::EKEY_CODE, bool> _isKeyPressed;
	std::map<irr::EKEY_CODE, bool> _isKeyReleased;
	std::vector<int> _stateIA;
	std::stack<irrklang::ISound *> _music;
	std::map<std::string, irr::core::vector3df> _coor;
	EntitiesMap *_map;
};


#endif /* !BOMBERMAN_ASTATESHARE_HPP */
