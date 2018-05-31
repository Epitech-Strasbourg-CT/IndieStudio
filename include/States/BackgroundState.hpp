/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BackgroundState.hpp
*/

#include <irrlicht.h>
#include <vector>
#include <chrono>
#include "AState.hpp"

#ifndef BOMBERMAN_BACKGROUNDSTATE_HPP
#define BOMBERMAN_BACKGROUNDSTATE_HPP

class BackgroundState : public AState {
public:
	void load() override;
	void unload() override;
	void update() override;
private:
	irr::scene::ISceneNode *_node;
};

#endif /* !BOMBERMAN_BACKGROUNDSTATE_HPP */
