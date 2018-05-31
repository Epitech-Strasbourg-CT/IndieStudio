/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AState.cpp
*/
#include <irrlicht.h>
#include <vector>
#include "AState.hpp"

#ifndef BOMBERMAN_SPLASHSTATE_HPP
#define BOMBERMAN_SPLASHSTATE_HPP


class SplashState : public AState {
public:
	SplashState();
	virtual ~SplashState() = default;
	void update() override;
	void load() override;
	void unload() override;

private:
	irr::scene::IMesh *_mesh;
	irr::scene::ISceneNode *_node;
	size_t _endTime;
};


#endif //BOMBERMAN_SPLASHSTATE_HPP
