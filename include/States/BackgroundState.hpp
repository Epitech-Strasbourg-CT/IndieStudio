/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BackgroundState.hpp
*/

#include <irrlicht.h>
#include <vector>
#include <chrono>
#include "../Abstracts/AState.hpp"

#ifndef BOMBERMAN_BACKGROUNDSTATE_HPP
#define BOMBERMAN_BACKGROUNDSTATE_HPP

class BackgroundState : public AState {
public:
	BackgroundState(AStateShare &_share);

	void load() override;
	void unload() override;
	void transitionPop() override;
	void transitionPush(bool keep) override;

private:
	irr::scene::ISceneNode *_node;

	void loadCharacter();

	void loadSkyBox();

	void loadMap();
};

#endif /* !BOMBERMAN_BACKGROUNDSTATE_HPP */
