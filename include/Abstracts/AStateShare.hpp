/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AStateShare.hpp
*/

#include <string>
#include <ISceneNode.h>
#include <map>

#ifndef BOMBERMAN_ASTATESHARE_HPP
#define BOMBERMAN_ASTATESHARE_HPP

class AStateShare {
public:
	AStateShare();
	bool addSharedNode(const std::string &, irr::scene::ISceneNode &);
	bool delSharedNode(const std::string &);
	irr::scene::ISceneNode & getSharedNode(const std::string &);
private:
	std::map<std::string, irr::scene::ISceneNode *> _sharedNodes;
};


#endif /* !BOMBERMAN_ASTATESHARE_HPP */
