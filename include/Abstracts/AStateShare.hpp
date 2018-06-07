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
private:
	std::map<std::string, irr::scene::ISceneNode *> _sharedNodes;
	std::map<irr::EKEY_CODE, bool> _isKeyDown;
	std::vector<int> _stateIA;
};


#endif /* !BOMBERMAN_ASTATESHARE_HPP */
