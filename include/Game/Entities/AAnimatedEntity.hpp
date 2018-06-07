/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AAnimatedEntity.hpp
*/

#ifndef BOMBERMAN_AANIMATEDENTITY_HPP
#define BOMBERMAN_AANIMATEDENTITY_HPP


#include "../AEntity.hpp"

class AAnimatedEntity: public AEntity {

public:

	AAnimatedEntity(const std::string &str, int x = 0, int y = 0);
	irr::scene::ISceneNode *
	addAnimationNode(const std::string &name, const std::string &mesh,
		const std::string &meshName);
	void cleanAnimationNodes();
	void selectAnimation(const std::string &name);
private:
	std::map<std::string, irr::scene::ISceneNode *> _animationsNodes;
};


#endif /* !BOMBERMAN_AANIMATEDENTITY_HPP */
