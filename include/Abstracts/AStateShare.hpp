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
#include "../Game/EntitiesMap.hpp"

#ifndef BOMBERMAN_ASTATESHARE_HPP
#define BOMBERMAN_ASTATESHARE_HPP

class AStateShare {
public:
	AStateShare();
	bool setIAState(std::vector<int> const &stateIA);
	std::vector<int> getIAState();
	bool addSharedNode(const std::string &, irr::scene::ISceneNode *);
	bool delSharedNode(const std::string &);
	irr::scene::ISceneNode &getSharedNode(const std::string &);
	bool isKeyDown(irr::EKEY_CODE keyCode) const;
	bool isKeyReleased(irr::EKEY_CODE keyCode);
	EntitiesMap *getMap() const;
	void setMap(EntitiesMap *map);
private:
	std::map<std::string, irr::scene::ISceneNode *> _sharedNodes;
	std::map<irr::EKEY_CODE, bool> _isKeyDown;
	std::map<irr::EKEY_CODE, bool> _isKeyReleased;
	std::vector<int> _stateIA;
	EntitiesMap *_map;
};


#endif /* !BOMBERMAN_ASTATESHARE_HPP */
